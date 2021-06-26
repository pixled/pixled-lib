#include "pixled.h"
#include "pixled/gif_output.h"

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	{
		// Simple rainbow hue
		pixled::hsb rainbow(pixled::Rainbow(40), 1.0, 1.0);
		pixled::Runtime runtime(panel, out, rainbow);

		// Writes 40 frames to gif file
		out.write(runtime, 40, "rainbow.gif");
	}
	{
		// Simple rainbow hue with dynamic brightness
		pixled::hsb rainbow(
				pixled::Rainbow(40), // hue
				1.0, // saturation
				pixled::Wave<float>(20, 0.5, 1.0) // brightness
				);
				
		pixled::Runtime runtime(panel, out, rainbow);

		// Writes 40 frames to gif file
		out.write(runtime, 40, "rainbow_dyn_b.gif");
	}
}
