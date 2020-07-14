#ifndef PIXLED_COORDINATES_H
#define PIXLED_COORDINATES_H

typedef long Coordinate;

namespace pixled {
	namespace api {
		struct Point {
			Coordinate x;
			Coordinate y;
			Point(Coordinate x, Coordinate y)
				: x(x), y(y) {}
		};

		struct Line {
			float a;
			float b;
			Line(float a, float b)
				: a(a), b(b) {}
		};
	}
}

#endif
