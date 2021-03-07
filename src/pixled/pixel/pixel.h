#ifndef PIXLED_PIXEL_PIXEL_H
#define PIXLED_PIXEL_PIXEL_H

#include "../function.h"

namespace pixled { namespace pixel {
	class hsb : public VarFunction<hsb, pixled::Color, float, float, float> {
		public:
			using VarFunction<hsb, pixled::Color, float, float, float>::VarFunction;

			pixled::Color operator()(Point c, Time t) const override;
	};

	class rgb : public VarFunction<rgb, pixled::Color, uint8_t, uint8_t, uint8_t> {
		public:
			using VarFunction<rgb, pixled::Color, uint8_t, uint8_t, uint8_t>::VarFunction;

			pixled::Color operator()(Point c, Time t) const override;
	};
}}
#endif
