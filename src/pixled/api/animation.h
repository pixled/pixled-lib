#ifndef ANIMATION_API_H
#define ANIMATION_API_H

#include "led.h"

typedef unsigned long Time;
namespace api {
	class AnimationRuntime {
		public:
			virtual unsigned long time() = 0;
			virtual void next() = 0;
			virtual void prev() = 0;
	};

	class Position {

	};

/*
 *    class View {
 *        public:
 *            virtual int position(int time) = 0;
 *
 *    };
 *
 *    template<int x>
 *    class StaticView : public View {
 *        public:
 *            int position(int time) {return x;}
 *    };
 */

	class Animation {
		public:
			virtual void compute(Color& color, int x, int time) = 0;
	};
}
#endif
