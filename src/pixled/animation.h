#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include "api/animation.h"
#include "api/output.h"
#include "api/mapping.h"
#include "pixel.h"
#include "functionnal/functionnal.h"

namespace pixled {

	class Runtime : public api::AnimationRuntime {
		private:
			unsigned long _time = 0;
			api::Mapping& map;
			api::Output& output;
			api::Function<Color>& animation;

		public:
			Runtime(api::Mapping& map, api::Output& output, api::Function<Color>& animation)
				: map(map), output(output), animation(animation) {}

			void frame(Time t) override;

			void prev() override;
			void next() override;
			Time time() const override;
	};

	class Rainbow : public api::UnaryFunction<float, Time, Rainbow> {
		public:
			using api::UnaryFunction<float, Time, Rainbow>::UnaryFunction;

			float operator()(api::Point c, Time t) const override;
	};

	class RainbowWave : public api::TernaryFunction<float, float, api::Line, Time, RainbowWave> {
		public:
			using api::TernaryFunction<float, float, api::Line, Time, RainbowWave>::TernaryFunction;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(api::Point p, Time t) const override;
	};

	class RainbowWaveX : public RainbowWave {
		public:
			template<typename Arg1, typename Arg2, typename Arg3>
				RainbowWaveX(Arg1&& lambda, Arg2&& x, Arg3&& time_period)
				: RainbowWave(std::forward<Arg1>(lambda), api::Line(1, 0, -std::forward<Arg2>(x)), std::forward<Arg3>(time_period)) {}
	};

	class RainbowWaveY : public RainbowWave {
		public:
			template<typename Arg1, typename Arg2, typename Arg3>
				RainbowWaveY(Arg1&& lambda, Arg2&& y, Arg3&& time_period)
				: RainbowWave(std::forward<Arg1>(lambda), api::Line(0, 1, -std::forward<Arg2>(y)), std::forward<Arg3>(time_period)) {}
	};

	class RadialRainbowWave : public api::TernaryFunction<float, float, api::Point, Time, RadialRainbowWave> {
		public:
			using api::TernaryFunction<float, float, api::Point, Time, RadialRainbowWave>::TernaryFunction;
			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(api::Point p, Time t) const override;
	};

	class SpatialUnitWave : public api::TernaryFunction<float, float, api::Line, Time, SpatialUnitWave> {
		public:
			using api::TernaryFunction<float, float, api::Line, Time, SpatialUnitWave>::TernaryFunction;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(api::Point p, Time t) const override;
	};

	class UnitWaveX : public SpatialUnitWave {
		public:
			template<typename Arg1, typename Arg2>
				UnitWaveX(Arg1&& lambda, Arg2&& time_period)
				: SpatialUnitWave(std::forward<Arg1>(lambda), api::Line(1, 0, 0), std::forward<Arg2>(time_period)) {}
	};

	class UnitWaveY : public SpatialUnitWave {
		public:
			template<typename Arg1, typename Arg2>
				UnitWaveY(Arg1&& lambda, Arg2&& time_period)
				: SpatialUnitWave(std::forward<Arg1>(lambda), api::Line(0, 1, 0), std::forward<Arg2>(time_period)) {}
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
			Color operator()(api::Point c, Time t) const override;
	};

	class PixelView : public api::TernaryFunction<Color, Coordinate, Coordinate, Color, PixelView> {
		public:
			using api::TernaryFunction<Color, Coordinate, Coordinate, Color, PixelView>::TernaryFunction;

			Color operator()(api::Point c, Time t) const override;
	};

	class Sequence : public api::Function<Color> {
		private:
			std::map<Time, api::FctWrapper<Color>> animations;
			Time duration = 0;

			mutable const api::FctWrapper<Color>* cache;
			mutable Time cache_time = 0;
			mutable Time cache_time_duration = 0;
		public:
			template<typename Anim>
			Sequence& add(Anim&& animation, Time duration) {
				animations.insert({this->duration, std::forward<Anim>(animation)});
				cache_time = this->duration;
				cache = &animations.at(cache_time);
				this->duration+=duration;
				cache_time_duration=duration;
				return *this;
			}

			Color operator()(api::Point p, Time t) const override;

			Sequence* copy() const override;
	};

	class Blink : public api::BinaryFunction<Color, Color, float, Blink> {
		private:
			Square square;
			Color black;

		public:
			template<typename Arg1, typename Arg2>
				Blink(Arg1&& arg1, Arg2&& arg2) :
					BinaryFunction<Color, Color, float, Blink>(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)),
					square(1, arg2, api::Cast<float, Time>(T())) {
						black.setRgb(0, 0, 0);
					}

			Color operator()(api::Point p, Time t) const override;
	};
}
#endif
