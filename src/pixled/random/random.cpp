#include "random.h"

namespace pixled { namespace random {

	std::minstd_rand RandomT::operator()(led l, time t) const {
		time _current_period = t / period;
		if(_current_period != current_period) {
			current_period = _current_period;
			rd.discard(1);
		}
		return rd;
	}

	std::minstd_rand RandomXYT::operator()(led l, time t) const {
		std::minstd_rand* rd;

		auto result = rds.find(l.index);
		if(result == rds.end()) {
			unsigned long _s = rd_seed(rd_seeder);
			// Inserts only if no entry exists yet for p
			auto inserted_item = rds.insert({l.index, std::minstd_rand(_s)});
			rd = &inserted_item.first->second;
		} else {
			rd = &result->second;
		}

		time _current_period = t / period;
		if(_current_period != current_period) {
			current_period = _current_period;
			for(auto& _rd : rds) {
				// Advances
				_rd.second.discard(1);
			}
		}
		return *rd;
	}


}}
