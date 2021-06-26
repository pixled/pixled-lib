#ifndef PIXLED_FUNCTIONNAL_ARITHMETIC_H
#define PIXLED_FUNCTIONNAL_ARITHMETIC_H

#include "../function.h"

namespace pixled { 
	namespace arithmetic {
		/**
		 * Plus operator implementation.
		 *
		 * @tparam R operation fundamental result type
		 * @tparam P1 fundamental left operand type
		 * @tparam P2 fundamental right operand type
		 */
		template<typename R, typename P1, typename P2>
			class Plus : public Function<Plus<R, P1, P2>, R, P1, P2> {

				public:
					using Function<Plus<R, P1, P2>, R, P1, P2>::Function;

					R operator()(point c, time t) const override {
						return this->template call<0>(c, t) + this->template call<1>(c, t);
					}
			};
	}

	/**
	 * \+ operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` or
	 * `Arg2` is an arithmetic type.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Plus instance that returns the common fundamental
	 * type between `Arg1::Type` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Plus<
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
	/**
	 * \+ operator definition, where `Arg1` is an arithmetic constant and
	 * `Arg2` is a \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` is
	 * not arithmetic or if `Arg2` is an arithmetic type.
	 *
	 * @param c1 left operand: arithmetic constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Plus instance that returns the common fundamental
	 * type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Plus<
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

	/**
	 * \+ operator definition, where `Arg1` is a \Function and `Arg2` is
	 * an arithmetic constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is skipped if Arg1 or
	 * Arg2 is an arithmetic type.
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Plus instance that returns the common fundamental
	 * type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Plus<
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

	namespace arithmetic {
		/**
		 * Minus operator implementation.
		 *
		 * @tparam R operation fundamental result type
		 * @tparam P1 fundamental left operand type
		 * @tparam P2 fundamental right operand type
		 */
		template<typename R, typename P1, typename P2>
			class Minus : public Function<Minus<R, P1, P2>, R, P1, P2> {

				public:
					using Function<Minus<R, P1, P2>, R, P1, P2>::Function;

					R operator()(point c, time t) const override {
						return this->template call<0>(c, t) - this->template call<1>(c, t);
					}
			};
	}

	/**
	 * \- operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` or
	 * `Arg2` is an arithmetic type.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Minus instance that returns the common fundamental
	 * type between `Arg1::Type` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Minus<
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

	/**
	 * \- operator definition, where `Arg1` is an arithmetic constant and
	 * `Arg2` is a \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` is
	 * not arithmetic or if `Arg2` is an arithmetic type.
	 *
	 * @param c1 left operand: arithmetic constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Minus instance that returns the common fundamental
	 * type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Minus<
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

	/**
	 * \- operator definition, where `Arg1` is a \Function and `Arg2` is
	 * an arithmetic constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is skipped if Arg1 or
	 * Arg2 is an arithmetic type.
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Minus instance that returns the common fundamental
	 * type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Minus<
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

	namespace arithmetic {
		/**
		 * Multiply operator implementation.
		 *
		 * @tparam R operation fundamental result type
		 * @tparam P1 fundamental left operand type
		 * @tparam P2 fundamental right operand type
		 */
		template<typename R, typename P1, typename P2>
			class Multiplies : public Function<Multiplies<R, P1, P2>, R, P1, P2> {
				public:
					using Function<Multiplies<R, P1, P2>, R, P1, P2>::Function;

					R operator()(point c, time t) const override {
						return this->template call<0>(c, t) * this->template call<1>(c, t);
					}
			};
	}

	/**
	 * \* operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` or
	 * `Arg2` is an arithmetic type.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Multiplies instance that returns the common
	 * fundamental type between `Arg1::Type` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Multiplies<
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
	/**
	 * \* operator definition, where `Arg1` is an arithmetic constant and
	 * `Arg2` is a \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` is
	 * not arithmetic or if `Arg2` is an arithmetic type.
	 *
	 * @param c1 left operand: arithmetic constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Multiplies instance that returns the common
	 * fundamental type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Multiplies<
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

	/**
	 * \* operator definition, where `Arg1` is a \Function and `Arg2` is
	 * an arithmetic constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is skipped if Arg1 or
	 * Arg2 is an arithmetic type.
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Multiplies instance that returns the common
	 * fundamental type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Multiplies<
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

	namespace arithmetic {
		/**
		 * Divide operator implementation.
		 *
		 * If the common operands type is integer, the algebraic quotient is
		 * returned. If the common type is floating, a regular floating-point
		 * division.
		 *
		 * @tparam R operation fundamental result type
		 * @tparam P1 fundamental left operand type
		 * @tparam P2 fundamental right operand type
		 */
		template<typename R, typename P1, typename P2>
			class Divides : public Function<Divides<R, P1, P2>, R, P1, P2> {
				public:
					using Function<Divides<R, P1, P2>, R, P1, P2>::Function;

					R operator()(point c, time t) const override {
						return this->template call<0>(c, t) / this->template call<1>(c, t);
					}
			};
	}

	/**
	 * / operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` or
	 * `Arg2` is an arithmetic type.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Divide instance that returns the common
	 * fundamental type between `Arg1::Type` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Divides<
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
	/**
	 * / operator definition, where `Arg1` is an arithmetic constant and
	 * `Arg2` is a \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` is
	 * not arithmetic or if `Arg2` is an arithmetic type.
	 *
	 * @param c1 left operand: arithmetic constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Divide instance that returns the common
	 * fundamental type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Divides<
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
	/**
	 * / operator definition, where `Arg1` is a \Function and `Arg2` is
	 * an arithmetic constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is skipped if Arg1 or
	 * Arg2 is an arithmetic type.
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Divide instance that returns the common
	 * fundamental type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Divides<
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

	namespace arithmetic {
		/**
		 * Modulus operator implementation, defined only for integer types.
		 *
		 * @tparam R operation fundamental integer result type
		 * @tparam P1 fundamental integer left operand type
		 * @tparam P2 fundamental integer right operand type
		 */
		template<typename R, typename P1, typename P2>
			class Modulus : public Function<Modulus<R, P1, P2>, R, P1, P2> {
				public:
					using Function<Modulus<R, P1, P2>, R, P1, P2>::Function;

					R operator()(point c, time t) const override {
						return this->template call<0>(c, t) % this->template call<1>(c, t);
					}
			};
	}
	/**
	 * % operator definition (modulus), where `Arg1` and `Arg2` are \Functions
	 * returning integer types.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` or
	 * `Arg2` is an arithmetic type.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Modulus instance that returns the common fundamental
	 * type between `Arg1::Type` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Modulus<
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
	/**
	 * % operator definition, where `Arg1` is an integer constant and
	 * `Arg2` is a \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is skipped if `Arg1` is
	 * not arithmetic or if `Arg2` is an arithmetic type.
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Modulus instance that returns the common fundamental
	 * type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& !std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Modulus<
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
	/**
	 * % operator definition, where `Arg1` is a \Function and `Arg2` is
	 * an integer constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is skipped if Arg1 or
	 * Arg2 is an arithmetic type.
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return an arithmetic::Modulus instance that returns the common fundamental
	 * type between `Arg1` and `Arg2::Type`.
	 */
	template<typename Arg1, typename Arg2,
		typename Enable = typename std::enable_if<
			!std::is_arithmetic<typename std::remove_reference<Arg1>::type>::value
				&& std::is_arithmetic<typename std::remove_reference<Arg2>::type>::value>::type>
			arithmetic::Modulus<
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
