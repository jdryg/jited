#include <jitsheet/canvas.h>
#include <jitsheet/os.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int32_t main(void)
{
	int64_t startTime = os_timeNow();

	float angle = 0.0f;

	// Create canvas
	canvas_t* canvas = canvasCreate(256, 256, CANVAS_FLAGS_NONE);

	// While the canvas is open
	while (canvasIsOpen(canvas)) {
		const int64_t now = os_timeNow();
		const float dt = (float)os_timeConvertTo(os_timeDiff(now, startTime), OS_TIME_UNITS_MS);
		startTime = now;

		uint32_t canvasWidth, canvasHeight;
		canvasGetSize(canvas, &canvasWidth, &canvasHeight);

		canvasClear(canvas, CANVAS_COLOR(0, 0, 0, 255));

		canvasPushState(canvas);
		{
			canvasTransformTranslate(canvas, (float)canvasWidth * 0.5f, (float)canvasHeight * 0.5f);
			canvasBeginPath(canvas);
			canvasCircle(canvas, 0.0f, 0.0f, 10.0f);
			canvasFillPath(canvas, CANVAS_COLOR(255, 255, 0, 255), CANVAS_FILL_FLAGS_CONVEX_AA);

			canvasPushState(canvas);
			{
				canvasTransformScale(canvas, 1.0f, -1.0f);
				canvasTransformRotate(canvas, angle);
				canvasTransformTranslate(canvas, 60.0f + 20.0f * cos(5.0f * angle), 0.0f);
				canvasBeginPath(canvas);
				canvasRect(canvas, -5.0f, -5.0f, 10.0f, 10.0f);
				canvasFillPath(canvas, CANVAS_COLOR_RED, CANVAS_FILL_FLAGS_CONVEX_AA);
			}
			canvasPopState(canvas);
		}
		canvasPopState(canvas);

		angle += dt / 1000.0f;

		// Draw frame time
		char str[256];
		snprintf(str, 256, "Frame: %.1fms", dt);
		canvasDrawText(canvas, 0.0f, (float)canvasHeight, 12.0f, CANVAS_FONT_TYPE_MONO_REGULAR, str, CANVAS_COLOR(255, 255, 255, 255));

		canvasSwapBuffers(canvas);
	}

	canvasDestroy(canvas);

	return 0;
}
