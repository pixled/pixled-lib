#ifndef ANIMATION_H
#define ANIMATION_H

#include "api/animation.h"
#include "led.h"

namespace base {
	template<typename rgb_array_t, typename strip_t>
		class Animation : public api::Animation<rgb_array_t> {
			private:
				strip_t strip;
				rgb_array_t output;

			public:
				rgb_array_t& next() override {
					strip.toRgbArray(output);
					return output;
				}
				rgb_array_t& prev() override {
					strip.toRgbArray(output);
					return output;
				}
		};
}
#endif
