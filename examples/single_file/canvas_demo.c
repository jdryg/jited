#include <jitsheet/canvas.h>
#include <jitsheet/os.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int32_t main(void)
{
	int64_t startTime = os_timeNow();

	// Create canvas
	canvas_t* canvas = canvasCreate(256, 256, CANVAS_FLAGS_NONE);

	// While the canvas is open
	while (canvasIsOpen(canvas)) {
		const int64_t now = os_timeNow();
		const float dt = (float)os_timeConvertTo(os_timeDiff(now, startTime), OS_TIME_UNITS_MS);
		startTime = now;

		uint32_t canvasWidth, canvasHeight;
		canvasGetSize(canvas, &canvasWidth, &canvasHeight);

		// Draw rectangle
		canvasClear(canvas, CANVAS_COLOR(0, 0, 0, 255));
		canvasBeginPath(canvas);
		canvasRect(canvas, 20.0f, 20.0f, (float)canvasWidth - 40.0f, (float)canvasHeight - 40.0f);
		canvasFillPath(canvas, canvasIsMouseButtonDown(canvas, CANVAS_MOUSE_BUTTON_LEFT) ? CANVAS_COLOR_BLUE : CANVAS_COLOR_RED, CANVAS_FILL_FLAGS_CONVEX);
		canvasStrokePath(canvas, CANVAS_COLOR_GREEN, 2.0f, CANVAS_STROKE_FLAGS_BUTT_MITER_AA);

		// Draw triangle
		canvasBeginPath(canvas);
		canvasMoveTo(canvas, 50.0f, 50.0f);
		canvasLineTo(canvas, 50.0f, 100.0f);
		canvasLineTo(canvas, 100.0f, 75.0f);
		canvasClosePath(canvas);
		canvasFillPath(canvas, CANVAS_COLOR(255, 255, 255, 255), CANVAS_FILL_FLAGS_CONVEX_AA);

		// Draw mouse cursor
		int16_t mx, my;
		canvasGetMousePos(canvas, &mx, &my);
		canvasBeginPath(canvas);
		canvasMoveTo(canvas, (float)mx, (float)my - 5.0f);
		canvasLineTo(canvas, (float)mx, (float)my + 5.0f);
		canvasMoveTo(canvas, (float)mx - 5.0f, (float)my);
		canvasLineTo(canvas, (float)mx + 5.0f, (float)my);
		canvasStrokePath(canvas, CANVAS_COLOR(255, 255, 255, 255), 1.0f, CANVAS_STROKE_FLAGS_BUTT_MITER_AA);

		// Draw frame time
		char str[256];
		snprintf(str, 256, "Frame: %.1fms", dt);
		canvasDrawText(canvas, 0.0f, (float)canvasHeight, 12.0f, CANVAS_FONT_TYPE_MONO_REGULAR, str, CANVAS_COLOR(255, 255, 255, 255));

		canvasSwapBuffers(canvas);
	}

	canvasDestroy(canvas);

	return 0;
}
