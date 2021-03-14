#ifndef PIXLED_FUNCTIONNAL_RANDOM_H
#define PIXLED_FUNCTIONNAL_RANDOM_H

#include <random>
#include <unordered_map>

#include "../function.h"

namespace pixled { namespace random {
	class RandomEngine {
		protected:
			time period;
			unsigned long seed = 0;

		public:
			RandomEngine(time period)
				: period(period) {
					std::random_device rd_seeder;
					std::uniform_int_distribution<unsigned long> rd_seed;
					seed = rd_seed(rd_seeder);
				}
			RandomEngine(time period, unsigned long seed)
				: period(period), seed(seed) {}
	};

	class RandomT : public base::Function<std::minstd_rand>, RandomEngine {
		public:
			mutable time current_period = 0;
			mutable std::minstd_rand rd;

			RandomT(time period)
				: RandomEngine(period), rd(this->seed) {}
			RandomT(time period, unsigned long seed)
				: RandomEngine(period, seed), rd(seed) {}

			std::minstd_rand operator()(point p, time t) const override;

			RandomT* copy() const override {
				return new RandomT(period, seed);
			}
	};

	class RandomXYT : public base::Function<std::minstd_rand>, RandomEngine {
		private:
			mutable time current_period = 0;
			mutable std::minstd_rand rd_seeder;
			mutable std::uniform_int_distribution<unsigned long> rd_seed;
			mutable std::unordered_map<point, std::minstd_rand, point_hash, point_equal> rds;
		public:
			using RandomEngine::RandomEngine;
			/*
			 * f = period 
			 */
			std::minstd_rand operator()(point p, time t) const override;

			RandomXYT* copy() const override {
				return new RandomXYT(period, seed);
			}
	};

	template<typename R>
		class UniformDistribution : public Function<UniformDistribution<R>, R, R, R, std::minstd_rand> {
			public:
				using Function<UniformDistribution<R>, R, R, R, std::minstd_rand>::Function;

				/*
				 * f1 = min
				 * f2 = max
				 * f3 = random engine
				 */
				R operator()(point p, time t) const override {
					std::uniform_real_distribution<float> random_real (this->template call<0>(p, t), this->template call<1>(p, t));
					auto engine = this->template call<2>(p, t);
					return random_real(engine);
				}
		};

	template<typename R>
	class NormalDistribution : public Function<NormalDistribution<R>, R, float, float, std::minstd_rand> {
		public:
			using Function<NormalDistribution<R>, R, float, float, std::minstd_rand>::Function;

			/*
			 * f1 = min
			 * f2 = max
			 * f3 = random engine
			 */
			R operator()(point p, time t) const override {
				std::normal_distribution<float> random_real (this->template call<0>(p, t), this->template call<1>(p, t));
				auto engine = this->template call<2>(p, t);
				return random_real(engine);
			}
	};
}}
#endif
