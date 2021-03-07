#ifndef PIXLED_MAPPING_API_H
#define PIXLED_MAPPING_API_H

#include "geometry.h"
#include <vector>
#include <utility>

namespace pixled {
	class Mapping {
		public:
			typedef std::vector<std::pair<Point, std::size_t>>::const_iterator map_iterator;
			virtual map_iterator begin() const = 0;
			virtual map_iterator end() const = 0;
	};
}
#endif
