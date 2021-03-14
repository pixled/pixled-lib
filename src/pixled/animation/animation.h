#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <map>
#include "../time/time.h"
#include "../signal/signal.h"
#include "../geometry/geometry.h"

namespace pixled { namespace animation {
	typedef FctWrapper<Color> Animation;

	class SinT : public Function<SinT, float, Time> {
		public:
			using Function<SinT, float, Time>::Function;

			float operator()(Point c, Time t) const override;
	};
	/**
	 * A rainbow hue that depends on time, not on space.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param Time rainbow period
	 */
	class Rainbow : public Function<Rainbow, float, Time> {
		private:
			SinT sin {this->arg<0>()};

		public:
			using Function<Rainbow, float, Time>::Function;

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
	class RainbowWave : public Function<RainbowWave, float, float, Line, Time> {
		public:
			using Function<RainbowWave, float, float, Line, Time>::Function;

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
	class RadialRainbowWave : public Function<RadialRainbowWave, float, float, Point, Time> {
		public:
			using Function<RadialRainbowWave, float, float, Point, Time>::Function;
			
			float operator()(Point p, Time t) const override;
	};

	class SpatialUnitWave : public Function<SpatialUnitWave, float, float, Line, Time> {
		public:
			using Function<SpatialUnitWave, float, float, Line, Time>::Function;

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
		class Wave : public Function<Wave<R>, R, Time, R, R> {
			public:
				using Function<Wave<R>, R, Time, R, R>::Function;

				/*
				 * f1 : time period
				 * f2 : center value
				 * f3 : amplitude
				 */
				R operator()(Point c, Time t) const override {
					return this->template call<1>(c, t) + this->template call<2>(c, t) * std::sin(2*PIXLED_PI * t / this->template call<0>(c, t));
				}
		};

	class Blooming : public Function<Blooming, Color, Color, Point, float> {
		public:
			using Function<Blooming, Color, Color, Point, float>::Function;

			/*
			 * f1 : Input color
			 * f2 : Center point
			 * f3 : Bloom radius
			 */
			Color operator()(Point c, Time t) const override;
	};

	class PixelView : public Function<PixelView, Color, Coordinate, Coordinate, Color> {
		public:
			using Function<PixelView, Color, Coordinate, Coordinate, Color>::Function;

			Color operator()(Point c, Time t) const override;
	};

	struct SequenceItem {
		Animation anim;
		Time duration;

		template<typename Anim>
			SequenceItem(Anim&& anim, Time duration)
			: anim(std::forward<Anim>(anim)), duration(duration) {}
	};


	class Sequence : public base::Function<Color> {
		private:
			std::map<Time, FctWrapper<Color>> animations;
			Time duration = 0;

			mutable const FctWrapper<Color>* cache;
			mutable Time cache_time = 0;
			mutable Time cache_time_duration = 0;
		public:
			Sequence(std::vector<SequenceItem> sequence) {
				for(auto item : sequence)
					this->add(item.anim, item.duration);
			}

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

	class Blink : public Function<Blink, Color, Color, float> {
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
					Function<Blink, Color, Color, float>(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)),
					square(1, arg2, Cast<float, Time>(T())) {
						black.setRgb(0, 0, 0);
					}

			Color operator()(Point p, Time t) const override;
	};
}}
#endif
