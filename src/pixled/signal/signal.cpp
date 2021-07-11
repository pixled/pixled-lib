#include "signal.h"

namespace pixled { namespace signal {

	float Sine::operator()(led l, time t) const {
		return std::sin(2*PI * this->call<0>(l, t));
	}

	float Square::operator()(led l, time t) const {
		return std::sin(2*PI * this->call<0>(l, t)) > 0 ? 1 : -1;
	}

	float Triangle::operator()(led l, time t) const {
		return 2 / PI * std::asin(std::sin(
					2*PI * this->call<0>(l, t)
					));
	}

	float Sawtooth::operator()(led l, time t) const {
		return 2 / PI * std::atan(std::tan(
					2*PI * this->call<0>(l, t)
					));
	}
}}
