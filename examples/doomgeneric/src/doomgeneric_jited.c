#include "doomkeys.h"
#include "doomgeneric.h"
#include <string.h> // memset
#include <jitsheet/canvas.h>
#include <jitsheet/image.h>
#include <jitsheet/os.h>

#include <stdio.h>
#include <Windows.h> // Sleep()/GetTickCount()

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static canvas_t* s_Canvas = NULL;
static image_t* s_Image = NULL;
static uint32_t* s_Pixels = NULL;
static int64_t s_FrameStartTime = 0;
static bool s_KeyWasDown[CANVAS_KEY_COUNT];

void DG_Init()
{
	memset(s_KeyQueue, 0, KEYQUEUE_SIZE * sizeof(unsigned short));
	memset(s_KeyWasDown, 0, sizeof(s_KeyWasDown));
}

static unsigned char convertToDoomKey(canvas_key key)
{
	switch (key) {
	case CANVAS_KEY_ENTER:
	case CANVAS_KEY_KP_ENTER:      return KEY_ENTER;
	case CANVAS_KEY_ESCAPE:        return KEY_ESCAPE;
	case CANVAS_KEY_TAB:           return KEY_TAB;
	case CANVAS_KEY_LEFT:          return KEY_LEFTARROW;
	case CANVAS_KEY_RIGHT:         return KEY_RIGHTARROW;
	case CANVAS_KEY_UP:            return KEY_UPARROW;
	case CANVAS_KEY_DOWN:          return KEY_DOWNARROW;
	case CANVAS_KEY_LEFT_CONTROL:
	case CANVAS_KEY_RIGHT_CONTROL: return KEY_FIRE;
	case CANVAS_KEY_SPACE:         return KEY_USE;
	case CANVAS_KEY_LEFT_SHIFT:
	case CANVAS_KEY_RIGHT_SHIFT:   return KEY_RSHIFT;
	case CANVAS_KEY_LEFT_ALT:
	case CANVAS_KEY_RIGHT_ALT:     return KEY_LALT;
	case CANVAS_KEY_BACKSPACE:     return KEY_BACKSPACE;
	case CANVAS_KEY_EQUAL:         return KEY_EQUALS;
	case CANVAS_KEY_MINUS:         return KEY_MINUS;
	case CANVAS_KEY_F1:            return KEY_F1;
	case CANVAS_KEY_F2:            return KEY_F2;
	case CANVAS_KEY_F3:            return KEY_F3;
	case CANVAS_KEY_F4:            return KEY_F4;
	case CANVAS_KEY_F5:            return KEY_F5;
	case CANVAS_KEY_F6:            return KEY_F6;
	case CANVAS_KEY_F7:            return KEY_F7;
	case CANVAS_KEY_F8:            return KEY_F8;
	case CANVAS_KEY_F9:            return KEY_F9;
	case CANVAS_KEY_F10:           return KEY_F10;
	case CANVAS_KEY_F11:           return KEY_F11;
	case CANVAS_KEY_F12:           return KEY_F12;
	default:
		if (key >= CANVAS_KEY_A && key <= CANVAS_KEY_Z) {
			return (unsigned char)('a' + (key - CANVAS_KEY_A));
		} else if (key >= CANVAS_KEY_0 && key <= CANVAS_KEY_9) {
			return (unsigned char)('0' + (key - CANVAS_KEY_0));
		}
		break;
	}

	return 0;
}

static void addKeyToQueue(int pressed, unsigned char doomKey)
{
	const unsigned short keyData = (unsigned short)((pressed << 8) | doomKey);
	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex = (s_KeyQueueWriteIndex + 1) % KEYQUEUE_SIZE;
}

// Diffs the canvas' current keyboard state against the state seen by the
// previous call and turns transitions into key press/release events.
static void pollKeyboardEvents(void)
{
	for (uint32_t iKey = 0; iKey < CANVAS_KEY_COUNT; ++iKey) {
		const bool isDown = canvasIsKeyDown(s_Canvas, (canvas_key)iKey);
		if (isDown != s_KeyWasDown[iKey]) {
			s_KeyWasDown[iKey] = isDown;

			const unsigned char doomKey = convertToDoomKey((canvas_key)iKey);
			if (doomKey != 0) {
				addKeyToQueue(isDown ? 1 : 0, doomKey);
			}
		}
	}
}

void DG_DrawFrame()
{
	const int64_t now = os_timeNow();
	const float dt = (float)os_timeConvertTo(os_timeDiff(now, s_FrameStartTime), OS_TIME_UNITS_MS);
	s_FrameStartTime = now;

	const uint8_t* src = (const uint8_t*)DG_ScreenBuffer;
	uint8_t* dst = (uint8_t*)s_Pixels;
	for (uint32_t i = 0;i < DOOMGENERIC_RESX * DOOMGENERIC_RESY;++i) {
		dst[0] = src[2];
		dst[1] = src[1];
		dst[2] = src[0];
		dst[3] = 255;
		dst += 4;
		src += 4;
	}
	imageSetRect(s_Image, 0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, s_Pixels);

	uint32_t canvasWidth, canvasHeight;
	canvasGetSize(s_Canvas, &canvasWidth, &canvasHeight);

	const float quadPos[] = {
		0.0f, 0.0f,
		(float)canvasWidth, 0.0f,
		(float)canvasWidth, (float)canvasHeight,
		0.0f, (float)canvasHeight
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
	canvasIndexedTriList(s_Canvas, quadPos, quadUV, 4, &quadColor, 1, quadIndices, 6, s_Image);
	
	// Draw frame time
	char str[256];
	snprintf(str, 256, "Frame: %.1fms", dt);
	canvasDrawText(s_Canvas, 0.0f, 14.0f, 12.0f, CANVAS_FONT_TYPE_MONO_REGULAR, str, CANVAS_COLOR(255, 255, 255, 255));

	canvasSwapBuffers(s_Canvas);
}

void DG_SleepMs(uint32_t ms)
{
	Sleep(ms);
}

uint32_t DG_GetTicksMs()
{
	return GetTickCount();
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	pollKeyboardEvents();

	if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex) {
		// Key queue is empty
		return 0;
	}

	const unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
	s_KeyQueueReadIndex = (s_KeyQueueReadIndex + 1) % KEYQUEUE_SIZE;

	*pressed = keyData >> 8;
	*doomKey = keyData & 0xFF;

	return 1;
}

void DG_SetWindowTitle(const char * title)
{
}

int main(void)
{
	s_Pixels = (uint32_t*)malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);
	s_Canvas = canvasCreate(DOOMGENERIC_RESX, DOOMGENERIC_RESY, CANVAS_FLAGS_NONE);
	s_Image = imageCreate(DOOMGENERIC_RESX, DOOMGENERIC_RESY, NULL);

	char* argv[3] = { (char*)".\\doomgeneric.exe", (char*)"-timedemo", (char*)"demo3" };
	doomgeneric_Create(3, &argv[0]);

	s_FrameStartTime = os_timeNow();
    while (canvasIsOpen(s_Canvas)) {
        doomgeneric_Tick();
    }

    return 0;
}
