#include "pixled.h"
#include "pixled/gif_output.h"


int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	{
		// Radial rainbow
		pixled::hsb rainbow(pixled::Rainbow(20), 1.0, 1.0);

		// Blooms the rainbow anim at (8, 8) with a radius of 10
		pixled::Blooming blooming(rainbow, pixled::point(8, 8), 10);
		pixled::Runtime runtime(panel, out, blooming);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "blooming_rainbow.gif");
	}
	{
		// Radial rainbow
		pixled::hsb rainbow(pixled::Rainbow(20), 1.0, 1.0);

		// Moving blooming rainbow
		pixled::Blooming blooming(
				rainbow,
				// X waves from 8 with an amplitude of 4 with a period of 40
				// frames
				pixled::Point(pixled::Wave<pixled::coordinate>(40, 8, 4), 9),
				// Radius varies from 10 with an amplitude of 4 with a period
				// of 20 frames
				pixled::Wave<pixled::coordinate>(20, 10, 5)
				);
		pixled::Runtime runtime(panel, out, blooming);

		// Writes 40 frames to gif file
		out.write(runtime, 40, "dynamic_blooming_rainbow.gif");
	}
}
