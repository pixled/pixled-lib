#include "pixled/mapping/mapping.h"

#include "gmock/gmock.h"

using namespace testing;
using namespace pixled;

using pixled::mapping::PANEL_LINKING;

#define ASSERT_ANGLE_EQ(A1, A2) \
	ASSERT_NEAR(pixled::cos(A1), pixled::cos(A2), 0.0001);\
	ASSERT_NEAR(pixled::sin(A1), pixled::sin(A2), 0.0001);

MATCHER_P(PointEq, p, "") {
	return Matches(FloatNear(p.x, .10e-5))(arg.x)
		&& Matches(FloatNear(p.y, .10e-5))(arg.y);
}
MATCHER_P2(LedEq, location, index, "") {
	return Matches(PointEq(location))(arg.location) && (pixled::index_t) index == arg.index;
}

class MappingTest : public Test {
	protected:
		Mapping mapping;

		void SetUp() override {
			mapping.push({point(2, 3), 0});
			mapping.push({point(6, 1.9), 1});
			mapping.push({point(4, 5), 2});
			mapping.push({point(10, 4), 3});
			mapping.push({point(6, 7.5), 4});
		}


};

TEST_F(MappingTest, leds) {
	ASSERT_THAT(mapping.leds(), UnorderedElementsAre(
				LedEq(point(2, 3), 0),
				LedEq(point(6, 1.9), 1),
				LedEq(point(4, 5), 2),
				LedEq(point(10, 4), 3),
				LedEq(point(6, 7.5), 4)
				));
}

TEST_F(MappingTest, bounding_box) {
	box bbox = mapping.boundingBox();

	ASSERT_EQ(bbox.position(), point(2, 1.9));
	ASSERT_FLOAT_EQ(bbox.width(), 10.-2.);
	ASSERT_FLOAT_EQ(bbox.height(), 7.5-1.9);
}

class TurtleMappingTest : public Test {
	protected:
		pixled::mapping::TurtleMapping turtle;

};

TEST_F(TurtleMappingTest, init) {
	ASSERT_EQ(turtle.position(), point(0, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), angle::fromRad(0.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, forward_no_led) {
	turtle.forward(10);

	ASSERT_EQ(turtle.position(), point(10, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), angle::fromDeg(0.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, forward) {
	turtle.forward(2);
	turtle.forward(10, 5);

	ASSERT_THAT(turtle.leds(), SizeIs(5));
	ASSERT_THAT(turtle.leds(), UnorderedElementsAre(
		LedEq(point(3, 0), 0),
		LedEq(point(5, 0), 1),
		LedEq(point(7, 0), 2),
		LedEq(point(9, 0), 3),
		LedEq(point(11, 0), 4)));
	ASSERT_EQ(turtle.position(), point(12, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), angle::fromDeg(0.));
	ASSERT_EQ(turtle.ledIndex(), 5);
}

TEST_F(TurtleMappingTest, turn_left) {
	turtle.turnLeft(angle::fromDeg(60));

	ASSERT_EQ(turtle.position(), point(0, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), angle::fromDeg(60.));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, turn_right) {
	turtle.turnRight(angle::fromDeg(60));

	ASSERT_EQ(turtle.position(), point(0, 0));
	ASSERT_ANGLE_EQ(turtle.orientation(), angle::fromDeg((300.)));
	ASSERT_EQ(turtle.ledIndex(), 0);
}

TEST_F(TurtleMappingTest, turn_forward) {
	turtle.turnRight(angle::fromDeg(60));
	turtle.forward(10, 3);

	pixled::point final_point(10 * cos(angle::fromDeg(-60)), 10 * sin(angle::fromDeg(-60)));
	float led_1_x = 1 * final_point.x / 6;
	float led_1_y = 1 * final_point.y / 6;
	float led_2_x = 3 * final_point.x / 6;
	float led_2_y = 3 * final_point.y / 6;
	float led_3_x = 5 * final_point.x / 6;
	float led_3_y = 5 * final_point.y / 6;

	ASSERT_THAT(turtle.leds(), SizeIs(3));
	ASSERT_THAT(turtle.leds(), UnorderedElementsAre(
		LedEq(point(led_1_x, led_1_y), 0),
		LedEq(point(led_2_x, led_2_y), 1),
		LedEq(point(led_3_x, led_3_y), 2)
		));
	ASSERT_EQ(turtle.position(), final_point);
	ASSERT_ANGLE_EQ(turtle.orientation(), angle::fromDeg(-60.));
	ASSERT_EQ(turtle.ledIndex(), 3);
}

TEST(LedStrip, test) {
	pixled::mapping::LedStrip led_strip(20);
	ASSERT_EQ(led_strip.getLength(), 20);

	ASSERT_THAT(led_strip.leds(), SizeIs(20));
	float y = led_strip.leds().begin()->location.y;
	for(auto led : led_strip.leds())
		ASSERT_FLOAT_EQ(led.location.y, y);

}

TEST(LedPanel, LRLRB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_LEFT_RIGHT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0.5, 0), 0),
		LedEq(point(1.5, 0), 1),
		LedEq(point(0.5, 1), 2),
		LedEq(point(1.5, 1), 3),
		LedEq(point(0.5, 2), 4),
		LedEq(point(1.5, 2), 5)
		));
}

TEST(LedPanel, RLRLB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_RIGHT_LEFT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(1.5, 0), 0),
		LedEq(point(0.5, 0), 1),
		LedEq(point(1.5, 1), 2),
		LedEq(point(0.5, 1), 3),
		LedEq(point(1.5, 2), 4),
		LedEq(point(0.5, 2), 5)
		));
}

TEST(LedPanel, LRRLB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0.5, 0), 0),
		LedEq(point(1.5, 0), 1),
		LedEq(point(1.5, 1), 2),
		LedEq(point(0.5, 1), 3),
		LedEq(point(0.5, 2), 4),
		LedEq(point(1.5, 2), 5)
		));
}

TEST(LedPanel, RLLRB) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_LEFT_RIGHT_FROM_BOTTOM);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(1.5, 0), 0),
		LedEq(point(0.5, 0), 1),
		LedEq(point(0.5, 1), 2),
		LedEq(point(1.5, 1), 3),
		LedEq(point(1.5, 2), 4),
		LedEq(point(0.5, 2), 5)
		));
}

TEST(LedPanel, TDTDL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_TOP_DOWN_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0, 1.5), 0),
		LedEq(point(0, 0.5), 1),
		LedEq(point(1, 1.5), 2),
		LedEq(point(1, 0.5), 3),
		LedEq(point(2, 1.5), 4),
		LedEq(point(2, 0.5), 5)
		));
}

TEST(LedPanel, DTDTL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_DOWN_TOP_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0, 0.5), 0),
		LedEq(point(0, 1.5), 1),
		LedEq(point(1, 0.5), 2),
		LedEq(point(1, 1.5), 3),
		LedEq(point(2, 0.5), 4),
		LedEq(point(2, 1.5), 5)
		));
}

TEST(LedPanel, TDDTL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_DOWN_TOP_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0, 1.5), 0),
		LedEq(point(0, 0.5), 1),
		LedEq(point(1, 0.5), 2),
		LedEq(point(1, 1.5), 3),
		LedEq(point(2, 1.5), 4),
		LedEq(point(2, 0.5), 5)
		));
}

TEST(LedPanel, DTTDL) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_TOP_DOWN_FROM_LEFT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0, 0.5), 0),
		LedEq(point(0, 1.5), 1),
		LedEq(point(1, 1.5), 2),
		LedEq(point(1, 0.5), 3),
		LedEq(point(2, 0.5), 4),
		LedEq(point(2, 1.5), 5)
		));
}

TEST(LedPanel, LRLRT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_LEFT_RIGHT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0.5, 2), 0),
		LedEq(point(1.5, 2), 1),
		LedEq(point(0.5, 1), 2),
		LedEq(point(1.5, 1), 3),
		LedEq(point(0.5, 0), 4),
		LedEq(point(1.5, 0), 5)
		));
}

TEST(LedPanel, RLRLT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_RIGHT_LEFT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(1.5, 2), 0),
		LedEq(point(0.5, 2), 1),
		LedEq(point(1.5, 1), 2),
		LedEq(point(0.5, 1), 3),
		LedEq(point(1.5, 0), 4),
		LedEq(point(0.5, 0), 5)
		));
}

TEST(LedPanel, LRRLT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::LEFT_RIGHT_RIGHT_LEFT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(0.5, 2), 0),
		LedEq(point(1.5, 2), 1),
		LedEq(point(1.5, 1), 2),
		LedEq(point(0.5, 1), 3),
		LedEq(point(0.5, 0), 4),
		LedEq(point(1.5, 0), 5)
		));
}

TEST(LedPanel, RLLRT) {
	pixled::mapping::LedPanel panel(2, 3, PANEL_LINKING::RIGHT_LEFT_LEFT_RIGHT_FROM_TOP);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(1.5, 2), 0),
		LedEq(point(0.5, 2), 1),
		LedEq(point(0.5, 1), 2),
		LedEq(point(1.5, 1), 3),
		LedEq(point(1.5, 0), 4),
		LedEq(point(0.5, 0), 5)
		));
}

TEST(LedPanel, TDTDR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_TOP_DOWN_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(2, 1.5), 0),
		LedEq(point(2, 0.5), 1),
		LedEq(point(1, 1.5), 2),
		LedEq(point(1, 0.5), 3),
		LedEq(point(0, 1.5), 4),
		LedEq(point(0, 0.5), 5)
		));
}

TEST(LedPanel, DTDTR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_DOWN_TOP_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(2, 0.5), 0),
		LedEq(point(2, 1.5), 1),
		LedEq(point(1, 0.5), 2),
		LedEq(point(1, 1.5), 3),
		LedEq(point(0, 0.5), 4),
		LedEq(point(0, 1.5), 5)
		));
}

TEST(LedPanel, TDDTR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::TOP_DOWN_DOWN_TOP_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(2, 1.5), 0),
		LedEq(point(2, 0.5), 1),
		LedEq(point(1, 0.5), 2),
		LedEq(point(1, 1.5), 3),
		LedEq(point(0, 1.5), 4),
		LedEq(point(0, 0.5), 5)
		));
}

TEST(LedPanel, DTTDR) {
	pixled::mapping::LedPanel panel(3, 2, PANEL_LINKING::DOWN_TOP_TOP_DOWN_FROM_RIGHT);

	ASSERT_THAT(panel.leds(), SizeIs(6));
	ASSERT_THAT(panel.leds(), UnorderedElementsAre(
		LedEq(point(2, 0.5), 0),
		LedEq(point(2, 1.5), 1),
		LedEq(point(1, 1.5), 2),
		LedEq(point(1, 0.5), 3),
		LedEq(point(0, 0.5), 4),
		LedEq(point(0, 1.5), 5)
		));
}
