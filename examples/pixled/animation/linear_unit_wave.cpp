#include "pixled.h"
#include "pixled/gif_output.h"

// Required for the * operator to work
using namespace pixled;

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	{
		pixled::rgb wave (
			pixled::Cast<uint8_t>(
				255 * pixled::LinearUnitWave(8, 20, pixled::XLine(8))
				),
			(uint8_t) 0,
			(uint8_t) 0
			);
		pixled::Runtime runtime(panel, out, wave);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "basic_linear_unit_wave.gif");
	}
	{
		pixled::hsb wave (
				pixled::Rainbow(20),
				1.0,
				pixled::LinearUnitWave(8, 20, pixled::XLine(8))
				);
		pixled::Runtime runtime(panel, out, wave);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "rainbow_linear_unit_wave.gif");
	}
}
