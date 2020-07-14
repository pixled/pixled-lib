#ifndef PIXLED_UTILS
#define PIXLED_UTILS

#include "animation.h"

#define PIXLED_PI 3.14159265358979323846f

namespace pixled {
	namespace api {
		inline bool operator==(const Point& c1, const Point& c2) {
			return (c1.x == c2.x) && (c1.y == c2.y);
		}
	}
}
#endif
