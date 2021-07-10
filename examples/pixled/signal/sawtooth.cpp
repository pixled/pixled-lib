#include "pixled.h"
#include "pixled/gif_output.h"

using namespace pixled;

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	// Time dependent wave
	{
		auto animation = pixled::rgb(
				// Red
				0,
				// Green
				0,
				// Blue = Time dependent sawtooth with a period of 10,
				// centered on 122, amplitude of 50
				pixled::Cast<std::uint8_t>(122 + (
						50 * pixled::Sawtooth(pixled::Cast<float>(pixled::T()) / 10.f)
						))
				);
		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sawtooth_t.gif");
	}

	// Space dependent wave
	{
		auto animation = pixled::rgb(
				// Red
				0,
				// Green
				0,
				// Blue = Space dependent sawtooth wave of period 8,
				// centered on 122, amplitude of 50
				pixled::Cast<std::uint8_t>(122 + (
						50 * pixled::Sawtooth(pixled::Cast<float>(pixled::X()) / 8.f)
						))
				);
		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sawtooth_x.gif");
	}

	// Linear progressive wave
	{
		auto animation = pixled::rgb(
				// Red
				0,
				// Green
				0,
				// Blue = Progressive sawtooth wave,
				// values centered on 122, amplitude of 50,
				// space period 8, time period 10
				pixled::Cast<std::uint8_t>(122 + (50 * pixled::Sawtooth(
					pixled::X() / 8.f - pixled::T() / 10.f
				)))
			);

		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sawtooth_x_t.gif");
	}

	// Radial progressive wave
	{
		auto animation = pixled::rgb(
				// Red
				0,
				// Green
				0,
				// Blue = Radial progressive sawtooth wave,
				// values centered on 122, amplitude of 50,
				// space period 8, time period 10
				pixled::Cast<std::uint8_t>(122 + (50 * pixled::Sawtooth(
							pixled::Distance(
								pixled::Point(pixled::X(), pixled::Y()),
								pixled::Point(8, 8)
								) / 8.f
							- pixled::T() / 10.f
							)))
				);

		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sawtooth_radial_t.gif");
	}
}
