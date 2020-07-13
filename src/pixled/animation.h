#ifndef ANIMATION_H
#define ANIMATION_H

#include "api/animation.h"
#include "api/output.h"
#include "pixel.h"
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

	class Runtime : public api::AnimationRuntime {
		private:
			unsigned long _time = 0;
			api::Mapping& map;
			api::Output& output;
			api::Function<Color>& animation;

		public:
			Runtime(api::Mapping& map, api::Output& output, api::Function<Color>& animation)
				: map(map), output(output), animation(animation) {}

			void frame(Time t) override {
				for(Coordinates c : map) {
					output.write(animation(c, t), map.map(c));
				}
			}

			void prev() override {
				frame(_time--);
			}
			void next() override {
				frame(_time++);
			}
			Time time() const override {
				return _time;
			}
	};
}
#endif
