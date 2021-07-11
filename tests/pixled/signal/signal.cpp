#include "pixled/signal/signal.h"
#include "pixled/animation/animation.h"
#include "pixled/arithmetic/arithmetic.h"
#include "gmock/gmock.h"

#include <random>

using ::testing::AnyOf;
using ::testing::FloatNear;

using namespace pixled;

class SignalTest : public ::testing::Test {
	private:
		std::mt19937 rd;
	protected:
		pixled::led random_led() {
			std::uniform_real_distribution<pixled::coordinate> rd_coord;
			std::uniform_int_distribution<pixled::index_t> rd_index;
			return {{rd_coord(rd), rd_coord(rd)}, rd_index(rd)};
		}
};

TEST_F(SignalTest, sine) {
	pixled::signal::Sine sine(Cast<float>(pixled::chrono::T() + 2) / 12);

	ASSERT_FLOAT_EQ(sine(random_led(), 0), std::sin(2*PI*2.f/12));

	ASSERT_NEAR(sine(random_led(), 1), 1, .10e-4);
	ASSERT_NEAR(sine(random_led(), 4), 0, .10e-4);
	ASSERT_NEAR(sine(random_led(), 7), -1, .10e-4);
	ASSERT_NEAR(sine(random_led(), 10), 0, .10e-4);
	ASSERT_NEAR(sine(random_led(), 13), 1, .10e-4);
	ASSERT_NEAR(sine(random_led(), 16), 0, .10e-4);
}

TEST_F(SignalTest, square) {
	pixled::signal::Square square(Cast<float>(pixled::chrono::T() + 2) / 12);

	ASSERT_THAT(
		square(random_led(), -2),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));


	for(pixled::time t = -1; t < 3; t++)
		ASSERT_NEAR(square(random_led(), t), 1, .10e-4);

	ASSERT_THAT(
		square(random_led(), 4),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));

	for(pixled::time t = 5; t < 9; t++)
		ASSERT_NEAR(square(random_led(), t), -1, .10e-4);

	ASSERT_THAT(
		square(random_led(), 10),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));
}


TEST_F(SignalTest, triangle) {
	pixled::signal::Triangle triangle(Cast<float>(pixled::chrono::T()) / 12);

	ASSERT_NEAR(triangle(random_led(), 0), 0, .10e-4);
	ASSERT_NEAR(triangle(random_led(), 3), 1, .10e-4);
	ASSERT_NEAR(triangle(random_led(), 6), 0, .10e-4);
	ASSERT_NEAR(triangle(random_led(), 9), -1, .10e-4);
	ASSERT_NEAR(triangle(random_led(), 12), 0, .10e-4);
}


TEST_F(SignalTest, sawtooth) {
	pixled::signal::Sawtooth sawtooth(Cast<float>(pixled::chrono::T()) / 12);

	ASSERT_NEAR(sawtooth(random_led(), 0), 0, .10e-4);

	ASSERT_THAT(
		sawtooth(random_led(), 3),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));

	ASSERT_NEAR(sawtooth(random_led(), 6), 0, .10e-4);

	ASSERT_THAT(
		sawtooth(random_led(), 9),
		AnyOf(FloatNear(-1, .10e-4), FloatNear(1, .10e-4)
			));

	ASSERT_NEAR(sawtooth(random_led(), 12), 0, .10e-4);
}
