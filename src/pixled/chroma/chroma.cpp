#include "chroma.h"


namespace pixled { namespace chroma {
	color hsb::operator()(led l, time t) const {
		return color::hsb(this->call<0>(l, t), this->call<1>(l, t), this->call<2>(l, t));
	}

	color rgb::operator()(led l, time t) const {
		return color::rgb(this->call<0>(l, t), this->call<1>(l, t), this->call<2>(l, t));
	}
}}
