#ifndef PIXLED_FUNCTIONNAL_COMPARISONS_H
#define PIXLED_FUNCTIONNAL_COMPARISONS_H

#include "../function.h"
#include <type_traits>

namespace pixled { 
	namespace conditional {
		template<typename IF_t, typename ELSE_t = IF_t>
			class If : public Function<If<IF_t, ELSE_t>,
			typename std::common_type<IF_t, ELSE_t>::type, bool, IF_t, ELSE_t> {

				typedef typename std::common_type<IF_t, ELSE_t>::type R;

				public:
				using Function<If<IF_t, ELSE_t>, R, bool, IF_t, ELSE_t>::Function;

				R operator()(point c, time t) const override {
					if(this->template call<0>(c, t))
						return this->template call<1>(c, t);
					else
						return this->template call<2>(c, t);
				}
			};

		template<typename P1, typename P2>
			class Equal : public Function<Equal<P1, P2>, bool, P1, P2> {
				public:
					using Function<Equal<P1, P2>, bool, P1, P2>::Function;

					bool operator()(point p, time t) const override {
						return this->template call<0>(p, t) == this->template call<1>(p, t);
					};
			};
	}

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
			> operator==(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

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
			> operator==(Arg1&& f1, Arg2&& f2) {
				return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
			}

}
#endif
