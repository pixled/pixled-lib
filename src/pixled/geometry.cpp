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

	angle operator+(const angle& a, const angle& b) {
		return angle(a.value+b.value);
	}

	angle operator-(const angle& a, const angle& b) {
		return angle(a.value-b.value);
	}

	line::line(point p, angle alpha)
		: a(-tan(alpha)), b(1), c(-p.y + p.x * tan(alpha)) {}

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

	bool point_equal::operator()(const point& p1, const point& p2) const {
		return p1 == p2;
	}

	std::ostream& operator<<(std::ostream& o, const point& p) {
		o << "(" << p.x << "," << p.y << ")";
		return o;
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


	box::box() : box({0, 0}, 0, 0) {}
	box::box(point position, coordinate width, coordinate height)
		: _position(position), _width(width), _height(height) {}

	bounding_box::bounding_box() {}
	bounding_box::bounding_box(std::vector<point> points) {
		for(auto point : points)
			this->stretchTo(point);
	}

	void bounding_box::stretchTo(point p) {
		if(!init) {
			this->_position=p;
			init=true;
		} else {
			if(p.x < this->_position.x) {
				this->_width+=this->_position.x - p.x;
				this->_position.x = p.x;
			}
			else if(p.x > this->_position.x + this->_width) {
				this->_width = p.x - this->_position.x;
			}
			if(p.y < this->_position.y) {
				this->_height+=this->_position.y - p.y;
				this->_position.y = p.y;
			}
			else if(p.y > this->_position.y + this->_height) {
				this->_height = p.y - this->_position.y;
			}
		}
	}

	point spiral::operator()(angle theta) {
		float r = a + b * theta.toDeg();
		return {
			center.x + r*cos(theta),
			center.y + r*sin(theta)
		};
	}
}
