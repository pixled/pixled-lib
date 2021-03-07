#include "geometry.h"

namespace pixled {
	float distance(const Point& p1, const Point& p2) {
		return std::sqrt(std::pow(p1.y - p2.y, 2) + std::pow(p1.x - p2.x, 2));
	}

	std::size_t point_hash::operator()(const Point& p) const {
		auto hash1 = std::hash<Coordinate>{}(p.x);
		auto hash2 = std::hash<Coordinate>{}(p.y);
		return hash1 ^ hash2;
	}

	bool operator==(const Point& c1, const Point& c2) {
			return (c1.x == c2.x) && (c1.y == c2.y);
	}

	float Cos(const Angle& a) {
		return std::cos(a.toRad());
	}

	float Sin(const Angle& a) {
		return std::sin(a.toRad());
	}

	std::ostream& operator<<(std::ostream& o, const Point& p) {
		o << "(" << p.x << "," << p.y << ")";
		return o;
	}
}
