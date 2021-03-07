#ifndef PIXLED_FUNCTIONNAL_ARITHMETIC_H
#define PIXLED_FUNCTIONNAL_ARITHMETIC_H

#include "../api/functionnal.h"

namespace pixled {
	template<typename R, typename P1, typename P2>
		class Plus : public VarFunction<Plus<R, P1, P2>, R, P1, P2> {

			public:
				using VarFunction<Plus<R, P1, P2>, R, P1, P2>::VarFunction;

				R operator()(Point c, Time t) const override {
					return this->template call<0>(c, t) + this->template call<1>(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Plus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator+(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Plus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type,
			// P2
			typename std::remove_reference<Arg2>::type::Type> operator+(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Plus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type> operator+(Arg1&& f1, Arg2&& c2) {
			return {std::forward<Arg1>(f1), c2};
		}

	template<typename R, typename P1, typename P2>
		class Minus : public VarFunction<Minus<R, P1, P2>, R, P1, P2> {

			public:
				using VarFunction<Minus<R, P1, P2>, R, P1, P2>::VarFunction;

				R operator()(Point c, Time t) const override {
					return this->template call<0>(c, t) - this->template call<1>(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Minus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator-(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Minus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type,
			// P2
			typename std::remove_reference<Arg2>::type::Type> operator-(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Minus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type> operator-(Arg1&& f1, Arg2&& c2) {
			return {std::forward<Arg1>(f1), c2};
		}

	template<typename R, typename P1, typename P2>
		class Multiplies : public VarFunction<Multiplies<R, P1, P2>, R, P1, P2> {
			public:
				using VarFunction<Multiplies<R, P1, P2>, R, P1, P2>::VarFunction;

				R operator()(Point c, Time t) const override {
					return this->template call<0>(c, t) * this->template call<1>(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
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
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Multiplies<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator*(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Multiplies<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type> operator*(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename R, typename P1, typename P2>
		class Divides : public VarFunction<Divides<R, P1, P2>, R, P1, P2> {
			public:
				using VarFunction<Divides<R, P1, P2>, R, P1, P2>::VarFunction;

				R operator()(Point c, Time t) const override {
					return this->template call<0>(c, t) / this->template call<1>(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
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
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Divides<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator/(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Divides<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type
			> operator/(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), c2};
			}

	template<typename R, typename P1, typename P2>
		class Modulus : public VarFunction<Modulus<R, P1, P2>, R, P1, P2> {
			public:
				using VarFunction<Modulus<R, P1, P2>, R, P1, P2>::VarFunction;

				R operator()(Point c, Time t) const override {
					return this->template call<0>(c, t) % this->template call<1>(c, t);
				}
		};

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Modulus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator%(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Modulus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type,
				typename std::remove_reference<Arg2>::type::Type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type,
			// P2
			typename std::remove_reference<Arg2>::type::Type
			> operator%(Arg1&& c1, Arg2&& f2) {
				return {c1, std::forward<Arg2>(f2)};
			}

	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			Modulus<
			// R
			typename std::common_type<
				typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type
			>::type,
			// P1
			typename std::remove_reference<Arg1>::type::Type,
			// P2
			typename std::remove_reference<Arg2>::type
			> operator%(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), c2};
			}
}
#endif
