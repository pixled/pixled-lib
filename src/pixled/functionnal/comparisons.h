#ifndef PIXLED_FUNCTIONNAL_COMPARISONS_H
#define PIXLED_FUNCTIONNAL_COMPARISONS_H

#include "../api/functionnal.h"

namespace pixled {
	template<typename IF_t, typename ELSE_t = IF_t>
		class If : public api::TernaryFunction<
			typename std::common_type<IF_t, ELSE_t>::type, bool, IF_t, ELSE_t, If<IF_t, ELSE_t>> {

				typedef typename std::common_type<IF_t, ELSE_t>::type R;

			public:
				using api::TernaryFunction<R, bool, IF_t, ELSE_t, If<IF_t, ELSE_t>>::TernaryFunction;

				R operator()(api::Point c, Time t) const override {
					if((*this->f1)(c, t))
						return (*this->f2)(c, t);
					else
						return (*this->f3)(c, t);
				}
		};
}
#endif
