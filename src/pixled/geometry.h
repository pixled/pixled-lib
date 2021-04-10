#ifndef PIXLED_GEOMETRY_H
#define PIXLED_GEOMETRY_H

#include <functional>
#include <cmath>
#include <iostream>

namespace pixled {
	static const float PI = 3.14159265358979323846f;

	typedef float coordinate;

	struct point {
		coordinate x;
		coordinate y;
		point() : point(0, 0) {}
		point(coordinate x, coordinate y)
			: x(x), y(y) {}
	};

	class angle {
		private:
			// value in radian
			float value;
			angle(float value) : value(value) {}

		public:

			static angle fromRad(float value);
			static angle fromDeg(float value);

			float toRad() const {
				return value;
			}

			float toDeg() const {
				return value * 180.f / PI;
			}

			angle operator+(const angle& other) const {
				return angle(value+other.value);
			}

			angle operator-(const angle& other) const {
				return angle(value-other.value);
			}

			angle& operator+=(const angle& other) {
				value+=other.value;
				return *this;
			}

			angle& operator-=(const angle& other) {
				value-=other.value;
				return *this;
			}
	};

	/**
	 * A Line with equation a*x + b*y + c = 0
	 */
	struct line {
		coordinate a;
		coordinate b;
		coordinate c;
		line(coordinate a, coordinate b, coordinate c)
			: a(a), b(b), c(c) {}

		line(point p, angle a);
		line(point p0, point p1);
	};
	struct point_hash {
		std::size_t operator()(const point& p) const;
	};

	bool operator==(const point& c1, const point& c2);

	struct point_equal {
		bool operator()(const point& p1, const point& p2) const {
			return p1 == p2;
		}
	};

	float distance(const point& p1, const point& p2);
	float cos(const angle& a);
	float sin(const angle& a);
	float tan(const angle& a);

	std::ostream& operator<<(std::ostream& o, const point& p);
}

#endif
