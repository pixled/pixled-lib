#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include "../time/time.h"
#include "../signal/signal.h"
#include "../geometry/geometry.h"

namespace pixled { namespace animation {
	/**
	 * A rainbow hue that depends on time, not on space.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param Time rainbow period
	 */
	class Rainbow : public VarFunction<Rainbow, float, Time> {
		public:
			using VarFunction<Rainbow, float, Time>::VarFunction;

			float operator()(Point c, Time t) const override;
	};

	/**
	 * A linear rainbow wave using an Line as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param Line origin line
	 * @param Time rainbow time period
	 */
	class RainbowWave : public VarFunction<RainbowWave, float, float, Line, Time> {
		public:
			using VarFunction<RainbowWave, float, float, Line, Time>::VarFunction;

			float operator()(Point p, Time t) const override;
	};

	/**
	 * A linear rainbow wave using a vertical line as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param float position of the vertical origin line (X)
	 * @param Time rainbow time period
	 */
	class RainbowWaveX : public RainbowWave {
		public:
			template<typename Arg1, typename Arg2, typename Arg3>
				RainbowWaveX(Arg1&& lambda, Arg2&& x, Arg3&& time_period)
				: RainbowWave(std::forward<Arg1>(lambda), Line(1, 0, -std::forward<Arg2>(x)), std::forward<Arg3>(time_period)) {}
	};

	/**
	 * A linear rainbow wave using an horizontal line as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param float position of the horizontal origin line (Y)
	 * @param Time rainbow time period
	 */
	class RainbowWaveY : public RainbowWave {
		public:
			template<typename Arg1, typename Arg2, typename Arg3>
				RainbowWaveY(Arg1&& lambda, Arg2&& y, Arg3&& time_period)
				: RainbowWave(std::forward<Arg1>(lambda), Line(0, 1, -std::forward<Arg2>(y)), std::forward<Arg3>(time_period)) {}
	};

	/**
	 * A rainbow wave using a point as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param Point position of the origin point
	 * @param Time rainbow time period
	 */
	class RadialRainbowWave : public VarFunction<RadialRainbowWave, float, float, Point, Time> {
		public:
			using VarFunction<RadialRainbowWave, float, float, Point, Time>::VarFunction;
			
			float operator()(Point p, Time t) const override;
	};

	class SpatialUnitWave : public VarFunction<SpatialUnitWave, float, float, Line, Time> {
		public:
			using VarFunction<SpatialUnitWave, float, float, Line, Time>::VarFunction;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(Point p, Time t) const override;
	};

	class UnitWaveX : public SpatialUnitWave {
		public:
			template<typename Arg1, typename Arg2>
				UnitWaveX(Arg1&& lambda, Arg2&& time_period)
				: SpatialUnitWave(std::forward<Arg1>(lambda), Line(1, 0, 0), std::forward<Arg2>(time_period)) {}
	};

	class UnitWaveY : public SpatialUnitWave {
		public:
			template<typename Arg1, typename Arg2>
				UnitWaveY(Arg1&& lambda, Arg2&& time_period)
				: SpatialUnitWave(std::forward<Arg1>(lambda), Line(0, 1, 0), std::forward<Arg2>(time_period)) {}
	};

	template<typename R>
		class Wave : public VarFunction<Wave<R>, R, Time, R, R> {
			public:
				using VarFunction<Wave<R>, R, Time, R, R>::VarFunction;

				/*
				 * f1 : time period
				 * f2 : center value
				 * f3 : amplitude
				 */
				R operator()(Point c, Time t) const override {
					return (*this->f2)(c, t) + (*this->f3)(c, t) * std::sin(2*PIXLED_PI * t / (*this->f1)(c, t));
				}
		};

	class Blooming : public VarFunction<Blooming, Color, Color, Point, float> {
		public:
			using VarFunction<Blooming, Color, Color, Point, float>::VarFunction;

			/*
			 * f1 : Input color
			 * f2 : Center point
			 * f3 : Bloom radius
			 */
			Color operator()(Point c, Time t) const override;
	};

	class PixelView : public VarFunction<PixelView, Color, Coordinate, Coordinate, Color> {
		public:
			using VarFunction<PixelView, Color, Coordinate, Coordinate, Color>::VarFunction;

			Color operator()(Point c, Time t) const override;
	};

	class Sequence : public base::Function<Color> {
		private:
			std::map<Time, FctWrapper<Color>> animations;
			Time duration = 0;

			mutable const FctWrapper<Color>* cache;
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

			Color operator()(Point p, Time t) const override;

			Sequence* copy() const override;
	};

	class Blink : public VarFunction<Blink, Color, Color, float> {
		private:
			signal::Square square;
			Color black;

		public:

			Blink(const std::tuple<
					const FctWrapper<Color>,
					const FctWrapper<float>
					>& args)
				: Blink(*std::get<0>(args), *std::get<1>(args)) {}

			template<typename Arg1, typename Arg2>
				Blink(Arg1&& arg1, Arg2&& arg2) :
					VarFunction<Blink, Color, Color, float>(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)),
					square(1, arg2, Cast<float, Time>(T())) {
						black.setRgb(0, 0, 0);
					}

			Color operator()(Point p, Time t) const override;
	};
}}
#endif
