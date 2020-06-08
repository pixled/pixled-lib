#ifndef OUTPUT_API_H
#define OUTPUT_API_H

#include <cstdint>

namespace api {
	class Color;
	class OutputFormat {
		public:
		virtual void write(const api::Color& color, uint8_t* const& output) = 0;
	};
}
#endif
