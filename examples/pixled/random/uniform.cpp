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
		// Uniform integer distribution between 30 and 200
		pixled::UniformDistribution<std::uint8_t> random_red(30, 200, random_engine);

		// Animation
		pixled::rgb color(random_red, 30, 30);

		pixled::Runtime runtime(panel, out, color);
		// Writes 100 frames to gif file
		out.write(runtime, 100, "uniform_t.gif");
	}
	{
		// Random engine that only depends upon time and space.
		// The value will be different for every leds, and will change every 10
		// frames.
		pixled::RandomXYT random_engine(10);
		// Uniform integer distribution between 30 and 200 (same as above)
		pixled::UniformDistribution<std::uint8_t> random_red(30, 200, random_engine);

		// Animation
		pixled::rgb color(random_red, 30, 30);

		pixled::Runtime runtime(panel, out, color);
		// Writes 100 frames to gif file
		out.write(runtime, 100, "uniform_xy_t.gif");
	}
	{
		// Same as above
		pixled::RandomXYT random_engine(10);
		// An uniformly distributed random float between 0 and 360
		pixled::UniformDistribution<float> random_hue(0, 360, random_engine);

		// Animation
		pixled::hsb color(random_hue, 1.0, 1.0);

		pixled::Runtime runtime(panel, out, color);
		// Writes 100 frames to gif file
		out.write(runtime, 100, "uniform_xy_t_hue.gif");
	}
}
