#ifndef FUNCTIONNAL_H
#define FUNCTIONNAL_H
#include "api/functionnal.h"
#include "api/utils.h"
#include "led.h"
#include <cmath>

namespace pixled {
	using api::Coordinates;

	class hsb : public api::TernaryFunction<base::Color, float, float, float, hsb> {
		public:
			using api::TernaryFunction<base::Color, float, float, float, hsb>::TernaryFunction;

			base::Color operator()(Coordinates c, Time t) const override {
				base::Color color;
				color.setHsv((*f1)(c, t), (*f2)(c, t), (*f3)(c, t));
				return color;
			}
	};

	class rgb : public api::TernaryFunction<base::Color, uint8_t, uint8_t, uint8_t, rgb> {
		public:
			using api::TernaryFunction<base::Color, uint8_t, uint8_t, uint8_t, rgb>::TernaryFunction;

			base::Color operator()(Coordinates c, Time t) const override {
				base::Color color;
				color.setRgb((*f1)(c, t), (*f2)(c, t), (*f3)(c, t));
				return color;
			}
	};

	template<typename T>
		class Plus : public api::BinaryFunction<T, Plus> {

			public:
				using api::BinaryFunction<T, Plus>::BinaryFunction;

				T operator()(Coordinates c, Time t) const override {
					return (*this->f1)(c, t) + (*this->f2)(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Plus<typename std::remove_reference<Arg1>::type::Type> operator+(Arg1&& f1, Arg2&& f2) {
				static_assert(std::is_same<
						typename std::remove_reference<Arg1>::type::Type,
						typename std::remove_reference<Arg2>::type::Type>::value,
						"The two argument functions must return the same type of values.");
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Plus<Arg1> operator+(Arg1&& c1, Arg2&& f2) {
				static_assert(std::is_same<
				Arg1, typename std::remove_reference<Arg2>::type::Type>::value,
				"The two argument functions must return the same type of values.");
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && std::is_arithmetic<Arg2>::value>::type>
			Plus<Arg2> operator+(Arg1&& f1, Arg2&& c2) {
				static_assert(std::is_same<
						typename std::remove_reference<Arg1>::type::Type, Arg2>::value,
						"The two argument functions must return the same type of values.");
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename T>
		class Multiplies : public api::BinaryFunction<T, Multiplies> {
			public:
				using api::BinaryFunction<T, Multiplies>::BinaryFunction;

				T operator()(Coordinates c, Time t) const override {
					return (*this->f1)(c, t) * (*this->f2)(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Multiplies<typename std::remove_reference<Arg1>::type::Type> operator*(Arg1&& f1, Arg2&& f2) {
				static_assert(std::is_same<
						typename std::remove_reference<Arg1>::type::Type,
						typename std::remove_reference<Arg2>::type::Type>::value,
						"The two argument functions must return the same type of values.");
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Multiplies<Arg1> operator*(Arg1&& c1, Arg2&& f2) {
				static_assert(std::is_same<
				Arg1, typename std::remove_reference<Arg2>::type::Type>::value,
				"The two argument functions must return the same type of values.");
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && std::is_arithmetic<Arg2>::value>::type>
			Multiplies<Arg2> operator*(Arg1&& f1, Arg2&& c2) {
				static_assert(std::is_same<
						typename std::remove_reference<Arg1>::type::Type, Arg2>::value,
						"The two argument functions must return the same type of values.");
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename T>
		class Divides : public api::BinaryFunction<T, Divides> {
			public:
				using api::BinaryFunction<T, Divides>::BinaryFunction;

				T operator()(Coordinates c, Time t) const override {
					return (*this->f1)(c, t) / (*this->f2)(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Divides<typename std::remove_reference<Arg1>::type::Type> operator/(Arg1&& f1, Arg2&& f2) {
				static_assert(std::is_same<
						typename std::remove_reference<Arg1>::type::Type,
						typename std::remove_reference<Arg2>::type::Type>::value,
						"The two argument functions must return the same type of values.");
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Divides<Arg1> operator/(Arg1&& c1, Arg2&& f2) {
				static_assert(std::is_same<
				Arg1, typename std::remove_reference<Arg2>::type::Type>::value,
				"The two argument functions must return the same type of values.");
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && std::is_arithmetic<Arg2>::value>::type>
			Divides<Arg2> operator/(Arg1&& f1, Arg2&& c2) {
				static_assert(std::is_same<
						typename std::remove_reference<Arg1>::type::Type, Arg2>::value,
						"The two argument functions must return the same type of values.");
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename T>
		class Sin : public api::UnaryFunction<T, Sin> {
			public:
				using api::UnaryFunction<T, Sin>::UnaryFunction;

				T operator()(Coordinates c, Time t) const override {
					return std::sin((*this->f)(c, t));
				}
		};

	template<typename T>
		class SinT : public api::BinaryFunction<T, SinT> {
			public:
				//IMPLEM_BINARY(SinT)
				using api::BinaryFunction<T, SinT>::BinaryFunction;

				T operator()(Coordinates c, Time t) const override {
					return std::sin(2 * PIXLED_PI * t / (*this->f1)(c, t) + (*this->f2)(c, t));
				}
		};
}

#endif
