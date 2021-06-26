#ifndef PIXLED_TIME_TIME_H
#define PIXLED_TIME_TIME_H

#include "../function.h"

namespace pixled {
	/**
	 * Namespace containing time related functions.
	 */
	namespace chrono {
		/**
		 * \Function that returns the current time.
		 */
		class T : public base::Function<time> {
			public:
				time operator()(point c, time t) const override {
					return t;
				}

				T* copy() const override {return new T;}
		};
	}
}
#endif
