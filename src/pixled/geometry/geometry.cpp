#include "geometry.h"


namespace pixled { namespace geometry {

	float Distance::operator()(led l, time t) const {
		point c1 = this->call<0>(l, t);
		point c2 = this->call<1>(l, t);
		return std::sqrt(std::pow(c2.y - c1.y, 2) + std::pow(c2.x - c1.x, 2));
	}

	float LineDistance::operator()(led l, time t) const {
		line _l = this->call<0>(l, t);
		point point = this->call<1>(l, t);
		return std::abs(_l.a * point.x + _l.b * point.y + _l.c) /
			std::sqrt(std::pow(_l.a, 2) + std::pow(_l.b, 2));
	}

	point Point::operator()(led l, time t) const {
		return {this->call<0>(l, t), this->call<1>(l, t)};
	}

	angle AngleDeg::operator()(led l, time t) const {
		return angle::fromDeg(this->call<0>(l, t));
	}

	angle AngleRad::operator()(led l, time t) const {
		return angle::fromRad(this->call<0>(l, t));
	}

	line Line::operator()(led l, time t) const {
		return {this->call<0>(l, t), this->call<1>(l, t), this->call<2>(l, t)};
	}

	line XLine::operator()(led l, time t) const {
		return {1, 0, -this->call<0>(l, t)};
	}

	line YLine::operator()(led l, time t) const {
		return {0, 1, -this->call<0>(l, t)};
	}

	line AlphaLine::operator()(led l, time t) const {
		return {this->call<0>(l, t), this->call<1>(l, t)};
	}

	line PointLine::operator()(led l, time t) const {
		return {this->call<0>(l, t), this->call<1>(l, t)};
	}
}}
