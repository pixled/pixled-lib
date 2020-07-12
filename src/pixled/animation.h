#ifndef ANIMATION_H
#define ANIMATION_H

#include <numbers>

#include "api/animation.h"
#include "api/output.h"
#include "led.h"
#include "functionnal.h"
#include "api/utils.h"

namespace pixled {

	class Rainbow : public pixled::hsb {
		public:
			template<typename Arg1, typename Arg2, typename Arg3>
				Rainbow(Arg1&& period, Arg2&& s, Arg3&& b)
				: hsb(
						180.f * (pixled::Sin<float>(2*PIXLED_PI * T() / std::forward<Arg1>(period)) + 1.f),
						std::forward<Arg2>(s),
						std::forward<Arg3>(b)) {
				}
	};

	class AnimationRuntime : public api::AnimationRuntime {
		private:
			unsigned long _time = 0;
			api::OutputFormat* format;
			pixled::Strip strip;
			api::Animation& animation;
			uint8_t* output;

		public:
			// TODO : default anim
			AnimationRuntime(
					int length,
					api::OutputFormat* format,
					api::Animation& animation)
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
