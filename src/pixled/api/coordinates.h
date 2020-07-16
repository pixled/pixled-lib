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

		/**
		 * A Line with equation a*x + b*y + c = 0
		 */
		struct Line {
			float a;
			float b;
			float c;
			Line(float a, float b, float c)
				: a(a), b(b), c(c) {}
		};
	}
}

#endif
