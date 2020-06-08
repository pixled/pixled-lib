#ifndef OUTPUT_H
#define OUTPUT_H

#include "api/output.h"

template<int r, int g, int b>
class RgbFormat : public api::OutputFormat {
	public:
		void write(const api::Color& color, uint8_t* const& output) {
			output[r] = color.red();
			output[g] = color.green();
			output[b] = color.blue();
		}
};

using RGB = RgbFormat<0, 1, 2>;
using RBG = RgbFormat<0, 2, 1>;
using GRB = RgbFormat<1, 0, 2>;
using GBR = RgbFormat<2, 0, 1>;
using BRG = RgbFormat<1, 2, 0>;
using BGR = RgbFormat<2, 1, 0>;

template<int r, int g, int b, int w>
class RgbwFormat : public api::OutputFormat {
	public:
		void write(const api::Color& color, uint8_t* const& output) {
			output[r] = color.red();
			output[g] = color.green();
			output[b] = color.blue();
			output[w] = 0;
		}
};

using WRGB = RgbwFormat<1, 2, 3, 0>;
using WRBG = RgbwFormat<1, 3, 2, 0>;
using WGRB = RgbwFormat<2, 1, 3, 0>;
using WGBR = RgbwFormat<3, 1, 2, 0>;
using WBRG = RgbwFormat<2, 3, 1, 0>;
using WBGR = RgbwFormat<3, 2, 1, 0>;

using RWGB = RgbwFormat<0, 2, 3, 1>;
using RWBG = RgbwFormat<0, 3, 2, 1>;
using GWRB = RgbwFormat<2, 0, 3, 1>;
using GWBR = RgbwFormat<3, 0, 2, 1>;
using BWRG = RgbwFormat<2, 3, 0, 1>;
using BWGR = RgbwFormat<3, 2, 0, 1>;

using RGWB = RgbwFormat<0, 1, 3, 2>;
using RBWG = RgbwFormat<0, 3, 1, 2>;
using GRWB = RgbwFormat<1, 0, 3, 2>;
using GBWR = RgbwFormat<3, 0, 1, 2>;
using BRWG = RgbwFormat<1, 3, 0, 2>;
using BGWR = RgbwFormat<3, 1, 0, 2>;

using RGBW = RgbwFormat<0, 1, 2, 3>;
using RBGW = RgbwFormat<0, 2, 1, 3>;
using GRBW = RgbwFormat<1, 0, 2, 3>;
using GBRW = RgbwFormat<2, 0, 1, 3>;
using BRGW = RgbwFormat<1, 2, 0, 3>;
using BGRW = RgbwFormat<2, 1, 0, 3>;

#endif
