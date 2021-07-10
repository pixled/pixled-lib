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
		pixled::point random_point() {
			std::uniform_real_distribution<pixled::coordinate> rd_coord;
			return {rd_coord(rd), rd_coord(rd)};
		}
};

TEST_F(SignalTest, sine) {
	pixled::signal::Sine sine(Cast<float>(pixled::chrono::T() + 2) / 12);

	ASSERT_FLOAT_EQ(sine(random_point(), 0), std::sin(2*PI*2.f/12));

	ASSERT_NEAR(sine(random_point(), 1), 1, .10e-4);
	ASSERT_NEAR(sine(random_point(), 4), 0, .10e-4);
	ASSERT_NEAR(sine(random_point(), 7), -1, .10e-4);
	ASSERT_NEAR(sine(random_point(), 10), 0, .10e-4);
	ASSERT_NEAR(sine(random_point(), 13), 1, .10e-4);
	ASSERT_NEAR(sine(random_point(), 16), 0, .10e-4);
}

TEST_F(SignalTest, square) {
	pixled::signal::Square square(Cast<float>(pixled::chrono::T() + 2) / 12);

	ASSERT_THAT(
		square(random_point(), -2),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));


	for(pixled::time t = -1; t < 3; t++)
		ASSERT_NEAR(square(random_point(), t), 1, .10e-4);

	ASSERT_THAT(
		square(random_point(), 4),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));

	for(pixled::time t = 5; t < 9; t++)
		ASSERT_NEAR(square(random_point(), t), -1, .10e-4);

	ASSERT_THAT(
		square(random_point(), 10),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));
}


TEST_F(SignalTest, triangle) {
	pixled::signal::Triangle triangle(Cast<float>(pixled::chrono::T()) / 12);

	ASSERT_NEAR(triangle(random_point(), 0), 0, .10e-4);
	ASSERT_NEAR(triangle(random_point(), 3), 1, .10e-4);
	ASSERT_NEAR(triangle(random_point(), 6), 0, .10e-4);
	ASSERT_NEAR(triangle(random_point(), 9), -1, .10e-4);
	ASSERT_NEAR(triangle(random_point(), 12), 0, .10e-4);
}


TEST_F(SignalTest, sawtooth) {
	pixled::signal::Sawtooth sawtooth(Cast<float>(pixled::chrono::T()) / 12);

	ASSERT_NEAR(sawtooth(random_point(), 0), 0, .10e-4);

	ASSERT_THAT(
		sawtooth(random_point(), 3),
		AnyOf(FloatNear(1, .10e-4), FloatNear(-1, .10e-4)
			));

	ASSERT_NEAR(sawtooth(random_point(), 6), 0, .10e-4);

	ASSERT_THAT(
		sawtooth(random_point(), 9),
		AnyOf(FloatNear(-1, .10e-4), FloatNear(1, .10e-4)
			));

	ASSERT_NEAR(sawtooth(random_point(), 12), 0, .10e-4);
}
