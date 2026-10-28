#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct image_t image_t;

#define CANVAS_COLOR_RED_Pos     0
#define CANVAS_COLOR_RED_Msk     (0xFFu << CANVAS_COLOR_RED_Pos)
#define CANVAS_COLOR_GREEN_Pos   8
#define CANVAS_COLOR_GREEN_Msk   (0xFFu << CANVAS_COLOR_GREEN_Pos)
#define CANVAS_COLOR_BLUE_Pos    16
#define CANVAS_COLOR_BLUE_Msk    (0xFFu << CANVAS_COLOR_BLUE_Pos)
#define CANVAS_COLOR_ALPHA_Pos   24
#define CANVAS_COLOR_ALPHA_Msk   (0xFFu << CANVAS_COLOR_ALPHA_Pos)
#define CANVAS_COLOR_RGB_Msk     (CANVAS_COLOR_RED_Msk | CANVAS_COLOR_GREEN_Msk | CANVAS_COLOR_BLUE_Msk)

#define CANVAS_COLOR(r, g, b, a) (0 \
	| (((uint32_t)(r) << CANVAS_COLOR_RED_Pos) & CANVAS_COLOR_RED_Msk) \
	| (((uint32_t)(g) << CANVAS_COLOR_GREEN_Pos) & CANVAS_COLOR_GREEN_Msk) \
	| (((uint32_t)(b) << CANVAS_COLOR_BLUE_Pos) & CANVAS_COLOR_BLUE_Msk) \
	| (((uint32_t)(a) << CANVAS_COLOR_ALPHA_Pos) & CANVAS_COLOR_ALPHA_Msk) \
)

#define CANVAS_COLOR_BLACK       CANVAS_COLOR(0, 0, 0, 255)
#define CANVAS_COLOR_RED         CANVAS_COLOR(255, 0, 0, 255)
#define CANVAS_COLOR_GREEN       CANVAS_COLOR(0, 255, 0, 255)
#define CANVAS_COLOR_BLUE        CANVAS_COLOR(0, 0, 255, 255)
#define CANVAS_COLOR_TRANSPARENT CANVAS_COLOR(0, 0, 0, 0)

#define CANVAS_STROKE_FLAGS_LINE_JOIN_Pos   0
#define CANVAS_STROKE_FLAGS_LINE_JOIN_Msk   (0x03u << CANVAS_STROKE_FLAGS_LINE_JOIN_Pos)
#define CANVAS_STROKE_FLAGS_LINE_CAP_Pos    2
#define CANVAS_STROKE_FLAGS_LINE_CAP_Msk    (0x03u << CANVAS_STROKE_FLAGS_LINE_CAP_Pos)
#define CANVAS_STROKE_FLAGS_AA_Pos          4
#define CANVAS_STROKE_FLAGS_AA_Msk          (0x01u << CANVAS_STROKE_FLAGS_AA_Pos)
#define CANVAS_STROKE_FLAGS_FIXED_WIDTH_Pos 5
#define CANVAS_STROKE_FLAGS_FIXED_WIDTH_Msk (0x01u << CANVAS_STROKE_FLAGS_FIXED_WIDTH_Pos)
#define CANVAS_STROKE_FLAGS(cap, join, aa) (0 \
	| (((uint32_t)(join) << CANVAS_STROKE_FLAGS_LINE_JOIN_Pos) & CANVAS_STROKE_FLAGS_LINE_JOIN_Msk) \
	| (((uint32_t)(cap) << CANVAS_STROKE_FLAGS_LINE_CAP_Pos) & CANVAS_STROKE_FLAGS_LINE_CAP_Msk) \
	| (((uint32_t)(aa) << CANVAS_STROKE_FLAGS_AA_Pos) & CANVAS_STROKE_FLAGS_AA_Msk) \
)

#define CANVAS_FILL_FLAGS_PATH_TYPE_Pos 0
#define CANVAS_FILL_FLAGS_PATH_TYPE_Msk (0x01u << CANVAS_FILL_FLAGS_PATH_TYPE_Pos)
#define CANVAS_FILL_FLAGS_FILL_RULE_Pos 1
#define CANVAS_FILL_FLAGS_FILL_RULE_Msk (0x01u << CANVAS_FILL_FLAGS_FILL_RULE_Pos)
#define CANVAS_FILL_FLAGS_AA_Pos        2
#define CANVAS_FILL_FLAGS_AA_Msk        (0x01u << CANVAS_FILL_FLAGS_AA_Pos)
#define CANVAS_FILL_FLAGS(type, rule, aa) (0 \
	| (((uint32_t)(type) << CANVAS_FILL_FLAGS_PATH_TYPE_Pos) & CANVAS_FILL_FLAGS_PATH_TYPE_Msk) \
	| (((uint32_t)(rule) << CANVAS_FILL_FLAGS_FILL_RULE_Pos) & CANVAS_FILL_FLAGS_FILL_RULE_Msk) \
	| (((uint32_t)(aa) << CANVAS_FILL_FLAGS_AA_Pos) & CANVAS_FILL_FLAGS_AA_Msk) \
)

typedef enum canvas_line_cap
{
	CANVAS_LINE_CAP_BUTT = 0,
	CANVAS_LINE_CAP_ROUND = 1,
	CANVAS_LINE_CAP_SQUARE = 2,
} canvas_line_cap;

typedef enum canvas_line_join
{
	CANVAS_LINE_JOIN_MITER = 0,
	CANVAS_LINE_JOIN_ROUND = 1,
	CANVAS_LINE_JOIN_BEVEL = 2
} canvas_line_join;

typedef enum canvas_path_type
{
	CANVAS_PATH_TYPE_CONVEX = 0,
	CANVAS_PATH_TYPE_CONCAVE = 1,
} canvas_path_type;

typedef enum canvas_fill_rule
{
	CANVAS_FILL_RULE_NON_ZERO = 0,
	CANVAS_FILL_RULE_EVEN_ODD = 1,
} canvas_fill_rule;

typedef enum canvas_winding
{
	CANVAS_WINDING_CCW = 0,
	CANVAS_WINDING_CW = 1,
} canvas_winding;

// Stroke combinations
#define CANVAS_STROKE_FLAGS_BUTT_MITER        CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_BUTT, CANVAS_LINE_JOIN_MITER, 0)
#define CANVAS_STROKE_FLAGS_BUTT_ROUND        CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_BUTT, CANVAS_LINE_JOIN_ROUND, 0)
#define CANVAS_STROKE_FLAGS_BUTT_BEVEL        CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_BUTT, CANVAS_LINE_JOIN_BEVEL, 0)
#define CANVAS_STROKE_FLAGS_ROUND_MITER       CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_ROUND, CANVAS_LINE_JOIN_MITER, 0)
#define CANVAS_STROKE_FLAGS_ROUND_ROUND       CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_ROUND, CANVAS_LINE_JOIN_ROUND, 0)
#define CANVAS_STROKE_FLAGS_ROUND_BEVEL       CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_ROUND, CANVAS_LINE_JOIN_BEVEL, 0)
#define CANVAS_STROKE_FLAGS_SQUARE_MITER      CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_SQUARE, CANVAS_LINE_JOIN_MITER, 0)
#define CANVAS_STROKE_FLAGS_SQUARE_ROUND      CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_SQUARE, CANVAS_LINE_JOIN_ROUND, 0)
#define CANVAS_STROKE_FLAGS_SQUARE_BEVEL      CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_SQUARE, CANVAS_LINE_JOIN_BEVEL, 0)
#define CANVAS_STROKE_FLAGS_BUTT_MITER_AA     CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_BUTT, CANVAS_LINE_JOIN_MITER, 1)
#define CANVAS_STROKE_FLAGS_BUTT_ROUND_AA     CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_BUTT, CANVAS_LINE_JOIN_ROUND, 1)
#define CANVAS_STROKE_FLAGS_BUTT_BEVEL_AA     CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_BUTT, CANVAS_LINE_JOIN_BEVEL, 1)
#define CANVAS_STROKE_FLAGS_ROUND_MITER_AA    CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_ROUND, CANVAS_LINE_JOIN_MITER, 1)
#define CANVAS_STROKE_FLAGS_ROUND_ROUND_AA    CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_ROUND, CANVAS_LINE_JOIN_ROUND, 1)
#define CANVAS_STROKE_FLAGS_ROUND_BEVEL_AA    CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_ROUND, CANVAS_LINE_JOIN_BEVEL, 1)
#define CANVAS_STROKE_FLAGS_SQUARE_MITER_AA   CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_SQUARE, CANVAS_LINE_JOIN_MITER, 1)
#define CANVAS_STROKE_FLAGS_SQUARE_ROUND_AA   CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_SQUARE, CANVAS_LINE_JOIN_ROUND, 1)
#define CANVAS_STROKE_FLAGS_SQUARE_BEVEL_AA   CANVAS_STROKE_FLAGS(CANVAS_LINE_CAP_SQUARE, CANVAS_LINE_JOIN_BEVEL, 1)
#define CANVAS_STROKE_FLAGS_FIXED_WIDTH       CANVAS_STROKE_FLAGS_FIXED_WIDTH_Msk // NOTE: Scale independent stroke width

// Fill combinations
#define CANVAS_FILL_FLAGS_CONVEX              CANVAS_FILL_FLAGS(CANVAS_PATH_TYPE_CONVEX, CANVAS_FILL_RULE_NON_ZERO, 0)
#define CANVAS_FILL_FLAGS_CONVEX_AA           CANVAS_FILL_FLAGS(CANVAS_PATH_TYPE_CONVEX, CANVAS_FILL_RULE_NON_ZERO, 1)
#define CANVAS_FILL_FLAGS_CONCAVE_NON_ZERO    CANVAS_FILL_FLAGS(CANVAS_PATH_TYPE_CONCAVE, CANVAS_FILL_RULE_NON_ZERO, 0)
#define CANVAS_FILL_FLAGS_CONCAVE_EVEN_ODD    CANVAS_FILL_FLAGS(CANVAS_PATH_TYPE_CONCAVE, CANVAS_FILL_RULE_EVEN_ODD, 0)
#define CANVAS_FILL_FLAGS_CONCAVE_NON_ZERO_AA CANVAS_FILL_FLAGS(CANVAS_PATH_TYPE_CONCAVE, CANVAS_FILL_RULE_NON_ZERO, 1)
#define CANVAS_FILL_FLAGS_CONCAVE_EVEN_ODD_AA CANVAS_FILL_FLAGS(CANVAS_PATH_TYPE_CONCAVE, CANVAS_FILL_RULE_EVEN_ODD, 1)

typedef enum canvas_mouse_button
{
	CANVAS_MOUSE_BUTTON_LEFT = 0,
	CANVAS_MOUSE_BUTTON_RIGHT = 1,
	CANVAS_MOUSE_BUTTON_MIDDLE = 2,
} canvas_mouse_button;

#define CANVAS_FLAGS_NONE          0
#define CANVAS_FLAGS_RESIZABLE_Pos 0
#define CANVAS_FLAGS_RESIZABLE_Msk (1u << CANVAS_FLAGS_RESIZABLE_Pos)

// NOTE: These should match UI's jx_gui_font_type.
typedef enum canvas_font_type
{
	CANVAS_FONT_TYPE_PROP_REGULAR = 0,
	CANVAS_FONT_TYPE_PROP_BOLD,
	CANVAS_FONT_TYPE_MONO_REGULAR,
	CANVAS_FONT_TYPE_MONO_BOLD,
	CANVAS_FONT_TYPE_ICON,
} canvas_font_type;

typedef enum canvas_transform_order
{
	CANVAS_TRANSFORM_ORDER_PRE = 0,
	CANVAS_TRANSFORM_ORDER_POST = 1,
} canvas_transform_order;

typedef enum canvas_key
{
	CANVAS_KEY_SPACE = 0,
	CANVAS_KEY_APOSTROPHE,
	CANVAS_KEY_COMMA,
	CANVAS_KEY_MINUS,
	CANVAS_KEY_PERIOD,
	CANVAS_KEY_SLASH,
	CANVAS_KEY_0,
	CANVAS_KEY_1,
	CANVAS_KEY_2,
	CANVAS_KEY_3,
	CANVAS_KEY_4,
	CANVAS_KEY_5,
	CANVAS_KEY_6,
	CANVAS_KEY_7,
	CANVAS_KEY_8,
	CANVAS_KEY_9,
	CANVAS_KEY_SEMICOLON,
	CANVAS_KEY_EQUAL,
	CANVAS_KEY_A,
	CANVAS_KEY_B,
	CANVAS_KEY_C,
	CANVAS_KEY_D,
	CANVAS_KEY_E,
	CANVAS_KEY_F,
	CANVAS_KEY_G,
	CANVAS_KEY_H,
	CANVAS_KEY_I,
	CANVAS_KEY_J,
	CANVAS_KEY_K,
	CANVAS_KEY_L,
	CANVAS_KEY_M,
	CANVAS_KEY_N,
	CANVAS_KEY_O,
	CANVAS_KEY_P,
	CANVAS_KEY_Q,
	CANVAS_KEY_R,
	CANVAS_KEY_S,
	CANVAS_KEY_T,
	CANVAS_KEY_U,
	CANVAS_KEY_V,
	CANVAS_KEY_W,
	CANVAS_KEY_X,
	CANVAS_KEY_Y,
	CANVAS_KEY_Z,
	CANVAS_KEY_LEFT_BRACKET,
	CANVAS_KEY_BACKSLASH,
	CANVAS_KEY_RIGHT_BRACKET,
	CANVAS_KEY_GRAVE_ACCENT,
	CANVAS_KEY_ESCAPE,
	CANVAS_KEY_ENTER,
	CANVAS_KEY_TAB,
	CANVAS_KEY_BACKSPACE,
	CANVAS_KEY_INSERT,
	CANVAS_KEY_DELETE,
	CANVAS_KEY_RIGHT,
	CANVAS_KEY_LEFT,
	CANVAS_KEY_DOWN,
	CANVAS_KEY_UP,
	CANVAS_KEY_PAGE_UP,
	CANVAS_KEY_PAGE_DOWN,
	CANVAS_KEY_HOME,
	CANVAS_KEY_END,
	CANVAS_KEY_F1,
	CANVAS_KEY_F2,
	CANVAS_KEY_F3,
	CANVAS_KEY_F4,
	CANVAS_KEY_F5,
	CANVAS_KEY_F6,
	CANVAS_KEY_F7,
	CANVAS_KEY_F8,
	CANVAS_KEY_F9,
	CANVAS_KEY_F10,
	CANVAS_KEY_F11,
	CANVAS_KEY_F12,
	CANVAS_KEY_KP_0,
	CANVAS_KEY_KP_1,
	CANVAS_KEY_KP_2,
	CANVAS_KEY_KP_3,
	CANVAS_KEY_KP_4,
	CANVAS_KEY_KP_5,
	CANVAS_KEY_KP_6,
	CANVAS_KEY_KP_7,
	CANVAS_KEY_KP_8,
	CANVAS_KEY_KP_9,
	CANVAS_KEY_KP_DECIMAL,
	CANVAS_KEY_KP_DIVIDE,
	CANVAS_KEY_KP_MULTIPLY,
	CANVAS_KEY_KP_SUBTRACT,
	CANVAS_KEY_KP_ADD,
	CANVAS_KEY_KP_ENTER,
	CANVAS_KEY_KP_EQUAL,
	CANVAS_KEY_LEFT_SHIFT,
	CANVAS_KEY_LEFT_CONTROL,
	CANVAS_KEY_LEFT_ALT,
	CANVAS_KEY_LEFT_SUPER,
	CANVAS_KEY_RIGHT_SHIFT,
	CANVAS_KEY_RIGHT_CONTROL,
	CANVAS_KEY_RIGHT_ALT,
	CANVAS_KEY_RIGHT_SUPER,

	CANVAS_KEY_COUNT,
} canvas_key;

typedef struct canvas_t canvas_t;

canvas_t* canvasCreate(uint32_t width, uint32_t height, uint32_t flags);
void canvasDestroy(canvas_t* canvas);
bool canvasIsOpen(canvas_t* canvas);
void canvasGetSize(canvas_t* canvas, uint32_t* width, uint32_t* height);
void canvasGetMousePos(canvas_t* canvas, int16_t* mx, int16_t* my);
int16_t canvasGetMouseScroll(canvas_t* canvas);
bool canvasIsMouseButtonDown(canvas_t* canvas, canvas_mouse_button mb);
bool canvasIsMouseButtonUp(canvas_t* canvas, canvas_mouse_button mb);
bool canvasHasMouseButtonWentDown(canvas_t* canvas, canvas_mouse_button mb);
bool canvasHasMouseButtonWentUp(canvas_t *canvas, canvas_mouse_button mb);
bool canvasIsKeyDown(canvas_t *canvas, canvas_key key);
bool canvasIsKeyUp(canvas_t *canvas, canvas_key key);
bool canvasIsKeyPressed(canvas_t *canvas, canvas_key key);
void canvasClear(canvas_t* canvas, uint32_t colorRGBA);
void canvasDrawText(canvas_t* canvas, float x, float y, float fontSize, canvas_font_type fontType, const char* str, uint32_t colorRGBA);
void canvasSwapBuffers(canvas_t* canvas);

void canvasBeginPath(canvas_t* canvas);
void canvasMoveTo(canvas_t* canvas, float x, float y);
void canvasLineTo(canvas_t* canvas, float x, float y);
void canvasCubicTo(canvas_t* canvas, float c1x, float c1y, float c2x, float c2y, float x, float y);
void canvasQuadraticTo(canvas_t* canvas, float cx, float cy, float x, float y);
void canvasArcTo(canvas_t* canvas, float x1, float y1, float x2, float y2, float r);
void canvasArc(canvas_t* canvas, float cx, float cy, float r, float a0, float a1, canvas_winding dir);
void canvasRect(canvas_t* canvas, float x, float y, float w, float h);
void canvasRoundedRect(canvas_t* canvas, float x, float y, float w, float h, float r);
void canvasCircle(canvas_t* canvas, float cx, float cy, float r);
void canvasEllipse(canvas_t* canvas, float cx, float cy, float rx, float ry);
void canvasPolyline(canvas_t* canvas, const float* coords, uint32_t numPoints);
void canvasClosePath(canvas_t* canvas);
void canvasFillPath(canvas_t* canvas, uint32_t color, uint32_t fillFlags);
void canvasStrokePath(canvas_t* canvas, uint32_t color, float strokeWidth, uint32_t strokeFlags);
void canvasIndexedTriList(canvas_t* canvas, const float* pos, const int16_t* uv, uint32_t numVertices, const uint32_t* colors, uint32_t numColors, const uint16_t* indices, uint32_t numIndices, image_t* img);

void canvasPushState(canvas_t* canvas);
void canvasPopState(canvas_t* canvas);
void canvasTransformIdentity(canvas_t* canvas);
void canvasTransformScale(canvas_t* canvas, float x, float y);
void canvasTransformTranslate(canvas_t* canvas, float x, float y);
void canvasTransformRotate(canvas_t* canvas, float ang_rad);
void canvasTransformMult(canvas_t* canvas, const float* mtx, canvas_transform_order order);

#endif // CANVAS_H
