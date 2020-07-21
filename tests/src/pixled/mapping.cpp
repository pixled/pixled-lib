#include "pixled/mapping.h"
#include "pixled/api/utils.h"

#include "gmock/gmock.h"

using ::testing::SizeIs;
using ::testing::Pair;
using ::testing::UnorderedElementsAre;
using ::testing::FloatEq;
using ::testing::Matches;

using pixled::api::Point;
using pixled::api::Angle;

#define ASSERT_ANGLE_EQ(A1, A2) \
	ASSERT_NEAR(pixled::api::Cos(A1), pixled::api::Cos(A2), 0.0001);\
	ASSERT_NEAR(pixled::api::Sin(A1), pixled::api::Sin(A2), 0.0001);

MATCHER_P(PointEq, p, "") {
	return Matches(FloatEq(p.x))(arg.x)
		&& Matches(FloatEq(p.y))(arg.y);
}

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
		Pair(Point(3, 0), 0),
		Pair(Point(5, 0), 1),
		Pair(Point(7, 0), 2),
		Pair(Point(9, 0), 3),
		Pair(Point(11, 0), 4)));
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

	pixled::api::Point final_point(10 * pixled::api::Cos(-60), 10 * pixled::api::Sin(-60));
	float led_1_x = 1 * final_point.x / 6;
	float led_1_y = 1 * final_point.y / 6;
	float led_2_x = 3 * final_point.x / 6;
	float led_2_y = 3 * final_point.y / 6;
	float led_3_x = 5 * final_point.x / 6;
	float led_3_y = 5 * final_point.y / 6;

	ASSERT_THAT(turtle.leds(), SizeIs(3));
	ASSERT_THAT(turtle.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(led_1_x, led_1_y)), 0),
		Pair(PointEq(Point(led_2_x, led_2_y)), 1),
		Pair(PointEq(Point(led_3_x, led_3_y)), 2)
		));
	ASSERT_EQ(turtle.position(), final_point);
	ASSERT_ANGLE_EQ(turtle.orientation(), Angle(-60.));
	ASSERT_EQ(turtle.ledIndex(), 3);
}

/*
 *TEST(Hexa, print) {
 *    pixled::TurtleMapping turtle;
 *    for(int i = 0; i < 6; i++) {
 *        turtle.forward(10, 10);
 *        turtle.turnLeft(60);
 *    }
 *    std::cout << turtle;
 *}
 */

TEST(LedPanel, LRLR) {
	pixled::LedPanel panel(3, 3, pixled::LEFT_RIGHT_LEFT_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(9));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0.5, 0)), 0),
		Pair(PointEq(Point(1.5, 0)), 1),
		Pair(PointEq(Point(2.5, 0)), 2),
		Pair(PointEq(Point(0.5, 1)), 3),
		Pair(PointEq(Point(1.5, 1)), 4),
		Pair(PointEq(Point(2.5, 1)), 5),
		Pair(PointEq(Point(0.5, 2)), 6),
		Pair(PointEq(Point(1.5, 2)), 7),
		Pair(PointEq(Point(2.5, 2)), 8)
		));

	//std::cout << panel;
}

TEST(LedPanel, LRRL) {
	pixled::LedPanel panel(3, 3, pixled::LEFT_RIGHT_RIGHT_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(9));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0.5, 0)), 0),
		Pair(PointEq(Point(1.5, 0)), 1),
		Pair(PointEq(Point(2.5, 0)), 2),
		Pair(PointEq(Point(2.5, 1)), 3),
		Pair(PointEq(Point(1.5, 1)), 4),
		Pair(PointEq(Point(0.5, 1)), 5),
		Pair(PointEq(Point(0.5, 2)), 6),
		Pair(PointEq(Point(1.5, 2)), 7),
		Pair(PointEq(Point(2.5, 2)), 8)
		));

	//std::cout << panel;
}
