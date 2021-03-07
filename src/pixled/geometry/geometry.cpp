#include "geometry.h"


namespace pixled { namespace geometry {

	float Distance::operator()(pixled::Point c, Time t) const {
		pixled::Point c1 = this->call<0>(c, t);
		pixled::Point c2 = this->call<1>(c, t);
		return std::sqrt(std::pow(c2.y - c1.y, 2) + std::pow(c2.x - c1.x, 2));
	}

	float LineDistance::operator()(pixled::Point p, Time t) const {
		pixled::Line line = this->call<0>(p, t);
		pixled::Point point = this->call<1>(p, t);
		return std::abs(line.a * point.x + line.b * point.y + line.c) /
			std::sqrt(std::pow(line.a, 2) + std::pow(line.b, 2));
	}

	pixled::Point Point::operator()(pixled::Point c, Time t) const {
		return {this->call<0>(c, t), this->call<1>(c, t)};
	}

	pixled::Line Line::operator()(pixled::Point p, Time t) const {
		return {this->call<0>(p, t), this->call<1>(p, t), this->call<2>(p, t)};
	}

	pixled::Line XLine::operator()(pixled::Point p, Time t) const {
		return {1, 0, -this->call<0>(p, t)};
	}

	pixled::Line YLine::operator()(pixled::Point p, Time t) const {
		return {0, 1, -this->call<0>(p, t)};
	}
}}
