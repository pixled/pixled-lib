#ifndef ANIMATION_API_H
#define ANIMATION_API_H

#include "led.h"

typedef unsigned long Time;
typedef long Coordinate;

namespace pixled {
	namespace api {
		class AnimationRuntime {
			public:
				virtual unsigned long time() = 0;
				virtual void next() = 0;
				virtual void prev() = 0;
		};

		struct Coordinates {
			Coordinate x;
			Coordinate y;
			Coordinates(Coordinate x, Coordinate y)
				: x(x), y(y) {}
		};

		struct Size {
			unsigned int width;
			unsigned int height;
			Size(unsigned int width, unsigned int height)
				: width(width), height(height) {}
		};

		class View {
			public:
				virtual Coordinates position(int time) const = 0;
				virtual Size size(int time) const = 0;
				virtual void operator()(Color&, int x, int y, unsigned long time) const = 0;
		};

		class StaticView : public View {
			private:
				Coordinates _position;
				Size size;
			public:
				StaticView(int x, int y, unsigned int width, unsigned int height) 
					: _position(x, y), size(width, height) {}
				Coordinates position(int time) {return _position;}
		};

		class Animation {
			public:
				virtual void compute(Color& color, int x, int time) = 0;
		};
	}
}
#endif
