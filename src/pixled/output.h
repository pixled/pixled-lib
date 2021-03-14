#ifndef OUTPUT_API_H
#define OUTPUT_API_H

#include "color.h"
#include <cstdint>

namespace pixled {
	class Output {
		public:
			virtual void write(const color& color, std::size_t i) = 0;

	};
}
#endif
