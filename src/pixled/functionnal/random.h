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

	class RandomT : public api::Function<std::minstd_rand>, RandomEngine {
		public:
			mutable Time current_period = 0;
			mutable std::minstd_rand rd;

			RandomT(Time period)
				: RandomEngine(period), rd(this->seed) {}
			RandomT(Time period, unsigned long seed)
				: RandomEngine(period, seed), rd(seed) {}

			std::minstd_rand operator()(api::Point p, Time t) const override {
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

	class RandomXYT : public api::Function<std::minstd_rand>, RandomEngine {
		private:
			mutable Time current_period = 0;
			mutable std::minstd_rand rd_seeder;
			mutable std::uniform_int_distribution<unsigned long> rd_seed;
			mutable std::unordered_map<api::Point, std::minstd_rand, api::point_hash, api::point_equal> rds;
		public:
			using RandomEngine::RandomEngine;
			/*
			 * f = period 
			 */
			std::minstd_rand operator()(api::Point p, Time t) const override {
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
		class UniformDistribution : public api::TernaryFunction<R, R, R, std::minstd_rand, UniformDistribution<R>> {
			public:
				using api::TernaryFunction<R, R, R, std::minstd_rand, UniformDistribution<R>>::TernaryFunction;

				/*
				 * f1 = min
				 * f2 = max
				 * f3 = random engine
				 */
				R operator()(api::Point p, Time t) const override {
					std::uniform_real_distribution<float> random_real ((*this->f1)(p, t), (*this->f2)(p, t));
					auto engine = (*this->f3)(p, t);
					return random_real(engine);
				}
		};

	template<typename R>
	class NormalDistribution : public api::TernaryFunction<R, float, float, std::minstd_rand, NormalDistribution<R>> {
		public:
			using api::TernaryFunction<R, float, float, std::minstd_rand, NormalDistribution<R>>::TernaryFunction;

			/*
			 * f1 = min
			 * f2 = max
			 * f3 = random engine
			 */
			R operator()(api::Point p, Time t) const override {
				std::normal_distribution<float> random_real ((*this->f1)(p, t), (*this->f2)(p, t));
				auto engine = (*this->f3)(p, t);
				return random_real(engine);
			}
	};
}
#endif
