#include "pixled/mapping.h"
#include "pixled/api/utils.h"

#include "gmock/gmock.h"

using ::testing::SizeIs;
using ::testing::Pair;
using ::testing::UnorderedElementsAre;

using pixled::api::Point;
using pixled::api::Angle;

#define ASSERT_ANGLE_EQ(A1, A2) \
	ASSERT_NEAR(pixled::api::Cos(A1), pixled::api::Cos(A2), 0.0001);\
	ASSERT_NEAR(pixled::api::Sin(A1), pixled::api::Sin(A2), 0.0001);

class TurtleMappingTest : public ::testing::Test {
	protected:
		pixled::TurtleMapping turtle;

};

TEST_F(TurtleMappingTest, init) {
	ASSERT_EQ(turtle.position(), Point(0, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(0.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, forward_no_led) {
	turtle.forward(10);

	ASSERT_EQ(turtle.position(), Point(10, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(0.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, forward) {
	turtle.forward(2);
	turtle.forward(10, 5);

	ASSERT_THAT(turtle.leds(), SizeIs(5));
	ASSERT_THAT(turtle.leds(), UnorderedElementsAre(
		Pair(Point(2, 0), 0),
		Pair(Point(4.5, 0), 1),
		Pair(Point(7, 0), 2),
		Pair(Point(9.5, 0), 3),
		Pair(Point(12, 0), 4)));
	ASSERT_EQ(turtle.position(), Point(12, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(0.));
	ASSERT_EQ(turtle.ledIndex(), 5);
}

TEST_F(TurtleMappingTest, turn_left) {
	turtle.turnLeft(60);

	ASSERT_EQ(turtle.position(), Point(0, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(60.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, turn_right) {
	turtle.turnRight(60);

	ASSERT_EQ(turtle.position(), Point(0, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(300.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, turn_forward) {
	turtle.turnRight(60);
	turtle.forward(10, 3);

	float expected_mid_x = 10 * pixled::api::Cos(-60) / 2;
	float expected_mid_y = 10 * pixled::api::Sin(-60) / 2;
	float expected_x = 10 * pixled::api::Cos(-60);
	float expected_y = 10 * pixled::api::Sin(-60);

	ASSERT_THAT(turtle.leds(), SizeIs(3));
	ASSERT_THAT(turtle.leds(), UnorderedElementsAre(
		Pair(Point(0, 0), 0),
		Pair(Point(expected_mid_x, expected_mid_y), 1),
		Pair(Point(expected_x, expected_y), 2)
		));
	ASSERT_EQ(turtle.position(), Point(expected_x, expected_y));
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(-60.));
	ASSERT_EQ(turtle.ledIndex(), 3);
}
