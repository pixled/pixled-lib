#include "pixel.h"


namespace pixled { namespace pixel {
	pixled::Color hsb::operator()(Point c, Time t) const {
		pixled::Color color;
		color.setHsb(this->call<0>(c, t), this->call<1>(c, t), this->call<2>(c, t));
		return color;
	}

	pixled::Color rgb::operator()(Point c, Time t) const {
		pixled::Color color;
		color.setRgb(this->call<0>(c, t), this->call<1>(c, t), this->call<2>(c, t));
		return color;
	}
}}
