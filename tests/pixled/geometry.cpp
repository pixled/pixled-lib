#include "pixled/geometry.h"
#include "gtest/gtest.h"

using namespace pixled;

TEST(line, line_definition) {
	float a = - 3;
	float b = 2;
	float c = 1;

	point p0(2, 2.5); 
	point p1(0, -1./2.);
	point p2(4, 5.5);

	angle alpha = angle::fromRad(std::atan(3./2.));

	line l1(a, b, c);
	line l2(p2, alpha);
	line l3(p2, p0);

	// l1
	ASSERT_NEAR(l1.a * p0.x + l1.b * p0.y + l1.c, 0, 1e-4);
	ASSERT_NEAR(l1.a * p1.x + l1.b * p1.y + l1.c, 0, 1e-4);
	ASSERT_NEAR(l1.a * p2.x + l1.b * p2.y + l1.c, 0, 1e-4);

	// l2
	ASSERT_NEAR(l2.a * p0.x + l2.b * p0.y + l2.c, 0, 1e-4);
	ASSERT_NEAR(l2.a * p1.x + l2.b * p1.y + l2.c, 0, 1e-4);
	ASSERT_NEAR(l2.a * p2.x + l2.b * p2.y + l2.c, 0, 1e-4);

	// l3
	ASSERT_NEAR(l3.a * p0.x + l3.b * p0.y + l3.c, 0, 1e-4);
	ASSERT_NEAR(l3.a * p1.x + l3.b * p1.y + l3.c, 0, 1e-4);
	ASSERT_NEAR(l3.a * p2.x + l3.b * p2.y + l3.c, 0, 1e-4);
}

TEST(line, vertical) {
	line l(point(2, 4), point(2, 7));

	ASSERT_NEAR(l.a * 2 + l.b * 4 + l.c, 0, 1.e-4);
	ASSERT_NEAR(l.a * 2 + l.b * 7 + l.c, 0, 1.e-4);
	ASSERT_NEAR(l.a * 2 + l.b * 84 + l.c, 0, 1.e-4);
}

TEST(box, constructor) {
	box b({2.3, 4}, 7.5, 8);

	ASSERT_EQ(b.position(), point(2.3, 4));
	ASSERT_EQ(b.width(), 7.5);
	ASSERT_EQ(b.height(), 8);
}

TEST(bounding_box, build) {
	bounding_box bbox({point(2.4, 7)});
	ASSERT_EQ(bbox.position(), point(2.4, 7));
	ASSERT_EQ(bbox.width(), 0);
	ASSERT_EQ(bbox.height(), 0);

	bbox = {{
			point(2, 3),
			point(6, 1.9),
			point(4, 5),
			point(10, 4),
			point(6, 7.5)
	}};
	ASSERT_EQ(bbox.position(), point(2, 1.9));
	ASSERT_FLOAT_EQ(bbox.width(), 10.-2.);
	ASSERT_FLOAT_EQ(bbox.height(), 7.5-1.9);
}

TEST(bounding_box, include) {
	bounding_box bbox({
			point(2, 3),
			point(6, 1.9),
			point(4, 5),
			point(10, 4),
			point(6, 7.5)
	});

	// No change
	bbox.stretchTo(point(4, 4));
	ASSERT_EQ(bbox.position(), point(2, 1.9));
	ASSERT_FLOAT_EQ(bbox.width(), 10.-2.);
	ASSERT_FLOAT_EQ(bbox.height(), 7.5-1.9);

	// Stretch top
	bbox.stretchTo(point(4, -1.2));
	ASSERT_EQ(bbox.position(), point(2, -1.2));
	ASSERT_FLOAT_EQ(bbox.width(), 10.-2.);
	ASSERT_FLOAT_EQ(bbox.height(), 7.5-(-1.2));

	// Stretch bottom
	bbox.stretchTo(point(8, 12));
	ASSERT_EQ(bbox.position(), point(2, -1.2));
	ASSERT_FLOAT_EQ(bbox.width(), 10.-2.);
	ASSERT_FLOAT_EQ(bbox.height(), 12-(-1.2));

	// Stretch right
	bbox.stretchTo(point(11, 5));
	ASSERT_EQ(bbox.position(), point(2, -1.2));
	ASSERT_FLOAT_EQ(bbox.width(), 11.-2.);
	ASSERT_FLOAT_EQ(bbox.height(), 12-(-1.2));
	
	// Stretch left
	bbox.stretchTo(point(-2.9, 5));
	ASSERT_EQ(bbox.position(), point(-2.9, -1.2));
	ASSERT_FLOAT_EQ(bbox.width(), 11.-(-2.9));
	ASSERT_FLOAT_EQ(bbox.height(), 12-(-1.2));

	// Stretch top right
	bbox.stretchTo(point(15, -4));
	ASSERT_EQ(bbox.position(), point(-2.9, -4));
	ASSERT_FLOAT_EQ(bbox.width(), 15.-(-2.9));
	ASSERT_FLOAT_EQ(bbox.height(), 12-(-4));
}
