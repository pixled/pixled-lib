#include "pixled.h"
#include "pixled/gif_output.h"


int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	{
		// Blink purple with a period of 10 frames
		pixled::Blink blink(pixled::PURPLE, 4);
		pixled::Runtime runtime(panel, out, blink);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "blink_color.gif");
	}
	{
		// Radial rainbow
		pixled::hsb rainbow(
				pixled::RadialRainbowWave(16, 20, pixled::point(8, 8)), // hue
				1.0, // saturation
				1.0 // brightness
				);

		// Blinks the rainbow anim with a period of 10 frames
		pixled::Blink blink(rainbow, 4);
		pixled::Runtime runtime(panel, out, blink);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "blink_rainbow.gif");
	}
}
