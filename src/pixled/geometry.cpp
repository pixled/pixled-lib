#include "geometry.h"

namespace pixled {
	float distance(const point& p1, const point& p2) {
		return std::sqrt(std::pow(p1.y - p2.y, 2) + std::pow(p1.x - p2.x, 2));
	}

	angle angle::fromRad(float value) {
		return angle(value);
	}
	angle angle::fromDeg(float value) {
		return angle(PI*value/180.f);
	}

	line::line(point p, angle alpha)
		: b(1), a(-tan(alpha)), c(-p.y + p.x * tan(alpha)) {}
	line::line(point p0, point p1) {
		if(p0.x != p1.x) {
			b = 1;
			a = -(p1.y - p0.y) / (p1.x - p0.x);
			c = -p0.y + p0.x * (p1.y - p0.y) / (p1.x - p0.x);
		} else {
			b = 0;
			a = 1;
			c = -p0.x;
		}
	}

	std::size_t point_hash::operator()(const point& p) const {
		auto hash1 = std::hash<coordinate>{}(p.x);
		auto hash2 = std::hash<coordinate>{}(p.y);
		return hash1 ^ hash2;
	}

	bool operator==(const point& c1, const point& c2) {
			return (c1.x == c2.x) && (c1.y == c2.y);
	}

	float cos(const angle& a) {
		return std::cos(a.toRad());
	}

	float sin(const angle& a) {
		return std::sin(a.toRad());
	}

	float tan(const angle& a) {
		return std::tan(a.toRad());
	}

	std::ostream& operator<<(std::ostream& o, const point& p) {
		o << "(" << p.x << "," << p.y << ")";
		return o;
	}
}
