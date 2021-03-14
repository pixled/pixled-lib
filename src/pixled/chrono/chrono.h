#ifndef PIXLED_TIME_TIME_H
#define PIXLED_TIME_TIME_H

#include "../function.h"

namespace pixled { namespace chrono {
	class T : public base::Function<time> {
		public:
			using Type = base::Function<time>::Type;

			time operator()(point c, time t) const override {
				return t;
			}

			T* copy() const override {return new T;}
	};
}}
#endif
