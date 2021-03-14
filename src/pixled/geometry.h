#ifndef PIXLED_GEOMETRY_H
#define PIXLED_GEOMETRY_H

#include <functional>
#include <cmath>
#include <iostream>

#define PIXLED_PI 3.14159265358979323846f

namespace pixled {
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
			float value;

		public:
			angle(float value) : value(value) {}

			float toRad() const {
				return 2*PIXLED_PI*value/360.f;
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
		float a;
		float b;
		float c;
		line(float a, float b, float c)
			: a(a), b(b), c(c) {}
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
