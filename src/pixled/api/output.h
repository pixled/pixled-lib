#ifndef OUTPUT_API_H
#define OUTPUT_API_H

#include "pixel.h"
#include <cstdint>

namespace pixled {
	namespace api {
		class Output {
			public:
				virtual void write(const api::Color& color, std::size_t i) = 0;

		};
	}
}
#endif
