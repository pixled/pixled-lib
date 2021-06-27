#ifndef PIXLED_FUNCTIONNAL_RANDOM_H
#define PIXLED_FUNCTIONNAL_RANDOM_H

#include <random>
#include <unordered_map>

#include "../function.h"

namespace pixled {
	/**
	 * Random engine pixled fundamental type.
	 */
	typedef std::minstd_rand random_engine;
}

namespace pixled { namespace random {
	/**
	 * A class storing the two parameters required to define a random engine: a
	 * period and a seed.
	 *
	 * The period defines the frame count during which the random engine stays
	 * in its current state.
	 *
	 * The seed can be used to generate different random sequences.
	 *
	 * Note that this class does not generate any random number, it just stores
	 * some configuration.
	 */
	class RandomEngineConfig {
		protected:
			/**
			 * Random engine period.
			 *
			 * The random value of the engine effectively changes at each
			 * period.
			 */
			time period;
			/**
			 * Seed used to initiate the random number sequence.
			 */
			unsigned long seed;

		public:
			/**
			 * RandomEngineConfig constructor.
			 *
			 * The `seed` is initialized randomly using an
			 * [std::random_device][https://en.cppreference.com/w/cpp/numeric/random/random_device)
			 * instance.
			 *
			 * @param period random engine period
			 */
			RandomEngineConfig(time period)
				: period(period) {
					std::random_device rd_seeder;
					std::uniform_int_distribution<unsigned long> rd_seed;
					seed = rd_seed(rd_seeder);
				}
			/**
			 * RandomEngineConfig constructor.
			 *
			 * @param period random engine period
			 * @param seed random engine seed
			 */
			RandomEngineConfig(time period, unsigned long seed)
				: period(period), seed(seed) {}
	};

	/**
	 * A time dependent random engine.
	 *
	 * The sequence of generated values varies in time, but is the same for any
	 * point.
	 */
	class RandomT : public base::Function<random_engine>, RandomEngineConfig {
		private:
			mutable time current_period = 0;
			mutable random_engine rd {this->seed};
		public:
			using RandomEngineConfig::RandomEngineConfig;

			random_engine operator()(point p, time t) const override;

			RandomT* copy() const override {
				return new RandomT(period, seed);
			}
	};

	/**
	 * A time/space dependent random engine.
	 *
	 * The sequence of values not only varies in time, but is also unique on
	 * each point of the 2D environment.
	 */
	class RandomXYT : public base::Function<random_engine>, RandomEngineConfig {
		private:
			mutable time current_period = 0;
			mutable random_engine rd_seeder {this->seed};
			mutable std::uniform_int_distribution<unsigned long> rd_seed;
			mutable std::unordered_map<point, random_engine, point_hash, point_equal> rds;
		public:
			using RandomEngineConfig::RandomEngineConfig;

			/*
			 * f = period 
			 */
			random_engine operator()(point p, time t) const override;

			RandomXYT* copy() const override {
				return new RandomXYT(period, seed);
			}
	};

	/**
	 * An random uniform distribution of numbers.
	 *
	 * @param R lower bound
	 * @param R upper bound
	 * @param random_engine random engine passed to the distribution (see
	 * RandomT, RandomXYT) 
	 * @return a value in the specified interval, distributed according an
	 * uniform distribution.
	 */
	template<typename R>
		class UniformDistribution :
			public Function<UniformDistribution<R>, R, R, R, random_engine> {
				public:
					using Function<UniformDistribution<R>, R, R, R, random_engine>::Function;

					/*
					 * f1 = min
					 * f2 = max
					 * f3 = random engine
					 */
					R operator()(point p, time t) const override {
						std::uniform_real_distribution<float> random_real (
								this->template call<0>(p, t), this->template call<1>(p, t)
								);
						auto engine = this->template call<2>(p, t);
						return random_real(engine);
					}
			};
	/**
	 * An random normal distribution of numbers.
	 *
	 * @param float mean value (μ) 
	 * @param float standard deviation (σ)
	 * @param random_engine random engine passed to the distribution (see
	 * RandomT, RandomXYT) 
	 * @return a value distributed according a normal distribution.
	 */
	template<typename R>
	class NormalDistribution : public Function<NormalDistribution<R>, R, float, float, random_engine> {
		public:
			using Function<NormalDistribution<R>, R, float, float, std::minstd_rand>::Function;

			/*
			 * f1 = min
			 * f2 = max
			 * f3 = random engine
			 */
			R operator()(point p, time t) const override {
				std::normal_distribution<float> random_real (
						this->template call<0>(p, t), this->template call<1>(p, t)
						);
				auto engine = this->template call<2>(p, t);
				return random_real(engine);
			}
	};
}}
#endif
