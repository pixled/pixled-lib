#include "pixled.h"
#include "pixled/gif_output.h"


using namespace pixled;

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutputConfig config;
	config.draw_led_index = true;
	pixled::GifOutput out(480, pixled::FIT_WIDTH, 20, panel, config);

	{
		auto anim = pixled::If<color>(
				pixled::I() % 2 == 0,
				pixled::rgb(Cast<std::uint8_t>(255 * T() / 20), 0, 0),
				pixled::rgb(0, 0, Cast<std::uint8_t>(255 - 255 * T() / 20))
				);
		pixled::Runtime runtime(panel, out, anim);

		// Writes 40 frames to gif file
		out.write(runtime, 40, "index.gif");
	}
}
