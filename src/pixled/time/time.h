#ifndef PIXLED_TIME_TIME_H
#define PIXLED_TIME_TIME_H

#include "../function.h"

namespace pixled {
	class T : public base::Function<Time> {
		public:
			using Type = base::Function<Time>::Type;

			Time operator()(Point c, Time t) const override {
				return t;
			}

			T* copy() const override {return new T;}
	};
}
#endif
