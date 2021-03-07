#ifndef PIXLED_FUNCTIONNAL_RANDOM_H
#define PIXLED_FUNCTIONNAL_RANDOM_H

#include <random>
#include <unordered_map>

#include "../api/functionnal.h"

namespace pixled {
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

			std::minstd_rand operator()(Point p, Time t) const override {
				Time _current_period = t / period;
				if(_current_period != current_period) {
					current_period = _current_period;
					rd.discard(1);
				}
				return rd;
			}

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
			std::minstd_rand operator()(Point p, Time t) const override {
				std::minstd_rand* rd;

				auto result = rds.find(p);
				if(result == rds.end()) {
					unsigned long _s = rd_seed(rd_seeder);
					// Inserts only if no entry exists yet for p
					auto inserted_item = rds.insert({p, std::minstd_rand(_s)});
					rd = &inserted_item.first->second;
				} else {
					rd = &result->second;
				}
				//std::cout << "rds size:" << rds.size() << std::endl;

				Time _current_period = t / period;
				if(_current_period != current_period) {
					current_period = _current_period;
					for(auto& _rd : rds) {
						// Advances
						_rd.second.discard(1);
					}
				}
				return *rd;
			}

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
}
#endif
