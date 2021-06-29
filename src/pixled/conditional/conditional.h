#ifndef PIXLED_FUNCTIONNAL_COMPARISONS_H
#define PIXLED_FUNCTIONNAL_COMPARISONS_H

#include "../function.h"
#include <type_traits>

namespace pixled { 
	namespace conditional {
		/**
		 * pixled If statement.
		 *
		 * `T` denotes the return type of functions returned depending on the
		 * condition.
		 *
		 * An If statement takes 3 parameters:
		 * - A `condition`, of type \Function{bool} (function returning a
		 *   boolean)
		 * - A `then` function, of type \Function{T}, returned when the
		 *   `condition` is `true`
		 * - An `else` function, of type \Function{T}, returned when the
		 *   `condition` is `false`
		 *
		 * @tparam T type of \Functions returned in the `then` / `else` cases
		 *
		 * @param bool condition
		 * @param T then function
		 * @param T else function
		 *
		 * @retval T value returned by the `then` or `else` function, depending
		 * on the `condition`
		 */
		template<typename T>
			class If : public Function<If<T>, T, bool, T, T> {
				public:
					using Function<If<T>, T, bool, T, T>::Function;

					T operator()(point c, time t) const override {
						if(this->template call<0>(c, t))
							return this->template call<1>(c, t);
						else
							return this->template call<2>(c, t);
					}
			};

		/**
		 * Equal operator implementation.
		 *
		 * @tparam P1 left operand type
		 * @tparam P2 right operand type
		 *
		 * @param P1 left operand
		 * @param P2 right operand
		 * @retval bool result of the == operator
		 */
		template<typename P1, typename P2>
			class Equal : public Function<Equal<P1, P2>, bool, P1, P2> {
				public:
					using Function<Equal<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) == this->template call<1>(p, t);
					};
			};
	}

	/**
	 * == operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` and `Arg2` are pixled functions.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::Equal instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::Equal<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator==(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	/**
	 * == operator definition, where `Arg1` is a \Function and `Arg2` is
	 * a constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` is a pixled function and `Arg2` is not
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::Equal instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			!is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::Equal<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type
			> operator==(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(c2)};
			}

	/**
	 * == operator definition, where `Arg1` is a constant and `Arg2` is a
	 * \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg2` is a pixled function and `Arg1` is not
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::Equal instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			!is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::Equal<
			// P1
			typename std::remove_reference<Arg1>::type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator==(Arg1&& c1, Arg2&& f2) {
				return {std::forward<Arg1>(c1), std::forward<Arg2>(f2)};
			}

	namespace conditional {
		/**
		 * Not equal operator implementation.
		 *
		 * @tparam P1 left operand type
		 * @tparam P2 right operand type
		 *
		 * @param P1 left operand
		 * @param P2 right operand
		 * @retval bool result of the != operator
		 */
		template<typename P1, typename P2>
			class NotEqual : public Function<NotEqual<P1, P2>, bool, P1, P2> {
				public:
					using Function<NotEqual<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) != this->template call<1>(p, t);
					};
			};
	}

	/**
	 * != operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` and `Arg2` are pixled functions.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::NotEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::NotEqual<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator!=(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	/**
	 * != operator definition, where `Arg1` is a \Function and `Arg2` is
	 * a constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` is a pixled function and `Arg2` is not
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::Equal instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			!is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::NotEqual<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type
			> operator!=(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(c2)};
			}

	/**
	 * != operator definition, where `Arg1` is a constant and `Arg2` is a
	 * \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg2` is a pixled function and `Arg1` is not
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::Equal instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			!is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::NotEqual<
			// P1
			typename std::remove_reference<Arg1>::type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator!=(Arg1&& c1, Arg2&& f2) {
				return {std::forward<Arg1>(c1), std::forward<Arg2>(f2)};
			}

	namespace conditional {
		/**
		 * Less than operator implementation.
		 *
		 * @tparam P1 left operand type
		 * @tparam P2 right operand type
		 *
		 * @param P1 left operand
		 * @param P2 right operand
		 * @retval bool result of the < operator
		 */
		template<typename P1, typename P2>
			class LessThan : public Function<LessThan<P1, P2>, bool, P1, P2> {
				public:
					using Function<LessThan<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) < this->template call<1>(p, t);
					};
			};
	}

	/**
	 * < operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` and `Arg2` are pixled functions.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::LessThan instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::LessThan<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator<(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	/**
	 * < operator definition, where `Arg1` is a \Function and `Arg2` is
	 * a constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` is a pixled function and `Arg2` is not
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::LessThan instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			!is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::LessThan<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type
			> operator<(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(c2)};
			}

	/**
	 * < operator definition, where `Arg1` is a constant and `Arg2` is a
	 * \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg2` is a pixled function and `Arg1` is not
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::LessThan instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			!is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::LessThan<
			// P1
			typename std::remove_reference<Arg1>::type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator<(Arg1&& c1, Arg2&& f2) {
				return {std::forward<Arg1>(c1), std::forward<Arg2>(f2)};
			}

	namespace conditional {
		/**
		 * Less than or equal operator implementation.
		 *
		 * @tparam P1 left operand type
		 * @tparam P2 right operand type
		 *
		 * @param P1 left operand
		 * @param P2 right operand
		 * @retval bool result of the <= operator
		 */
		template<typename P1, typename P2>
			class LessThanOrEqual : public Function<LessThanOrEqual<P1, P2>, bool, P1, P2> {
				public:
					using Function<LessThanOrEqual<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) <= this->template call<1>(p, t);
					};
			};
	}

	/**
	 * <= operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` and `Arg2` are pixled functions.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::LessThanOrEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::LessThanOrEqual<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator<=(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	/**
	 * <= operator definition, where `Arg1` is a \Function and `Arg2` is
	 * a constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` is a pixled function and `Arg2` is not
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::LessThanOrEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			!is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::LessThanOrEqual<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type
			> operator<=(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(c2)};
			}

	/**
	 * <= operator definition, where `Arg1` is a constant and `Arg2` is a
	 * \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg2` is a pixled function and `Arg1` is not
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::LessThanOrEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			!is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::LessThanOrEqual<
			// P1
			typename std::remove_reference<Arg1>::type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator<=(Arg1&& c1, Arg2&& f2) {
				return {std::forward<Arg1>(c1), std::forward<Arg2>(f2)};
			}

	namespace conditional {
		/**
		 * Greater than operator implementation.
		 *
		 * @tparam P1 left operand type
		 * @tparam P2 right operand type
		 *
		 * @param P1 left operand
		 * @param P2 right operand
		 * @retval bool result of the > operator
		 */
		template<typename P1, typename P2>
			class GreaterThan : public Function<GreaterThan<P1, P2>, bool, P1, P2> {
				public:
					using Function<GreaterThan<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) > this->template call<1>(p, t);
					};
			};
	}

	/**
	 * > operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` and `Arg2` are pixled functions.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::GreaterThan instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::GreaterThan<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator>(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	/**
	 * > operator definition, where `Arg1` is a \Function and `Arg2` is
	 * a constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` is a pixled function and `Arg2` is not
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::GreaterThan instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			!is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::GreaterThan<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type
			> operator>(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(c2)};
			}

	/**
	 * > operator definition, where `Arg1` is a constant and `Arg2` is a
	 * \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg2` is a pixled function and `Arg1` is not
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::GreaterThan instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			!is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::GreaterThan<
			// P1
			typename std::remove_reference<Arg1>::type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator>(Arg1&& c1, Arg2&& f2) {
				return {std::forward<Arg1>(c1), std::forward<Arg2>(f2)};
			}

	namespace conditional {
		/**
		 * Greater than or equal operator implementation.
		 *
		 * @tparam P1 left operand type
		 * @tparam P2 right operand type
		 *
		 * @param P1 left operand
		 * @param P2 right operand
		 * @retval bool result of the >= operator
		 */
		template<typename P1, typename P2>
			class GreaterThanOrEqual : public Function<GreaterThanOrEqual<P1, P2>, bool, P1, P2> {
				public:
					using Function<GreaterThanOrEqual<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) >= this->template call<1>(p, t);
					};
			};
	}

	/**
	 * >= operator definition, where `Arg1` and `Arg2` are \Functions.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` and `Arg2` are pixled functions.
	 *
	 * @param f1 left operand: lvalue or rvalue to a \Function
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::GreaterThanOrEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::GreaterThanOrEqual<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator>=(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

	/**
	 * >= operator definition, where `Arg1` is a \Function and `Arg2` is
	 * a constant.
	 *
	 * @tparam Arg1 automatically deduced left operand type (\Function)
	 * @tparam Arg2 automatically deduced right operand fundamental type
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg1` is a pixled function and `Arg2` is not
	 *
	 * @param f1 left operand: arithmetic constant
	 * @param c2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::GreaterThanOrEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			is_pixled_function<Arg1>::value &&
			!is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::GreaterThanOrEqual<
			// P1
			typename std::remove_reference<Arg1>::type::Type,
		// P2
		typename std::remove_reference<Arg2>::type
			> operator>=(Arg1&& f1, Arg2&& c2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(c2)};
			}

	/**
	 * >= operator definition, where `Arg1` is a constant and `Arg2` is a
	 * \Function.
	 *
	 * @tparam Arg1 automatically deduced left operand fundamental type
	 * @tparam Arg2 automatically deduced right operand type (\Function)
	 * @tparam Enable \SFINAE condition: this overload is considered only if
	 * `Arg2` is a pixled function and `Arg1` is not
	 *
	 * @param c1 left operand: integer constant
	 * @param f2 right operand: lvalue or rvalue to a \Function
	 *
	 * @return a conditional::GreaterThanOrEqual instance
	 */
	template<typename Arg1, typename Arg2,
		typename std::enable_if< 
			!is_pixled_function<Arg1>::value &&
			is_pixled_function<Arg2>::value
			, bool>::type = true>
			conditional::GreaterThanOrEqual<
			// P1
			typename std::remove_reference<Arg1>::type,
		// P2
		typename std::remove_reference<Arg2>::type::Type
			> operator>=(Arg1&& c1, Arg2&& f2) {
				return {std::forward<Arg1>(c1), std::forward<Arg2>(f2)};
			}

}
#endif
