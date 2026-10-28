#include <jitsheet/canvas.h>
#include <jitsheet/os.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 256

int32_t main(void)
{
	const float w = 50.0f;
	const float h = 40.0f;
	float x = 0.0f;
	float y = 0.0f;
	float dirX = 50.0f;
	float dirY = 50.0f;

	int64_t startTime = os_timeNow();

	canvas_t* canvas = canvasCreate(CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_FLAGS_RESIZABLE_Msk);
	while (canvasIsOpen(canvas)) {
		const int64_t now = os_timeNow();
		const float dt = (float)os_timeConvertTo(os_timeDiff(now, startTime), OS_TIME_UNITS_MS);
		startTime = now;

		uint32_t canvasWidth, canvasHeight;
		canvasGetSize(canvas, &canvasWidth, &canvasHeight);

		canvasClear(canvas, CANVAS_COLOR(0, 0, 0, 255));

		canvasBeginPath(canvas);
		canvasRect(canvas, 0.0f, 0.0f, (float)canvasWidth, (float)canvasHeight);
		canvasStrokePath(canvas, CANVAS_COLOR(255, 255, 255, 255), 2.0f, CANVAS_STROKE_FLAGS_BUTT_MITER_AA);

		canvasBeginPath(canvas);
		canvasRect(canvas, x, y, w, h);
		canvasFillPath(canvas, CANVAS_COLOR(255, 0, 0, 255), CANVAS_FILL_FLAGS_CONVEX);
		canvasStrokePath(canvas, CANVAS_COLOR(0, 255, 0, 255), 2.0f, CANVAS_STROKE_FLAGS_BUTT_MITER_AA);

		char str[256];
		snprintf(str, 256, "Frame: %.1fms", dt);
		canvasDrawText(canvas, 0.0f, (float)canvasHeight, 12.0f, CANVAS_FONT_TYPE_MONO_REGULAR, str, CANVAS_COLOR(255, 255, 255, 255));

		canvasSwapBuffers(canvas);

		x += dirX * dt / 1000.0f;
		y += dirY * dt / 1000.0f;
		if (x + w > canvasWidth) {
			x = canvasWidth - w;
			dirX *= -1.0f;
		} else if (x < 0.0f) {
			x = 0.0f;
			dirX *= -1.0f;
		}
		
		if (y + h > canvasHeight) {
			y = canvasHeight - h;
			dirY *= -1.0f;
		} else if (y < 0.0f) {
			y = 0.0f;
			dirY *= -1.0f;
		}
	}

	canvasDestroy(canvas);

	return 0;
}
