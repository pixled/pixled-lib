#ifndef ANIMATION_H
#define ANIMATION_H

#include "api/animation.h"
#include "api/output.h"
#include "led.h"

namespace base {

	template<typename color_t>
	class RgbAnimation {


	};

	template<typename color_t, typename strip_t>
		class AnimationRuntime : public api::AnimationRuntime {
			private:
				api::Animation<color_t>& animation;
				unsigned long _time = 0;
				api::OutputFormat* format;
				strip_t strip;
				uint8_t* output;

			public:
				// TODO : default anim
				AnimationRuntime(
					int length,
					api::OutputFormat* format,
					api::Animation<color_t>& animation)
					: format(format), strip(length), animation(animation) {

				}

				AnimationRuntime(const AnimationRuntime&) = delete;
				AnimationRuntime(AnimationRuntime&&) = delete;
				AnimationRuntime& operator=(const AnimationRuntime&) = delete;
				AnimationRuntime& operator=(AnimationRuntime&&) = delete;

				unsigned long time() override {
					return _time;
				}

				void next() override {
					_time++;
					for(int x = 0; x < strip.getLength(); x ++) {
						animation.compute(strip[x].color(), x, _time);
					}
					strip.toArray(*format, output);
				}
				void prev() override {
					_time--;
					for(int x = 0; x < strip.getLength(); x ++) {
						animation.compute(strip[x].color(), x, _time);
					}
					strip.toArray(*format, output);
				}

				~AnimationRuntime() {
					//delete format;
				}
		};
}
#endif
