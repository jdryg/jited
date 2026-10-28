#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // NULL
#include <stdio.h>
#include <string.h>
#include <jitsheet/canvas.h>
#include <jitsheet/image.h>
#include <jitsheet/os.h>

#define PLAYFIELD_WIDTH  10
#define PLAYFIELD_HEIGHT 20

typedef enum piece_kind
{
	PIECE_NONE = 0,
	PIECE_I,
	PIECE_J,
	PIECE_L,
	PIECE_O,
	PIECE_S,
	PIECE_Z,
	PIECE_T,
	PIECE_COUNT,
} piece_kind;

static const uint32_t kPieceColor[PIECE_COUNT] = {
    CANVAS_COLOR(0, 0, 0, 255),     // None = black
    CANVAS_COLOR(0, 255, 255, 255), // I = light blue
    CANVAS_COLOR(0, 0, 255, 255),   // J = dark blue
    CANVAS_COLOR(255, 128, 0, 255), // L = orange
    CANVAS_COLOR(255, 255, 0, 255), // O = yellow
    CANVAS_COLOR(0, 255, 0, 255),   // S = green
    CANVAS_COLOR(255, 0, 0, 255),   // Z = red
    CANVAS_COLOR(255, 0, 255, 255), // T = magenta
};

typedef struct piece_shape_t
{
	uint8_t m_Bitmask[4]; // 4-bits per row
} piece_shape_t;

static const piece_shape_t kPieceShapes[PIECE_COUNT][4] = {
    [PIECE_NONE] = {
        {0b0000, 0b0000, 0b0000, 0b0000}, // 0b0000000000000000
        {0b0000, 0b0000, 0b0000, 0b0000}, // 0b0000000000000000
        {0b0000, 0b0000, 0b0000, 0b0000}, // 0b0000000000000000
        {0b0000, 0b0000, 0b0000, 0b0000}, // 0b0000000000000000
    },
    [PIECE_I] = {
        {0b0000, 0b0000, 0b1111, 0b0000}, // 0b0000111100000000
        {0b0100, 0b0100, 0b0100, 0b0100}, // 0b0100010001000100
        {0b0000, 0b1111, 0b0000, 0b0000}, // 0b0000000011110000
        {0b0010, 0b0010, 0b0010, 0b0010}, // 0b0010001000100010
    },
    [PIECE_J] = {
        {0b0000, 0b0111, 0b0001, 0b0000}, // 0b0000000101110000
        {0b0010, 0b0010, 0b0110, 0b0000}, // 0b0000011000100010
		{0b0100, 0b0111, 0b0000, 0b0000}, // 0b0000000001110100
		{0b0011, 0b0010, 0b0010, 0b0000}, // 0b0000001000100011
    },
    [PIECE_L] = {
        {0b0000, 0b0111, 0b0100, 0b0000}, // 0b0000010001110000
        {0b0110, 0b0010, 0b0010, 0b0000}, // 0b0000001000100110
		{0b0001, 0b0111, 0b0000, 0b0000}, // 0b0000000001110001
		{0b0010, 0b0010, 0b0011, 0b0000}, // 0b0000001100100010
    },
    [PIECE_O] = {
        {0b0000, 0b0110, 0b0110, 0b0000}, // 0b0000011001100000
        {0b0000, 0b0110, 0b0110, 0b0000}, // 0b0000011001100000
        {0b0000, 0b0110, 0b0110, 0b0000}, // 0b0000011001100000
        {0b0000, 0b0110, 0b0110, 0b0000}, // 0b0000011001100000
    },
    [PIECE_S] = {
        {0b0000, 0b0011, 0b0110, 0b0000}, // 0b0000011000110000
        {0b0100, 0b0110, 0b0010, 0b0000}, // 0b0000001001100100
		{0b0011, 0b0110, 0b0000, 0b0000}, // 0b0000000001100011
		{0b0010, 0b0011, 0b0001, 0b0000}, // 0b0000000100110010
    },
    [PIECE_T] = {
		{0b0000, 0b0111, 0b0010, 0b0000}, // 0b0000001001110000
        {0b0010, 0b0110, 0b0010, 0b0000}, // 0b0000001001100010
		{0b0010, 0b0111, 0b0000, 0b0000}, // 0b0000000001110010
		{0b0010, 0b0011, 0b0010, 0b0000}, // 0b0000001000110010
    },
    [PIECE_Z] = {
        {0b0000, 0b0110, 0b0011, 0b0000}, // 0b0000001101100000
		{0b0010, 0b0110, 0b0100, 0b0000}, // 0b0000010001100010
		{0b0110, 0b0011, 0b0000, 0b0000}, // 0b0000000000110110
		{0b0001, 0b0011, 0b0010, 0b0000}, // 0b0000001000111000
    },
};

typedef struct piece_t
{
	piece_kind m_Kind;
	int32_t m_PosX;
	int32_t m_PosY;
	uint32_t m_Orientation;
} piece_t;

typedef struct pcg32_random_t
{
	uint64_t state;
	uint64_t inc;
} pcg32_random_t;

typedef struct playfield_t
{
	pcg32_random_t m_RNG;
	uint32_t* m_Image;
	uint16_t m_TileFilled[PLAYFIELD_HEIGHT + 3];
	uint8_t m_TilePiece[PLAYFIELD_WIDTH * PLAYFIELD_HEIGHT];
	uint32_t m_PieceBag[7];
	uint32_t m_RemainingBagPieces;
	piece_t m_CurPiece;
	uint32_t m_TotalLinesCleared;
	uint32_t m_Score;
	uint32_t m_Level;
	uint32_t m_NumTetris; // consecutive 4-line clears
	uint32_t m_NumClears; // consecutive any-line clears;
	float m_TickTimer_ms;
} playfield_t;

static const uint32_t kClearLineScore[5] = {
    0, 100, 300, 500, 800
};

static void playfieldInit(playfield_t* pf);
static void playfieldGenPieceBag(playfield_t* pf);
static void playfieldTick(playfield_t* pf, float dt, bool wasHardDrop);
static bool playfieldCanPlacePieceAt(playfield_t* pf, piece_kind piece, uint32_t orientation, int32_t x, int32_t y);
static bool playfieldPieceTranslate(playfield_t* pf, piece_t* piece, int32_t dx, int32_t dy);
static bool playfieldPieceRotate(playfield_t* pf, piece_t* piece, int32_t delta);
static void canvasDrawImage(canvas_t* canvas, float x, float y, float w, float h, image_t* img);
static void generateCheckerboardImg(uint8_t* pixels, uint32_t w, uint32_t h);

#define PLAYFIELD_ORIGIN_X 3
#define PLAYFIELD_ORIGIN_Y 1

int32_t main(void)
{
	playfield_t pf = { 0 };

	playfieldInit(&pf);

	image_t* img = imageCreate(PLAYFIELD_WIDTH * 16, PLAYFIELD_HEIGHT * 16, (const uint8_t*)&pf.m_Image[0]);

	const uint32_t canvasWidth = PLAYFIELD_WIDTH * 16;
	const uint32_t canvasHeight = PLAYFIELD_HEIGHT * 16 + 32;
	canvas_t* canvas = canvasCreate(canvasWidth, canvasHeight, CANVAS_FLAGS_NONE);

	int64_t startTime = os_timeNow();
	while (canvasIsOpen(canvas)) {
		const int64_t now = os_timeNow();
		const float dt = (float)os_timeConvertTo(os_timeDiff(now, startTime), OS_TIME_UNITS_MS);
		startTime = now;

		bool hardDrop = false;
		if (canvasIsKeyPressed(canvas, CANVAS_KEY_LEFT)) {
			playfieldPieceTranslate(&pf, &pf.m_CurPiece, -1, 0);
		} else if (canvasIsKeyPressed(canvas, CANVAS_KEY_RIGHT)) {
			playfieldPieceTranslate(&pf, &pf.m_CurPiece, 1, 0);
		} else if (canvasIsKeyPressed(canvas, CANVAS_KEY_DOWN)) {
			playfieldPieceTranslate(&pf, &pf.m_CurPiece, 0, -1);
		} else if (canvasIsKeyPressed(canvas, CANVAS_KEY_UP)) {
			playfieldPieceRotate(&pf, &pf.m_CurPiece, 1);
		} else if (canvasIsKeyPressed(canvas, CANVAS_KEY_Z)) {
			playfieldPieceRotate(&pf, &pf.m_CurPiece, -1);
		} else if (canvasIsKeyPressed(canvas, CANVAS_KEY_SPACE)) {
			// Hard drop.
			while (playfieldPieceTranslate(&pf, &pf.m_CurPiece, 0, -1)) {
				;
			}
			hardDrop = true;
		}

		playfieldTick(&pf, dt, hardDrop);
		imageSetRect(img, 0, 0, PLAYFIELD_WIDTH * 16, PLAYFIELD_HEIGHT * 16, pf.m_Image);

		canvasClear(canvas, CANVAS_COLOR(32, 32, 32, 255));
		canvasDrawImage(canvas, 0.0f, 32.0f, (float)canvasWidth, (float)(canvasHeight - 32), img);
		char scoreStr[256];
		snprintf(scoreStr, 256, "Score: %u", pf.m_Score);
		canvasDrawText(canvas, 0.0f, 24, 18, CANVAS_FONT_TYPE_MONO_REGULAR, scoreStr, CANVAS_COLOR(255, 255, 255, 255));
		canvasSwapBuffers(canvas);
	}

	canvasDestroy(canvas);

	return 0;
}

static void playfieldInit(playfield_t* pf)
{
	// * = wall
	// . = empty
	// 
	// 22- ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//     ***..........***
	//  0- ****************
	//     |              |
	//     0              15
	pf->m_TileFilled[0] = 0b1111111111111111;
	for (uint32_t y = 1; y < PLAYFIELD_HEIGHT + 3; ++y) {
		pf->m_TileFilled[y] = 0b1110000000000111;
	}

	pf->m_Level = 1;
	pf->m_NumTetris = 0;
	pf->m_NumClears = 0;
	pf->m_Score = 0;
	pf->m_TotalLinesCleared = 0;

	pf->m_RNG.state = os_timeNow();
	pf->m_RNG.inc = (uint64_t)&pf->m_RNG;
	playfieldGenPieceBag(pf);

	--pf->m_RemainingBagPieces;
	pf->m_CurPiece.m_Kind = pf->m_PieceBag[pf->m_RemainingBagPieces];
    pf->m_CurPiece.m_PosX = PLAYFIELD_ORIGIN_X + PLAYFIELD_WIDTH / 2 - 2;
	pf->m_CurPiece.m_PosY = PLAYFIELD_ORIGIN_Y + PLAYFIELD_HEIGHT - 2;
	pf->m_CurPiece.m_Orientation = 0;

	const uint32_t numPixels = (PLAYFIELD_WIDTH * 16) * (PLAYFIELD_HEIGHT * 16);
	pf->m_Image = (uint32_t*)malloc(sizeof(uint32_t) * numPixels);
}

// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
static uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

static void playfieldGenPieceBag(playfield_t* pf)
{
	pf->m_PieceBag[0] = PIECE_I;
	pf->m_PieceBag[1] = PIECE_J;
	pf->m_PieceBag[2] = PIECE_L;
	pf->m_PieceBag[3] = PIECE_O;
	pf->m_PieceBag[4] = PIECE_S;
	pf->m_PieceBag[5] = PIECE_Z;
	pf->m_PieceBag[6] = PIECE_T;

	for (uint32_t i = 7; i != 0; --i) {
		const uint32_t id = pcg32_random_r(&pf->m_RNG) % i;
		uint32_t tmp = pf->m_PieceBag[id];
		pf->m_PieceBag[id] = pf->m_PieceBag[i - 1];
		pf->m_PieceBag[i - 1] = tmp;
	}

	pf->m_RemainingBagPieces = 7;
}

static void playfieldSetColor(playfield_t* pf, int32_t x, int32_t y, uint32_t color)
{
	if (x < 0 || x >= PLAYFIELD_WIDTH || y < 0 || y >= PLAYFIELD_HEIGHT) {
		return;
	}

	const uint32_t imgX = x * 16;
	const uint32_t imgY = (PLAYFIELD_HEIGHT - 1 - y) * 16;
	uint32_t* rowPtr = &pf->m_Image[imgX + imgY * PLAYFIELD_WIDTH * 16];

	if (color == CANVAS_COLOR_BLACK) {
		// Empty tile
		for (uint32_t py = 0; py < 16; ++py) {
			for (uint32_t px = 0; px < 16; ++px) {
				*rowPtr++ = CANVAS_COLOR_BLACK;
			}

			rowPtr += (PLAYFIELD_WIDTH * 16) - 16;
		}
	} else {
		const uint32_t r = (color & CANVAS_COLOR_RED_Msk) >> CANVAS_COLOR_RED_Pos;
		const uint32_t g = (color & CANVAS_COLOR_GREEN_Msk) >> CANVAS_COLOR_GREEN_Pos;
		const uint32_t b = (color & CANVAS_COLOR_BLUE_Msk) >> CANVAS_COLOR_BLUE_Pos;
		const uint32_t a = (color & CANVAS_COLOR_ALPHA_Msk) >> CANVAS_COLOR_ALPHA_Pos;
		const uint32_t borderColor = CANVAS_COLOR((uint8_t)(r * 0.5f), (uint8_t)(g * 0.5f), (uint8_t)(b * 0.5f), a);

		uint32_t* rowPtr = &pf->m_Image[imgX + imgY * PLAYFIELD_WIDTH * 16];

		// first row
		for (uint32_t px = 0; px < 16; ++px) {
			*rowPtr++ = borderColor;
		}
		rowPtr += (PLAYFIELD_WIDTH * 16) - 16;

		for (uint32_t py = 1; py < 15; ++py) {
			*rowPtr++ = borderColor;
			for (uint32_t px = 1; px < 15; ++px) {
				*rowPtr++ = color;
			}
			*rowPtr++ = borderColor; 
			rowPtr += (PLAYFIELD_WIDTH * 16) - 16;
		}

		// last row
		{
			for (uint32_t px = 0; px < 16; ++px) {
				*rowPtr++ = borderColor;
			}
		}
	}
}

static void playfieldSetOutline(playfield_t* pf, int32_t x, int32_t y, uint32_t color)
{
	if (x < 0 || x >= PLAYFIELD_WIDTH || y < 0 || y >= PLAYFIELD_HEIGHT) {
		return;
	}

	const uint32_t imgX = x * 16;
	const uint32_t imgY = (PLAYFIELD_HEIGHT - 1 - y) * 16;
	uint32_t* rowPtr = &pf->m_Image[imgX + imgY * PLAYFIELD_WIDTH * 16];

	// first row
	for (uint32_t px = 0; px < 16; ++px) {
		*rowPtr++ = color;
	}
	rowPtr += (PLAYFIELD_WIDTH * 16) - 16;

	for (uint32_t py = 1; py < 15; ++py) {
		rowPtr[0] = color;
		rowPtr[15] = color; 
		rowPtr += (PLAYFIELD_WIDTH * 16);
	}

	// last row
	for (uint32_t px = 0; px < 16; ++px) {
		*rowPtr++ = color;
	}
}

static const float kFramesPerRow[13] = {
    60.0f, // 0
    60.0f, // 1
    36.0f, // 2
    24.0f, // 3
    18.0f, // 4
    12.0f, // 5
    9.0f,  // 6
    7.0f,  // 7
    6.0f,  // 8
    5.0f,  // 9
    4.0f,  // 10
    3.33f, // 11
    3.0f,  // 12
};

static inline float playfieldGetRowTick_ms(playfield_t* pf)
{
	const uint32_t level = pf->m_Level > 12 ? 12 : pf->m_Level;
	return kFramesPerRow[level] * 16.6f;
}

static void playfieldTick(playfield_t* pf, float dt_ms, bool wasHardDrop)
{
	pf->m_TickTimer_ms += dt_ms;
	const float rowTick_ms = playfieldGetRowTick_ms(pf);
	bool applyGravity = wasHardDrop || pf->m_TickTimer_ms >= rowTick_ms;
	if (applyGravity) {
		if (!wasHardDrop) {
			pf->m_TickTimer_ms -= rowTick_ms;
		}

		// Apply gravity to current piece
		if (!playfieldPieceTranslate(pf, &pf->m_CurPiece, 0, -1)) {
			// Place piece on board
			const int32_t posx = pf->m_CurPiece.m_PosX;
			const int32_t posy = pf->m_CurPiece.m_PosY;
			const piece_shape_t* shape = &kPieceShapes[pf->m_CurPiece.m_Kind][pf->m_CurPiece.m_Orientation];
			for (int32_t py = 0; py < 4; ++py) {
				const uint8_t bitmask = shape->m_Bitmask[py];
				if (bitmask) {
					pf->m_TileFilled[posy + py] |= (shape->m_Bitmask[py] << posx);
	
					for (int32_t px = 0; px < 4; ++px) {
						if (shape->m_Bitmask[py] & (1u << px)) {
							pf->m_TilePiece[(posx - PLAYFIELD_ORIGIN_X + px) + (posy - PLAYFIELD_ORIGIN_Y + py) * PLAYFIELD_WIDTH] = (uint8_t)pf->m_CurPiece.m_Kind;
						}
					}
				}
			}

			// Check for complete rows
			{
				uint32_t numRowsCleared = 0;
				uint32_t firstRow = PLAYFIELD_ORIGIN_Y;
loop:
				for (uint32_t y = firstRow; y <= PLAYFIELD_HEIGHT; ++y) {
					if (pf->m_TileFilled[y] == 0xFFFF) {
						// Row is complete. Remove and move the rest down.
						++numRowsCleared;

						memmove(&pf->m_TileFilled[y], &pf->m_TileFilled[y + 1], sizeof(uint16_t) * (PLAYFIELD_HEIGHT + 3 - y - 1));
						memmove(&pf->m_TilePiece[(y - PLAYFIELD_ORIGIN_Y) * PLAYFIELD_WIDTH], &pf->m_TilePiece[(y + 1 - PLAYFIELD_ORIGIN_Y) * PLAYFIELD_WIDTH], sizeof(uint8_t) * PLAYFIELD_WIDTH * (PLAYFIELD_HEIGHT - (y - PLAYFIELD_ORIGIN_Y) - 1));
						firstRow = y;
						goto loop;
					}
				}

				if (numRowsCleared) {
					++pf->m_NumClears;
					pf->m_TotalLinesCleared += numRowsCleared;

					pf->m_Score += kClearLineScore[numRowsCleared] * pf->m_Level + (pf->m_NumClears - 1) * 50;
					if (numRowsCleared == 4) {
						++pf->m_NumTetris;
						if (pf->m_NumTetris != 0) {
							pf->m_Score += kClearLineScore[4] / 2;
						}
					} else {
						pf->m_NumTetris = 0;
					}

					pf->m_Level = (pf->m_TotalLinesCleared / 20) + 1;
				} else {
					pf->m_NumClears = 0;
					pf->m_NumTetris = 0;
				}				
			}

			// Move on to next piece
			if (!pf->m_RemainingBagPieces) {
				playfieldGenPieceBag(pf);
			}

			pf->m_RemainingBagPieces--;
			pf->m_CurPiece.m_Kind = pf->m_PieceBag[pf->m_RemainingBagPieces];
			pf->m_CurPiece.m_PosX = PLAYFIELD_ORIGIN_X + PLAYFIELD_WIDTH / 2 - 2;
			pf->m_CurPiece.m_PosY = PLAYFIELD_ORIGIN_Y + PLAYFIELD_HEIGHT - 2;
			pf->m_CurPiece.m_Orientation = 0;
			if (!playfieldPieceTranslate(pf, &pf->m_CurPiece, 0, 0)) {
				// TODO: Game Over
				exit(1);
			}
		}
	}

	for (uint32_t y = 0; y < PLAYFIELD_HEIGHT; ++y) {
		const uint16_t bitmask = pf->m_TileFilled[PLAYFIELD_ORIGIN_Y + y];
		for (uint32_t x = 0; x < PLAYFIELD_WIDTH; ++x) {
			const piece_kind piece = (piece_kind)pf->m_TilePiece[x + y * PLAYFIELD_WIDTH];
			playfieldSetColor(pf, x, y, kPieceColor[piece]);
		}
	}

	// Draw ghost piece.
	{
		for (int32_t y = pf->m_CurPiece.m_PosY; y > -3; --y) {
			if (!playfieldCanPlacePieceAt(pf, pf->m_CurPiece.m_Kind, pf->m_CurPiece.m_Orientation, pf->m_CurPiece.m_PosX, y)) {
				if (y + 1 != pf->m_CurPiece.m_PosY) {
					int32_t x = pf->m_CurPiece.m_PosX - PLAYFIELD_ORIGIN_X;
					y -= PLAYFIELD_ORIGIN_Y - 1;

					uint32_t color = kPieceColor[pf->m_CurPiece.m_Kind];
					color &= ~CANVAS_COLOR_ALPHA_Msk;
					color |= (64 << CANVAS_COLOR_ALPHA_Pos) & CANVAS_COLOR_ALPHA_Msk;

					const piece_shape_t* shape = &kPieceShapes[pf->m_CurPiece.m_Kind][pf->m_CurPiece.m_Orientation];
					for (int32_t i = 0; i < 4; ++i) {
						const uint8_t bitmask = shape->m_Bitmask[i];
						if (bitmask != 0) {
							for (int32_t j = 0; j < 4; ++j) {
								if ((bitmask & (1u << j)) != 0) {
									playfieldSetColor(pf, x + j, y + i, color);
								}
							}
						}
					}
				}

				break;
			}
		}
	}

	// Draw the current piece.
	{
		int32_t x = pf->m_CurPiece.m_PosX - PLAYFIELD_ORIGIN_X;
		int32_t y = pf->m_CurPiece.m_PosY - PLAYFIELD_ORIGIN_Y;
		const piece_shape_t* shape = &kPieceShapes[pf->m_CurPiece.m_Kind][pf->m_CurPiece.m_Orientation];
		for (int32_t i = 0; i < 4; ++i) {
			const uint8_t bitmask = shape->m_Bitmask[i];
			if (bitmask != 0) {
				for (int32_t j = 0; j < 4; ++j) {
					if ((bitmask & (1u << j)) != 0) {
						playfieldSetColor(pf, x + j, y + i, kPieceColor[pf->m_CurPiece.m_Kind]);
					}
				}
			}
		}
	}
}

static bool playfieldCanPlacePieceAt(playfield_t* pf, piece_kind piece, uint32_t orientation, int32_t x, int32_t y)
{
	if (x < 0) {
		return false;
	}

	const piece_shape_t* shape = &kPieceShapes[piece][orientation];
	for (int32_t py = 0; py < 4; ++py) {
		const uint8_t pieceRowMask = shape->m_Bitmask[py];
		if (pieceRowMask != 0) {
			if (y + py < 0 || pf->m_TileFilled[y + py] & (pieceRowMask << x)) {
				return false;
			}
		}
	}

	return true;
}

static bool playfieldPieceTranslate(playfield_t* pf, piece_t* piece, int32_t dx, int32_t dy)
{
	int32_t x = piece->m_PosX + dx;
	int32_t y = piece->m_PosY + dy;

	if (!playfieldCanPlacePieceAt(pf, piece->m_Kind, piece->m_Orientation, x, y)) {
		return false;
	}
	
	piece->m_PosX += dx;
	piece->m_PosY += dy;

	return true;
}

typedef struct offset_t
{
	int8_t m_dX;
	int8_t m_dY;
} offset_t;

static const offset_t kCommonWallKickOffsets[4][4][5] = {
	[0] = {
		[1] = {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}, // 0 -> R
		[3] = {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},    // 0 -> L
	},
	[1] = {
		[0] = {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},     // R -> 0
		[2] = {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},     // R -> 2
	},
	[2] = {
		[1] = {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}, // 2 -> R
		[3] = {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},    // 2 -> L
	},
	[3] = {
		[0] = {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},  // L -> 0
		[2] = {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},  // L -> 2
	},
};

static const offset_t kIWallKickOffsets[4][4][5] = {
	[0] = {
		[1] = {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},   // 0 -> R
		[3] = {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},   // 0 -> L
	},
	[1] = {
		[0] = {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},   // R -> 0
		[2] = {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},   // R -> 2
	},
	[2] = {
		[1] = {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},   // 2 -> R
		[3] = {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},   // 2 -> L
	},
	[3] = {
		[0] = {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},   // L -> 0
		[2] = {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},   // L -> 2
	},
};

static bool playfieldPieceRotate(playfield_t* pf, piece_t* piece, int32_t delta)
{
	uint32_t orient = (piece->m_Orientation + (uint32_t)delta) & 3;

	bool found = false;
	if (piece->m_Kind == PIECE_I) {
		for (uint32_t i = 0; i < 5; ++i) {
			const offset_t* offset = &kIWallKickOffsets[piece->m_Orientation][orient][i];
			const int32_t x = piece->m_PosX + offset->m_dX;
			const int32_t y = piece->m_PosY + offset->m_dY;
			if (playfieldCanPlacePieceAt(pf, piece->m_Kind, orient, x, y)) {
				piece->m_PosX = x;
				piece->m_PosY = y;
				found = true;
				break;
			}
		}
	} else {
		for (uint32_t i = 0; i < 5; ++i) {
			const offset_t* offset = &kCommonWallKickOffsets[piece->m_Orientation][orient][i];
			const int32_t x = piece->m_PosX + offset->m_dX;
			const int32_t y = piece->m_PosY + offset->m_dY;
			if (playfieldCanPlacePieceAt(pf, piece->m_Kind, orient, x, y)) {
				piece->m_PosX = x;
				piece->m_PosY = y;
				found = true;
				break;
			}
		}
	}

	if (!found) {
		return false;
	}

	piece->m_Orientation = orient;

	return true;
}

static void canvasDrawImage(canvas_t* canvas, float x, float y, float w, float h, image_t* img)
{
	const float quadPos[] = {
		x, y,
		x + w, y,
		x + w, y + h,
		x, y + h
	};
	const int16_t quadUV[] = {
		0, 0,
		INT16_MAX, 0,
		INT16_MAX, INT16_MAX,
		0, INT16_MAX
	};
	const uint32_t quadColor = CANVAS_COLOR(255, 255, 255, 255);
	const uint16_t quadIndices[] = {
		0, 1, 2,
		0, 2, 3
	};
	canvasIndexedTriList(canvas, quadPos, quadUV, 4, &quadColor, 1, quadIndices, 6, img);
}
