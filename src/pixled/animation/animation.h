#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <map>
#include "../chrono/chrono.h"
#include "../signal/signal.h"
#include "../geometry/geometry.h"
#include "../signal/signal.h"
#include "../arithmetic/arithmetic.h"

namespace pixled { namespace animation {

	/**
	 * A time dependent sine wave.
	 *
	 * The wave is such that the value returned varies in time with a sine
	 * shape of the specified `time period` around the `center value` with the
	 * given `amplitude`, such as the maximum value of the wave is `center
	 * value + amplitude` and the minimum value is `center value - amplitude`.
	 *
	 * @tparam R numeric return type (e.g. float, coordinate, time, uint8_t...)
	 *
	 * @retval R time dependent wave
	 * @param time time period
	 * @param R center value
	 * @param R amplitude
	 */
	template<typename R>
		class Wave : public Function<Wave<R>, R, time, R, R> {
			public:
				using Function<Wave<R>, R, time, R, R>::Function;

				R operator()(led l, time t) const override {
					return this->template call<1>(l, t)
						+ this->template call<2>(l, t) * std::sin(
								2*PI * t / this->template call<0>(l, t)
								);
				}
		};

	/**
	 * A progressive wave that propagates from a line.
	 *
	 * @retval float progressive wave
	 * @param coordinate spatial period (_lambda_)
	 * @param time time period (_T_)
	 * @param line origin of the wave
	 */
	class LinearUnitWave : public Function<LinearUnitWave, float, coordinate, time, line> {
		public:
			using Function<LinearUnitWave, float, coordinate, time, line>::Function;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(led l, time t) const override;
	};

	/**
	 * A progressive wave that propagates from a point.
	 *
	 * @retval float progressive wave
	 * @param coordinate spatial period (_lambda_)
	 * @param time time period (_T_)
	 * @param point origin of the wave
	 */
	class RadialUnitWave : public Function<RadialUnitWave, float, coordinate, time, point> {
		public:
			using Function<RadialUnitWave, float, coordinate, time, point>::Function;

			/*
			 * f1 : lambda
			 * f2 : origin line
			 * f3 : time period
			 */
			float operator()(led l, time t) const override;
	};

	/**
	 * A rainbow hue that varies between 0 and 360 in time with a sine shape.
	 *
	 * @param time rainbow period
	 * @retval float rainbow hue in `[0, 360]`
	 */
	class Rainbow : public Function<Rainbow, float, time> {
		private:
			signal::Sine sin {
				Cast<float>(chrono::T()) / Cast<float>(this->arg<0>())
			};

		public:
			using Function<Rainbow, float, time>::Function;

			float operator()(led l, time t) const override;
	};

	/**
	 * A progressive rainbow wave that propagates from a line.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param time rainbow time period
	 * @param line origin line
	 */
	class RainbowWave : public Function<RainbowWave, float, float, time, line> {
		public:
			using Function<RainbowWave, float, float, time, line>::Function;

			float operator()(led l, time t) const override;
	};

	/**
	 * A rainbow wave using a point as origin.
	 *
	 * @retval float rainbow hue in `[0, 360]`
	 * @param float spatial period of the wave
	 * @param time rainbow time period
	 * @param point position of the origin point
	 */
	class RadialRainbowWave : public Function<RadialRainbowWave, float, coordinate, time, point> {
		public:
			using Function<RadialRainbowWave, float, coordinate, time, point>::Function;

			float operator()(led l, time t) const override;
	};

	/**
	 * The brightness of the input animation is set to a circle, decreasing
	 * from the center according to the radius parameter.
	 *
	 * @retval color bloomed color
	 * @param color input animation
	 * @param point center
	 * @param coordinate blooming radius
	 */
	class Blooming : public Function<Blooming, color, color, point, coordinate> {
		public:
			using Function<Blooming, color, color, point, coordinate>::Function;

			color operator()(led l, time t) const override;
	};


	/**
	 * Blink animation.
	 *
	 * @retval color blinked animation
	 * @param color origin animation
	 * @param time period
	 */
	class Blink : public Function<Blink, color, color, time> {
		private:
			signal::Square square {
				Cast<float>(chrono::T()) // parameter
				/ Cast<float>(this->arg<1>()) // period
			};
			color black {color::rgb(0, 0, 0)};

		public:
			using Function<Blink, color, color, time>::Function;

			color operator()(led l, time t) const override;
	};

	/**
	 * A Sequence item, that assign a duration to each Animation in the
	 * sequence.
	 */
	struct SequenceItem {
		/**
		 * An Animation in the Sequence.
		 */
		FctWrapper<color> animation;
		/**
		 * The duration of the animation in the Sequence.
		 */
		time duration;

		/**
		 * Sequence item constructor.
		 *
		 * @tparam Anim automatically deduced
		 * @param animation An Animation, passed by lvalue or rvalue
		 * @param duration Animation duration in the Sequence
		 */
		template<typename Anim>
			SequenceItem(Anim&& animation, time duration)
			: animation(std::forward<Anim>(animation)), duration(duration) {}
	};


	/**
	 * Defines a sequence of animations.
	 */
	class Sequence : public base::Function<color> {
		private:
			std::map<time, FctWrapper<color>> animations;
			time duration = 0;

			mutable const FctWrapper<color>* cache;
			mutable time cache_time = 0;
			mutable time cache_time_duration = 0;
		public:
			/**
			 * Initializes an emty Sequence.
			 *
			 * Sequence items can be added later using the add() method.
			 */
			Sequence() {
			}

			/**
			 * Sequence constructor.
			 *
			 * The sequence can be conveniently specified using initializer
			 * lists:
			 * ```cpp
			 * Sequence seq({
			 * 	{anim1, 10},
			 * 	{anim2, 15},
			 * 	{anim1, 10},
			 * 	{anim3, 20}
			 * 	});
			 * ```
			 *
			 * Sequence items can also be added later using the add() method.
			 *
			 * @param sequence a SequenceItem list describing the sequence.
			 */
			Sequence(std::vector<SequenceItem> sequence) {
				for(auto item : sequence)
					this->add(item.animation, item.duration);
			}

			/**
			 * Adds an item to the Sequence.
			 *
			 * ```cpp
			 * Sequence sequence;
			 * sequence
			 * 	.add(anim1, 10)
			 * 	.add(anim2, 15)
			 * 	.add(anim1, 10)
			 * 	.add(anim3, 20);
			 * ```
			 *
			 * @tparam Anim automatically deduced
			 * @param animation An Animation, passed by lvalue or rvalue
			 * @param duration Animation duration in the Sequence
			 * @return reference to the current sequence
			 */
			template<typename Anim>
				Sequence& add(Anim&& animation, time duration) {
					animations.insert({this->duration, std::forward<Anim>(animation)});
					cache_time = this->duration;
					cache = &animations.at(cache_time);
					this->duration+=duration;
					cache_time_duration=duration;
					return *this;
				}

			color operator()(led l, time t) const override;

			Sequence* copy() const override;
	};

}}
#endif
