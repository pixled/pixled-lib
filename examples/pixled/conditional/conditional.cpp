#include "pixled.h"
#include "pixled/gif_output.h"


using namespace pixled;

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	{
		// If based animation
		auto anim = pixled::If<color>(
				// condition
				pixled::Cast<int>(pixled::X() + pixled::Y()) % 2 == 0,
				// then
				pixled::rgb(
					0, pixled::UniformDistribution<uint8_t>(
						50, 200, pixled::RandomXYT(10)
						),
					0
				   ),
				// else
				pixled::rgb(
					0, 0, pixled::UniformDistribution<uint8_t>(
						50, 200, pixled::RandomXYT(10)
						)
				   )
				);

		pixled::Runtime runtime(panel, out, anim);

		// Writes 100 frames to gif file
		out.write(runtime, 100, "conditional_eq.gif");
	}
	{
		auto anim = pixled::If<color>(
				pixled::X() > 10,
				pixled::Blink(chroma::RED, 10),
				pixled::If<color>(
					pixled::X() <= 6,
					pixled::Blink(chroma::BLUE, 10),
					pixled::Blink(chroma::GREEN, 5)
					)
				);

		pixled::Runtime runtime(panel, out, anim);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "conditional_less_greater.gif");

	}
}
