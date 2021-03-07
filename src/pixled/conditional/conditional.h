#ifndef PIXLED_FUNCTIONNAL_COMPARISONS_H
#define PIXLED_FUNCTIONNAL_COMPARISONS_H

#include "../function.h"

namespace pixled { namespace conditional {
	template<typename IF_t, typename ELSE_t = IF_t>
		class If : public VarFunction<If<IF_t, ELSE_t>,
			typename std::common_type<IF_t, ELSE_t>::type, bool, IF_t, ELSE_t> {

				typedef typename std::common_type<IF_t, ELSE_t>::type R;

			public:
				using VarFunction<If<IF_t, ELSE_t>, R, bool, IF_t, ELSE_t>::VarFunction;

				R operator()(Point c, Time t) const override {
					if(this->template call<0>(c, t))
						return this->template call<1>(c, t);
					else
						return this->template call<2>(c, t);
				}
		};
}}
#endif
