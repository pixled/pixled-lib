#include "pixled.h"
#include "pixled/gif_output.h"


int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	{
		// Random engine that only depends upon time.
		// The value will be the same for every leds, and will change every 10
		// frames.
		pixled::RandomT random_engine(10);
		// Normal integer distribution centered on 200 with a variation of 20
		pixled::NormalDistribution<std::uint8_t> random_red(200, 20, random_engine);

		// Animation
		pixled::rgb color(random_red, 50, 50);

		pixled::Runtime runtime(panel, out, color);
		// Writes 100 frames to gif file
		out.write(runtime, 100, "random_normal_t.gif");
	}
	{
		// Random engine that only depends upon time and space.
		// The value will be different for every leds, and will change every 10
		// frames.
		pixled::RandomXYT random_engine(10);
		// Normal integer distribution centered on 200 with a variation of 20
		// (same as above)
		pixled::NormalDistribution<std::uint8_t> random_red(200, 20, random_engine);

		// Animation
		pixled::rgb color(random_red, 50, 50);

		pixled::Runtime runtime(panel, out, color);
		// Writes 100 frames to gif file
		out.write(runtime, 100, "random_normal_xy_t.gif");
	}
	{
		// Same as above
		pixled::RandomXYT random_engine(10);
		// A random hue with values distributed according to a normal
		// distribution
		pixled::NormalDistribution<float> random_hue(
				// The center of the normal distribution varies from 0 to 360
				pixled::Rainbow(50),
				// Variation
				20,
				// Random engine
				random_engine
				);

		// Animation
		pixled::hsb color(random_hue, 1.0, 1.0);

		pixled::Runtime runtime(panel, out, color);
		// Writes 100 frames to gif file
		out.write(runtime, 100, "random_normal_xy_t_hue.gif");
	}
}
