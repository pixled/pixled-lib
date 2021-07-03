#include "pixled.h"
#include "pixled/gif_output.h"

using namespace pixled;

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	// Time dependent wave
	{
		auto animation = pixled::hsb(
				// Rainbow hue
				pixled::Rainbow(20),
				// Max saturation
				1.0,
				// Saturation = Time dependent sine wave with a period of 10
				0.5f * (1.f + pixled::Sine(pixled::Cast<float>(pixled::T()) / 10.f))
				);
		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sine_t.gif");
	}

	// Space dependent wave
	{
		auto animation = pixled::hsb(
				// Rainbow hue
				pixled::Rainbow(20),
				// Max saturation
				1.0,
				// Saturation = Space dependent sine wave of period 8
				0.5f * (1.f + pixled::Sine(pixled::X() / 8.f))
				);
		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sine_x.gif");
	}

	// Linear progressive wave
	{
		auto animation = pixled::hsb(
				// Rainbow hue
				pixled::Rainbow(20),
				// Max saturation
				1.0,
				// Saturation = Progressive sine wave of period 8
				0.5f * (1.f + pixled::Sine(
						pixled::X() / 8.f - pixled::T() / 10.f
						))
				);
		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sine_x_t.gif");
	}

	// Radial progressive wave
	{
		auto animation = pixled::hsb(
				// Rainbow hue
				pixled::Rainbow(20),
				// Max saturation
				1.0,
				// Saturation = Radial progressive sine wave
				0.5f * (1.f + pixled::Sine(
						pixled::Distance(
							pixled::Point(pixled::X(), pixled::Y()), point(8, 8)
							) / 8.f
						- pixled::T() / 10.f
						))
				);
		pixled::Runtime runtime(panel, out, animation);

		// Writes 20 frames to gif file
		out.write(runtime, 20, "sine_radial_t.gif");
	}
}
