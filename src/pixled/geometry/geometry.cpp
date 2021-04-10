#include "geometry.h"


namespace pixled { namespace geometry {

	float Distance::operator()(point c, time t) const {
		point c1 = this->call<0>(c, t);
		point c2 = this->call<1>(c, t);
		return std::sqrt(std::pow(c2.y - c1.y, 2) + std::pow(c2.x - c1.x, 2));
	}

	float LineDistance::operator()(point p, time t) const {
		line l = this->call<0>(p, t);
		point point = this->call<1>(p, t);
		return std::abs(l.a * point.x + l.b * point.y + l.c) /
			std::sqrt(std::pow(l.a, 2) + std::pow(l.b, 2));
	}

	point Point::operator()(point c, time t) const {
		return {this->call<0>(c, t), this->call<1>(c, t)};
	}

	angle AngleDeg::operator()(point p, time t) const {
		return angle::fromDeg(this->call<0>(p, t));
	}

	angle AngleRad::operator()(point p, time t) const {
		return angle::fromRad(this->call<0>(p, t));
	}

	line Line::operator()(point p, time t) const {
		return {this->call<0>(p, t), this->call<1>(p, t), this->call<2>(p, t)};
	}

	line XLine::operator()(point p, time t) const {
		return {1, 0, -this->call<0>(p, t)};
	}

	line YLine::operator()(point p, time t) const {
		return {0, 1, -this->call<0>(p, t)};
	}

	line AlphaLine::operator()(point p, time t) const {
		return {this->call<0>(p, t), this->call<1>(p, t)};
	}

	line PointLine::operator()(point p, time t) const {
		return {this->call<0>(p, t), this->call<1>(p, t)};
	}
}}
