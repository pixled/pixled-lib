#ifndef ANIMATION_API_H
#define ANIMATION_API_H

#include "led.h"

typedef unsigned long Time;
namespace api {
	template<typename rgb_array_t>
		class Animation {
			public:
				virtual rgb_array_t& next() = 0;
				virtual rgb_array_t& prev() = 0;
		};
}
#endif
