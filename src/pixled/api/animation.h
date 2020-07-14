#ifndef ANIMATION_API_H
#define ANIMATION_API_H

#include "pixel.h"
#include "coordinates.h"

typedef unsigned long Time;

namespace pixled {
	namespace api {
		class AnimationRuntime {
			public:
				virtual Time time() const = 0;
				virtual void next() = 0;
				virtual void prev() = 0;
				virtual void frame(Time t) = 0;
		};

		struct Size {
			unsigned int width;
			unsigned int height;
			Size(unsigned int width, unsigned int height)
				: width(width), height(height) {}
		};

		class View {
			public:
				virtual Point position(int time) const = 0;
				virtual Size size(int time) const = 0;
				virtual void operator()(Color&, int x, int y, unsigned long time) const = 0;
		};

		class StaticView : public View {
			private:
				Point _position;
				Size size;
			public:
				StaticView(int x, int y, unsigned int width, unsigned int height) 
					: _position(x, y), size(width, height) {}
				Point position(int time) const override {return _position;}
		};

		class Animation {
			public:
				virtual void compute(Color& color, int x, int time) = 0;
		};
	}
}
#endif
