#include "chroma.h"


namespace pixled { namespace chroma {
	color hsb::operator()(point c, time t) const {
		return color::hsb(this->call<0>(c, t), this->call<1>(c, t), this->call<2>(c, t));
	}

	color rgb::operator()(point c, time t) const {
		return color::rgb(this->call<0>(c, t), this->call<1>(c, t), this->call<2>(c, t));
	}
}}
