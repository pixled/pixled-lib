#ifndef FUNCTIONNAL_H
#define FUNCTIONNAL_H
#include "api/functionnal.h"
#include "led.h"
#include <cmath>

namespace pixled {
	class hsb : public api::Function<base::Color> {
		private:
			api::Function<float>& h;
			api::Function<float>& s;
			api::Function<float>& b;
		public:
			hsb(api::Function<float>& h, api::Function<float>& s, api::Function<float>& b)
				: h(h), s(s), b(b) {}

			base::Color operator()() const {
				base::Color color;
				color.setHsv(h(), s(), b());
				return color;
			}
	};

	class rgb : public api::Function<base::Color> {
		private:
			api::Function<uint8_t>& r;
			api::Function<uint8_t>& g;
			api::Function<uint8_t>& b;

		public:
			rgb(api::Function<uint8_t>& r, api::Function<uint8_t>& g, api::Function<uint8_t>& b)
				: r(r), g(g), b(b) {}

			base::Color operator()() const {
				base::Color color;
				color.setRgb(r(), g(), b());
				return color;
			}
	};

	template<typename T>
	class Constant : public api::Function<T> {
		private:
			T value;
		public:
			Constant(T& value) :
				value(value) {}
			T operator()() const {return value;};
	};

/*
 *    template<typename T>
 *        class Plus : public api::Function<T> {
 *            private:
 *                const api::Function<T>* f1;
 *                bool f1_owned = false;
 *                const api::Function<T>* f2;
 *                bool f2_owned = false;
 *
 *            public:
 *                Plus(const api::Function<T>& f1, const api::Function<T>& f2)
 *                    : f1(&f1), f2(&f2) {}
 *                Plus(const api::Function<T>&& f1, const api::Function<T>&& f2)
 *                    : f1(f1.copy()), f2(f2.copy()) {
 *                        f1_owned = true;
 *                        f2_owned = true;
 *                    }
 *
 *                T operator()() const override {
 *                    return (*f1)() + (*f2)();
 *                }
 *
 *                Plus<T>* copy() const override {
 *                    Plus<T>* copy = new Plus<T>(*f1, *f2);
 *                    copy->f1_owned = f1_owned;
 *                    copy->f2_owned = f2_owned;
 *                    return copy;
 *                }
 *
 *                ~Plus() {
 *                    if(f1_owned)
 *                        delete f1;
 *                    if(f2_owned)
 *                        delete f2;
 *                }
 *        };
 */
	template<typename T>
		class Plus : public api::BinaryFunction<T, Plus> {

			public:
				template<typename Arg1, typename Arg2>
					Plus(Arg1&& arg1, Arg2&& arg2)
						: api::BinaryFunction<T, Plus>(
								std::forward<Arg1>(arg1),
								std::forward<Arg2>(arg2))
					{}
				Plus(const Plus& other)
					: api::BinaryFunction<T, Plus>(other) {}

				Plus(Plus&& other)
					: api::BinaryFunction<T, Plus>(std::move(other)) {}

				Plus& operator=(const Plus& other) {
					api::BinaryFunction<T, Plus>::operator=(other);
					return *this;
				}

				Plus& operator=(Plus&& other) {
					api::BinaryFunction<T, Plus>::operator=(std::move(other));
					return *this;
				}
				/*
				 *Plus(const api::Function<T>& f1, const api::Function<T>& f2)
				 *    : f1(&f1), f2(&f2) {}
				 *Plus(const api::Function<T>&& f1, const api::Function<T>&& f2)
				 *    : f1(f1.copy()), f2(f2.copy()) {
				 *        f1_owned = true;
				 *        f2_owned = true;
				 *    }
				 */

				T operator()() const override {
					return (*this->f1)() + (*this->f2)();
				}
		};

	template<typename Arg1, typename Arg2>
	Plus<float> operator+(Arg1&& f1, Arg2&& f2) {
		return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
	}

	template<typename T>
		class sin : public api::Function<T> {
			private:
				api::Function<float>& f;
			public:
				sin(api::Function<float>& f) :
					f(f) {}
				T operator()() {
					return std::sin(f());
				}
		};

	template<typename T>
		class multiplies : public api::Function<T> {
			private:
				api::Function<T>& f1;
				api::Function<T>& f2;

			public:
				multiplies(api::Function<T>& f1, api::Function<T>& f2)
					: f1(f1), f2(f2) {}

				T operator()() {
					return f1() * f2();
				}
		};

	template<typename T>
		multiplies<T> operator*(api::Function<T>& f1, api::Function<T>& f2) {
			return {f1, f2};
		}
}

#endif
