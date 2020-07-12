#ifndef FUNCTIONNAL_H
#define FUNCTIONNAL_H
#include "api/functionnal.h"
#include "api/utils.h"
#include "led.h"
#include <cmath>

namespace pixled {
	using api::Coordinates;

	class X : public api::Function<Coordinate> {
		public:
			using Type = api::Function<Coordinate>::Type;

			Coordinate operator()(Coordinates c, Time t) const override {
				return c.x;
			}

			X* copy() const override {return new X;}
	};

	class Y : public api::Function<Coordinate> {
		public:
			using Type = api::Function<Coordinate>::Type;

			Coordinate operator()(Coordinates c, Time t) const override {
				return c.y;
			}

			Y* copy() const override {return new Y;}
	};

	class T : public api::Function<Time> {
		public:
			using Type = api::Function<Time>::Type;

			Time operator()(Coordinates c, Time t) const override {
				return t;
			}

			T* copy() const override {return new T;}
	};

	class hsb : public api::TernaryFunction<pixled::Color, float, float, float, hsb> {
		public:
			using api::TernaryFunction<pixled::Color, float, float, float, hsb>::TernaryFunction;

			pixled::Color operator()(Coordinates c, Time t) const override {
				pixled::Color color;
				color.setHsv((*f1)(c, t), (*f2)(c, t), (*f3)(c, t));
				return color;
			}
	};

	class rgb : public api::TernaryFunction<pixled::Color, uint8_t, uint8_t, uint8_t, rgb> {
		public:
			using api::TernaryFunction<pixled::Color, uint8_t, uint8_t, uint8_t, rgb>::TernaryFunction;

			pixled::Color operator()(Coordinates c, Time t) const override {
				pixled::Color color;
				color.setRgb((*f1)(c, t), (*f2)(c, t), (*f3)(c, t));
				return color;
			}
	};

	template<typename T1, typename T2>
		class OpType {};

	template<typename R, typename P1, typename P2>
		class Plus : public api::BinaryFunction<R, P1, P2, Plus<R, P1, P2>> {

			public:
				using api::BinaryFunction<R, P1, P2, Plus<R, P1, P2>>::BinaryFunction;

				R operator()(Coordinates c, Time t) const override {
					return (*this->f1)(c, t) + (*this->f2)(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Plus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg1>::type::Type
			> operator+(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Plus<
			// R
			typename std::common_type<
				Arg1,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			Arg1,
			// P2
			typename std::remove_reference<Arg2>::type::Type> operator+(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && std::is_arithmetic<Arg2>::value>::type>
			Plus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				Arg2
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			Arg2> operator+(Arg1&& f1, Arg2&& c2) {
			return {std::forward<Arg1>(f1), c2};
		}

	template<typename R, typename P1, typename P2>
		class Multiplies : public api::BinaryFunction<R, P1, P2, Multiplies<R, P1, P2>> {
			public:
				using api::BinaryFunction<R, P1, P2, Multiplies<R, P1, P2>>::BinaryFunction;

				R operator()(Coordinates c, Time t) const override {
					return (*this->f1)(c, t) * (*this->f2)(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Multiplies<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator*(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Multiplies<
			// R
			typename std::common_type<
				Arg1,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			Arg1,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator*(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && std::is_arithmetic<Arg2>::value>::type>
			Multiplies<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				Arg2
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			Arg2> operator*(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename R, typename P1, typename P2>
		class Divides : public api::BinaryFunction<R, P1, P2, Divides<R, P1, P2>> {
			public:
				using api::BinaryFunction<R, P1, P2, Divides<R, P1, P2>>::BinaryFunction;

				R operator()(Coordinates c, Time t) const override {
					return (*this->f1)(c, t) / (*this->f2)(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Divides<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator/(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<Arg1>::value && !std::is_arithmetic<Arg2>::value>::type>
			Divides<
			// R
			typename std::common_type<
				Arg1,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			Arg1,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator/(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<Arg1>::value && std::is_arithmetic<Arg2>::value>::type>
			Divides<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				Arg2
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			Arg2
			> operator/(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename T>
		class Sin : public api::UnaryFunction<T, T, Sin<T>> {
			public:
				using api::UnaryFunction<T, T, Sin>::UnaryFunction;

				T operator()(Coordinates c, Time t) const override {
					return std::sin((*this->f)(c, t));
				}
		};
}

#endif
