#ifndef PIXLED_COORDINATES_H
#define PIXLED_COORDINATES_H

typedef long Coordinate;

namespace pixled {
	namespace api {
		struct Coordinates {
			Coordinate x;
			Coordinate y;
			Coordinates(Coordinate x, Coordinate y)
				: x(x), y(y) {}
		};
	}
}

#endif
