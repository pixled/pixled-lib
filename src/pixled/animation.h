#ifndef ANIMATION_H
#define ANIMATION_H

#include "api/animation.h"
#include "api/output.h"
#include "pixel.h"
#include "functionnal.h"
#include "api/utils.h"

namespace pixled {

	class Rainbow : public api::UnaryFunction<float, Time, Rainbow> {
		public:
			using api::UnaryFunction<float, Time, Rainbow>::UnaryFunction;

			float operator()(api::Point c, Time t) const override {
				return 
					180.f * (std::sin(2*PIXLED_PI * t / (*this->f)(c, t)) + 1.f);
			}
	};

	class RainbowWave : public api::TernaryFunction<float, float, api::Line, Time, RainbowWave> {
		public:
			using api::TernaryFunction<float, float, api::Line, Time, RainbowWave>::TernaryFunction;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(api::Point p, Time t) const override {
				float d = LineDistance(*this->f2, p)(p, t);
				return 180.f * (1.f + std::sin(d / (*this->f1)(p, t) - (float) t / (*this->f3)(p, t)));
			}
	};

	class RainbowWaveX : public RainbowWave {
		public:
			template<typename Arg1, typename Arg2>
				RainbowWaveX(Arg1&& lambda, Arg2&& time_period)
				: RainbowWave(std::forward<Arg1>(lambda), api::Line(1, 0, 0), std::forward<Arg2>(time_period)) {}
	};

	class RainbowWaveY : public RainbowWave {
		public:
			template<typename Arg1, typename Arg2>
				RainbowWaveY(Arg1&& lambda, Arg2&& time_period)
				: RainbowWave(std::forward<Arg1>(lambda), api::Line(0, 1, 0), std::forward<Arg2>(time_period)) {}
	};


	template<typename R>
		class Wave : public api::TernaryFunction<R, Time, R, R, Wave<R>> {
			public:
				using api::TernaryFunction<R, Time, R, R, Wave<R>>::TernaryFunction;

				/*
				 * f1 : time period
				 * f2 : center value
				 * f3 : amplitude
				 */
				R operator()(api::Point c, Time t) const override {
					return (*this->f2)(c, t) + (*this->f3)(c, t) * std::sin(2*PIXLED_PI * t / (*this->f1)(c, t));
				}
		};

	class Blooming : public api::TernaryFunction<Color, Color, api::Point, float, Blooming> {
		public:
			using api::TernaryFunction<Color, Color, api::Point, float, Blooming>::TernaryFunction;

			/*
			 * f1 : Input color
			 * f2 : Center point
			 * f3 : Bloom radius
			 */
			Color operator()(api::Point c, Time t) const override {
				Color color = (*this->f1)(c, t);
				// Max distance from center point, where b = epsilon
				float D = (*this->f3)(c, t);
				// Distance from c to center point
				float d = Distance(*this->f2, c)(c, t);

				// The brightness decreases as a 1 / x light functions, scaled
				// so that when d = D, b = epsilon.
				float epsilon = 0.05;
				float alpha = (1 - epsilon) / (epsilon * D);
				float b = 1 / (1 + alpha * d);
				if(b < epsilon)
					b = 0.;

				color.setHsv(
					color.hue(),
					color.saturation(),
					b);
				return color;
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
				for(api::Point c : map) {
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

	class PixelView : public api::TernaryFunction<Color, Coordinate, Coordinate, Color, PixelView> {
		public:
			using api::TernaryFunction<Color, Coordinate, Coordinate, Color, PixelView>::TernaryFunction;

			Color operator()(api::Point c, Time t) const override {
				if (c.x == (*f1)(c, t) && c.y == (*f2)(c, t))
					return (*f3)(c, t);
				return Color();
			}
	};
}
#endif
