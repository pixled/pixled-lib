#ifndef PIXLED_FUNCTIONNAL_RANDOM_H
#define PIXLED_FUNCTIONNAL_RANDOM_H

#include <random>
#include <unordered_map>

#include "../function.h"

namespace pixled { namespace random {
	class RandomEngine {
		protected:
			Time period;
			unsigned long seed = 0;

		public:
			RandomEngine(Time period)
				: period(period) {
					std::random_device rd_seeder;
					std::uniform_int_distribution<unsigned long> rd_seed;
					seed = rd_seed(rd_seeder);
				}
			RandomEngine(Time period, unsigned long seed)
				: period(period), seed(seed) {}
	};

	class RandomT : public base::Function<std::minstd_rand>, RandomEngine {
		public:
			mutable Time current_period = 0;
			mutable std::minstd_rand rd;

			RandomT(Time period)
				: RandomEngine(period), rd(this->seed) {}
			RandomT(Time period, unsigned long seed)
				: RandomEngine(period, seed), rd(seed) {}

			std::minstd_rand operator()(Point p, Time t) const override;

			RandomT* copy() const override {
				return new RandomT(period, seed);
			}
	};

	class RandomXYT : public base::Function<std::minstd_rand>, RandomEngine {
		private:
			mutable Time current_period = 0;
			mutable std::minstd_rand rd_seeder;
			mutable std::uniform_int_distribution<unsigned long> rd_seed;
			mutable std::unordered_map<Point, std::minstd_rand, point_hash, point_equal> rds;
		public:
			using RandomEngine::RandomEngine;
			/*
			 * f = period 
			 */
			std::minstd_rand operator()(Point p, Time t) const override;

			RandomXYT* copy() const override {
				return new RandomXYT(period, seed);
			}
	};

	template<typename R>
		class UniformDistribution : public VarFunction<UniformDistribution<R>, R, R, R, std::minstd_rand> {
			public:
				using VarFunction<UniformDistribution<R>, R, R, R, std::minstd_rand>::VarFunction;

				/*
				 * f1 = min
				 * f2 = max
				 * f3 = random engine
				 */
				R operator()(Point p, Time t) const override {
					std::uniform_real_distribution<float> random_real (this->template call<0>(p, t), this->template call<1>(p, t));
					auto engine = this->template call<2>(p, t);
					return random_real(engine);
				}
		};

	template<typename R>
	class NormalDistribution : public VarFunction<NormalDistribution<R>, R, float, float, std::minstd_rand> {
		public:
			using VarFunction<NormalDistribution<R>, R, float, float, std::minstd_rand>::VarFunction;

			/*
			 * f1 = min
			 * f2 = max
			 * f3 = random engine
			 */
			R operator()(Point p, Time t) const override {
				std::normal_distribution<float> random_real (this->template call<0>(p, t), this->template call<1>(p, t));
				auto engine = this->template call<2>(p, t);
				return random_real(engine);
			}
	};
}}
#endif
