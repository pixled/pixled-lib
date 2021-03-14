#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <map>
#include "../chrono/chrono.h"
#include "../signal/signal.h"
#include "../geometry/geometry.h"

namespace pixled { namespace animation {
	typedef FctWrapper<color> Animation;

	class SinT : public Function<SinT, float, time> {
		public:
			using Function<SinT, float, time>::Function;

			float operator()(point c, time t) const override;
	};
	/**
	 * A rainbow hue that depends on time, not on space.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param time rainbow period
	 */
	class Rainbow : public Function<Rainbow, float, time> {
		private:
			SinT sin {this->arg<0>()};

		public:
			using Function<Rainbow, float, time>::Function;

			float operator()(point c, time t) const override;
	};

	/**
	 * A linear rainbow wave using an Line as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param Line origin line
	 * @param time rainbow time period
	 */
	class RainbowWave : public Function<RainbowWave, float, float, line, time> {
		public:
			using Function<RainbowWave, float, float, line, time>::Function;

			float operator()(point p, time t) const override;
	};

	/**
	 * A linear rainbow wave using a vertical line as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param float position of the vertical origin line (X)
	 * @param time rainbow time period
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
	 * @param time rainbow time period
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
	 * @param point position of the origin point
	 * @param time rainbow time period
	 */
	class RadialRainbowWave : public Function<RadialRainbowWave, float, float, point, time> {
		public:
			using Function<RadialRainbowWave, float, float, point, time>::Function;
			
			float operator()(point p, time t) const override;
	};

	class SpatialUnitWave : public Function<SpatialUnitWave, float, float, line, time> {
		public:
			using Function<SpatialUnitWave, float, float, line, time>::Function;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(point p, time t) const override;
	};

	class UnitWaveX : public SpatialUnitWave {
		public:
			template<typename Arg1, typename Arg2>
				UnitWaveX(Arg1&& lambda, Arg2&& time_period)
				: SpatialUnitWave(std::forward<Arg1>(lambda), line(1, 0, 0), std::forward<Arg2>(time_period)) {}
	};

	class UnitWaveY : public SpatialUnitWave {
		public:
			template<typename Arg1, typename Arg2>
				UnitWaveY(Arg1&& lambda, Arg2&& time_period)
				: SpatialUnitWave(std::forward<Arg1>(lambda), line(0, 1, 0), std::forward<Arg2>(time_period)) {}
	};

	template<typename R>
		class Wave : public Function<Wave<R>, R, time, R, R> {
			public:
				using Function<Wave<R>, R, time, R, R>::Function;

				/*
				 * f1 : time period
				 * f2 : center value
				 * f3 : amplitude
				 */
				R operator()(point c, time t) const override {
					return this->template call<1>(c, t) + this->template call<2>(c, t) * std::sin(2*PIXLED_PI * t / this->template call<0>(c, t));
				}
		};

	class Blooming : public Function<Blooming, color, color, point, float> {
		public:
			using Function<Blooming, color, color, point, float>::Function;

			/*
			 * f1 : Input color
			 * f2 : Center point
			 * f3 : Bloom radius
			 */
			color operator()(point c, time t) const override;
	};

	class PixelView : public Function<PixelView, color, coordinate, coordinate, color> {
		public:
			using Function<PixelView, color, coordinate, coordinate, color>::Function;

			color operator()(point c, time t) const override;
	};

	struct SequenceItem {
		Animation anim;
		time duration;

		template<typename Anim>
			SequenceItem(Anim&& anim, time duration)
			: anim(std::forward<Anim>(anim)), duration(duration) {}
	};


	class Sequence : public base::Function<color> {
		private:
			std::map<time, FctWrapper<color>> animations;
			time duration = 0;

			mutable const FctWrapper<color>* cache;
			mutable time cache_time = 0;
			mutable time cache_time_duration = 0;
		public:
			Sequence(std::vector<SequenceItem> sequence) {
				for(auto item : sequence)
					this->add(item.anim, item.duration);
			}

			template<typename Anim>
			Sequence& add(Anim&& animation, time duration) {
				animations.insert({this->duration, std::forward<Anim>(animation)});
				cache_time = this->duration;
				cache = &animations.at(cache_time);
				this->duration+=duration;
				cache_time_duration=duration;
				return *this;
			}

			color operator()(point p, time t) const override;

			Sequence* copy() const override;
	};

	class Blink : public Function<Blink, color, color, float> {
		private:
			signal::Square square;
			color black;

		public:

			Blink(const std::tuple<
					const FctWrapper<color>,
					const FctWrapper<float>
					>& args)
				: Blink(*std::get<0>(args), *std::get<1>(args)) {}

			template<typename Arg1, typename Arg2>
				Blink(Arg1&& arg1, Arg2&& arg2) :
					Function<Blink, color, color, float>(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)),
					square(1, arg2, Cast<float, time>(chrono::T())) {
						black.setRgb(0, 0, 0);
					}

			color operator()(point p, time t) const override;
	};
}}
#endif
