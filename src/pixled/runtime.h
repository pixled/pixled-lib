#ifndef PIXLED_RUNTIME_H
#define PIXLED_RUNTIME_H

#include "output.h"
#include "function.h"
#include "mapping/mapping.h"

namespace pixled {
	class Runtime {
		private:
			unsigned long _time = 0;
			Mapping& map;
			Output& output;
			base::Function<Color>& animation;

		public:
			Runtime(Mapping& map, Output& output, base::Function<Color>& animation)
				: map(map), output(output), animation(animation) {}

			void frame(Time t);

			void prev();
			void next();
			Time time() const;
	};
}
#endif
