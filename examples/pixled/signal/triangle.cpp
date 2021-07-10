#include "pixled.h"
#include "pixled/gif_output.h"

using namespace pixled;

int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	// Radial progressive wave
	{
		// Center of the radial wave
		auto center_x = 8.f * (1.f + pixled::Sine(pixled::T() / 30.f));
		auto animation = pixled::hsb(
				// Rainbow hue
				pixled::Rainbow(20),
				// Max saturation
				1.0,
				// Saturation = Radial progressive sine wave
				0.5f * (1.f + pixled::Sine(
						// Distance between...
						pixled::Distance(
							// ... current point
							pixled::Point(pixled::X(), pixled::Y()),
							// ... and a point described by a triangle wave of
							// parameter `center_x`
							pixled::Point(
								pixled::Cast<coordinate>(center_x),
								8.f + 3.f * pixled::Triangle(center_x / 8.f)
								)
							)
						/ 8.f // Spatial period of the Sine
						- pixled::T() / 10.f // Time component of the Sine
						))
				);

		pixled::Runtime runtime(panel, out, animation);

		// Writes 60 frames to gif file
		out.write(runtime, 60, "insane_triangle_radial_t.gif");
	}
}
