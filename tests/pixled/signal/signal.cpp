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

class SineTest : public SignalTest {};

TEST_F(SineTest, const_params) {
	pixled::signal::Sine sine(Cast<float>(pixled::chrono::T() + 2) / 12);

	ASSERT_FLOAT_EQ(sine(random_point(), 0), std::sin(2*PI*2.f/12));

	ASSERT_NEAR(sine(random_point(), 1), 1, .10e-4);
	ASSERT_NEAR(sine(random_point(), 4), 0, .10e-4);
	ASSERT_NEAR(sine(random_point(), 7), -1, .10e-4);
	ASSERT_NEAR(sine(random_point(), 10), 0, .10e-4);
	ASSERT_NEAR(sine(random_point(), 13), 1, .10e-4);
	ASSERT_NEAR(sine(random_point(), 16), 0, .10e-4);
}

class SquareTest : public SignalTest {};

TEST_F(SquareTest, const_params) {
	pixled::signal::Square square(12.4, 12, Cast<float>(pixled::chrono::T() + 2));

	ASSERT_THAT(
		square(random_point(), -2),
		AnyOf(FloatNear(12.4, .10e-4), FloatNear(-12.4, .10e-4)
			));


	for(pixled::time t = -1; t < 3; t++)
		ASSERT_NEAR(square(random_point(), t), 12.4, .10e-4);

	ASSERT_THAT(
		square(random_point(), 4),
		AnyOf(FloatNear(12.4, .10e-4), FloatNear(-12.4, .10e-4)
			));

	for(pixled::time t = 5; t < 9; t++)
		ASSERT_NEAR(square(random_point(), t), -12.4, .10e-4);

	ASSERT_THAT(
		square(random_point(), 10),
		AnyOf(FloatNear(12.4, .10e-4), FloatNear(-12.4, .10e-4)
			));
}
