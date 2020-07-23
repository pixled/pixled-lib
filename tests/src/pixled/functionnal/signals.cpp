#include "pixled/functionnal/functionnal.h"
#include "gmock/gmock.h"

using ::testing::AnyOf;
using ::testing::FloatNear;

class SignalTest : public ::testing::Test {
	private:
		std::mt19937 rd;
	protected:
		pixled::api::Point random_point() {
			std::uniform_real_distribution<pixled::Coordinate> rd_coord;
			return {rd_coord(rd), rd_coord(rd)};
		}
};

class SineTest : public SignalTest {};

TEST_F(SineTest, const_params) {
	pixled::Sine sine(12.4, 12, pixled::T() + 2.f);

	ASSERT_FLOAT_EQ(sine(random_point(), 0), 12.4*std::sin(2*PIXLED_PI*2.f/12));

	ASSERT_NEAR(sine(random_point(), 1), 12.4, .10e-4);
	ASSERT_NEAR(sine(random_point(), 4), 0, .10e-4);
	ASSERT_NEAR(sine(random_point(), 7), -12.4, .10e-4);
	ASSERT_NEAR(sine(random_point(), 10), 0, .10e-4);
	ASSERT_NEAR(sine(random_point(), 13), 12.4, .10e-4);
	ASSERT_NEAR(sine(random_point(), 16), 0, .10e-4);
}

class SquareTest : public SignalTest {};

TEST_F(SquareTest, const_params) {
	pixled::Square square(12.4, 12, pixled::T() + 2.f);

	ASSERT_THAT(
		square(random_point(), -2),
		AnyOf(FloatNear(12.4, .10e-4), FloatNear(-12.4, .10e-4)
			));


	for(pixled::Time t = -1; t < 3; t++)
		ASSERT_NEAR(square(random_point(), t), 12.4, .10e-4);

	ASSERT_THAT(
		square(random_point(), 4),
		AnyOf(FloatNear(12.4, .10e-4), FloatNear(-12.4, .10e-4)
			));

	for(pixled::Time t = 5; t < 9; t++)
		ASSERT_NEAR(square(random_point(), t), -12.4, .10e-4);

	ASSERT_THAT(
		square(random_point(), 10),
		AnyOf(FloatNear(12.4, .10e-4), FloatNear(-12.4, .10e-4)
			));
}
