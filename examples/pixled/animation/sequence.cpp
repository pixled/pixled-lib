#include "pixled.h"
#include "pixled/gif_output.h"


int main(int argc, char** argv) {
	pixled::LedPanel panel(16, 16, pixled::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);
	pixled::GifOutput out(256, pixled::FIT_WIDTH, 20, panel);

	// Simple blink
	pixled::Blink anim1(pixled::PURPLE, 4);
	// A rainbow
	pixled::hsb anim2(pixled::RadialRainbowWave(32, 40, pixled::point(8, 8)), 1.0, 1.0);
	// Sequence are Animations too, so they can be added to other sequences
	pixled::Sequence anim3({
			{pixled::RED, 10},
			{pixled::GREEN, 10},
			{pixled::BLUE, 10}
			});

	// Animation sequence
	pixled::Sequence anim({
			{anim1, 20},
			{anim2, 20},
			{anim3, 40},
			{anim2, 40}
			});

	pixled::Runtime runtime(panel, out, anim);

	// Writes 120 frames to gif file
	out.write(runtime, 120, "sequence.gif");
}
