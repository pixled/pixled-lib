#ifndef PIXLED_COORDINATES_H
#define PIXLED_COORDINATES_H

#include <functional>

typedef long Coordinate;

namespace pixled {
	namespace api {
		struct Point {
			Coordinate x;
			Coordinate y;
			Point() : Point(0, 0) {}
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
		struct point_hash {
			std::size_t operator()(const Point& p) const{
				auto hash1 = std::hash<Coordinate>{}(p.x);
				auto hash2 = std::hash<Coordinate>{}(p.y);
				return hash1 ^ hash2;
			}
		};

		struct point_equal {
			bool operator()(const Point& p1, const Point& p2) const {
				return p1.x == p2.x && p1.y == p2.y;
			}
		};
	}

}

#endif
