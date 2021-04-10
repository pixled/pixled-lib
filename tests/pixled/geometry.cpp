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
