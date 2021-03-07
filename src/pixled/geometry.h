#ifndef PIXLED_GEOMETRY_H
#define PIXLED_GEOMETRY_H

#include <functional>
#include <cmath>
#include <iostream>

#define PIXLED_PI 3.14159265358979323846f

namespace pixled {
	typedef float Coordinate;

	struct Point {
		Coordinate x;
		Coordinate y;
		Point() : Point(0, 0) {}
		Point(Coordinate x, Coordinate y)
			: x(x), y(y) {}
	};

	class Angle {
		private:
			float value;

		public:
			Angle(float value) : value(value) {}

			float toRad() const {
				return 2*PIXLED_PI*value/360.f;
			}

			Angle operator+(const Angle& other) const {
				return Angle(value+other.value);
			}

			Angle operator-(const Angle& other) const {
				return Angle(value-other.value);
			}

			Angle& operator+=(const Angle& other) {
				value+=other.value;
				return *this;
			}

			Angle& operator-=(const Angle& other) {
				value-=other.value;
				return *this;
			}
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
		std::size_t operator()(const Point& p) const;
	};

	bool operator==(const Point& c1, const Point& c2);

	struct point_equal {
		bool operator()(const Point& p1, const Point& p2) const {
			return p1 == p2;
		}
	};

	float distance(const Point& p1, const Point& p2);
	float Cos(const Angle& a);
	float Sin(const Angle& a);

	std::ostream& operator<<(std::ostream& o, const Point& p);
}

#endif
