#include "pixled/mapping/mapping.h"

#include "gmock/gmock.h"

using namespace testing;

using pixled::Point;
using pixled::Angle;
using pixled::mapping::PANEL_LINKING;

#define ASSERT_ANGLE_EQ(A1, A2) \
	ASSERT_NEAR(pixled::Cos(A1), pixled::Cos(A2), 0.0001);\
	ASSERT_NEAR(pixled::Sin(A1), pixled::Sin(A2), 0.0001);

MATCHER_P(PointEq, p, "") {
	return Matches(FloatNear(p.x, .10e-5))(arg.x)
		&& Matches(FloatNear(p.y, .10e-5))(arg.y);
}

class TurtleMappingTest : public Test {
	protected:
		pixled::mapping::TurtleMapping turtle;

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

	pixled::Point final_point(10 * pixled::Cos(-60), 10 * pixled::Sin(-60));
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

TEST(LedPanel, LRLRB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_LEFT_RIGHT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0.5, 0)), 0),
		Pair(PointEq(Point(1.5, 0)), 1),
		Pair(PointEq(Point(0.5, 1)), 2),
		Pair(PointEq(Point(1.5, 1)), 3),
		Pair(PointEq(Point(0.5, 2)), 4),
		Pair(PointEq(Point(1.5, 2)), 5)
		));
}

TEST(LedPanel, RLRLB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_RIGHT_LEFT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(1.5, 0)), 0),
		Pair(PointEq(Point(0.5, 0)), 1),
		Pair(PointEq(Point(1.5, 1)), 2),
		Pair(PointEq(Point(0.5, 1)), 3),
		Pair(PointEq(Point(1.5, 2)), 4),
		Pair(PointEq(Point(0.5, 2)), 5)
		));
}

TEST(LedPanel, LRRLB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0.5, 0)), 0),
		Pair(PointEq(Point(1.5, 0)), 1),
		Pair(PointEq(Point(1.5, 1)), 2),
		Pair(PointEq(Point(0.5, 1)), 3),
		Pair(PointEq(Point(0.5, 2)), 4),
		Pair(PointEq(Point(1.5, 2)), 5)
		));
}

TEST(LedPanel, RLLRB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_LEFT_RIGHT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(1.5, 0)), 0),
		Pair(PointEq(Point(0.5, 0)), 1),
		Pair(PointEq(Point(0.5, 1)), 2),
		Pair(PointEq(Point(1.5, 1)), 3),
		Pair(PointEq(Point(1.5, 2)), 4),
		Pair(PointEq(Point(0.5, 2)), 5)
		));
}

TEST(LedPanel, TDTDL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_TOP_DOWN_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0, 1.5)), 0),
		Pair(PointEq(Point(0, 0.5)), 1),
		Pair(PointEq(Point(1, 1.5)), 2),
		Pair(PointEq(Point(1, 0.5)), 3),
		Pair(PointEq(Point(2, 1.5)), 4),
		Pair(PointEq(Point(2, 0.5)), 5)
		));
}

TEST(LedPanel, DTDTL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_DOWN_TOP_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0, 0.5)), 0),
		Pair(PointEq(Point(0, 1.5)), 1),
		Pair(PointEq(Point(1, 0.5)), 2),
		Pair(PointEq(Point(1, 1.5)), 3),
		Pair(PointEq(Point(2, 0.5)), 4),
		Pair(PointEq(Point(2, 1.5)), 5)
		));
}

TEST(LedPanel, TDDTL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_DOWN_TOP_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0, 1.5)), 0),
		Pair(PointEq(Point(0, 0.5)), 1),
		Pair(PointEq(Point(1, 0.5)), 2),
		Pair(PointEq(Point(1, 1.5)), 3),
		Pair(PointEq(Point(2, 1.5)), 4),
		Pair(PointEq(Point(2, 0.5)), 5)
		));
}

TEST(LedPanel, DTTDL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_TOP_DOWN_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0, 0.5)), 0),
		Pair(PointEq(Point(0, 1.5)), 1),
		Pair(PointEq(Point(1, 1.5)), 2),
		Pair(PointEq(Point(1, 0.5)), 3),
		Pair(PointEq(Point(2, 0.5)), 4),
		Pair(PointEq(Point(2, 1.5)), 5)
		));
}

TEST(LedPanel, LRLRT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_LEFT_RIGHT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0.5, 2)), 0),
		Pair(PointEq(Point(1.5, 2)), 1),
		Pair(PointEq(Point(0.5, 1)), 2),
		Pair(PointEq(Point(1.5, 1)), 3),
		Pair(PointEq(Point(0.5, 0)), 4),
		Pair(PointEq(Point(1.5, 0)), 5)
		));
}

TEST(LedPanel, RLRLT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_RIGHT_LEFT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(1.5, 2)), 0),
		Pair(PointEq(Point(0.5, 2)), 1),
		Pair(PointEq(Point(1.5, 1)), 2),
		Pair(PointEq(Point(0.5, 1)), 3),
		Pair(PointEq(Point(1.5, 0)), 4),
		Pair(PointEq(Point(0.5, 0)), 5)
		));
}

TEST(LedPanel, LRRLT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_RIGHT_LEFT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(0.5, 2)), 0),
		Pair(PointEq(Point(1.5, 2)), 1),
		Pair(PointEq(Point(1.5, 1)), 2),
		Pair(PointEq(Point(0.5, 1)), 3),
		Pair(PointEq(Point(0.5, 0)), 4),
		Pair(PointEq(Point(1.5, 0)), 5)
		));
}

TEST(LedPanel, RLLRT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_LEFT_RIGHT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(1.5, 2)), 0),
		Pair(PointEq(Point(0.5, 2)), 1),
		Pair(PointEq(Point(0.5, 1)), 2),
		Pair(PointEq(Point(1.5, 1)), 3),
		Pair(PointEq(Point(1.5, 0)), 4),
		Pair(PointEq(Point(0.5, 0)), 5)
		));
}

TEST(LedPanel, TDTDR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_TOP_DOWN_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(2, 1.5)), 0),
		Pair(PointEq(Point(2, 0.5)), 1),
		Pair(PointEq(Point(1, 1.5)), 2),
		Pair(PointEq(Point(1, 0.5)), 3),
		Pair(PointEq(Point(0, 1.5)), 4),
		Pair(PointEq(Point(0, 0.5)), 5)
		));
}

TEST(LedPanel, DTDTR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_DOWN_TOP_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(2, 0.5)), 0),
		Pair(PointEq(Point(2, 1.5)), 1),
		Pair(PointEq(Point(1, 0.5)), 2),
		Pair(PointEq(Point(1, 1.5)), 3),
		Pair(PointEq(Point(0, 0.5)), 4),
		Pair(PointEq(Point(0, 1.5)), 5)
		));
}

TEST(LedPanel, TDDTR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_DOWN_TOP_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(2, 1.5)), 0),
		Pair(PointEq(Point(2, 0.5)), 1),
		Pair(PointEq(Point(1, 0.5)), 2),
		Pair(PointEq(Point(1, 1.5)), 3),
		Pair(PointEq(Point(0, 1.5)), 4),
		Pair(PointEq(Point(0, 0.5)), 5)
		));
}

TEST(LedPanel, DTTDR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_TOP_DOWN_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		Pair(PointEq(Point(2, 0.5)), 0),
		Pair(PointEq(Point(2, 1.5)), 1),
		Pair(PointEq(Point(1, 1.5)), 2),
		Pair(PointEq(Point(1, 0.5)), 3),
		Pair(PointEq(Point(0, 0.5)), 4),
		Pair(PointEq(Point(0, 1.5)), 5)
		));
}
