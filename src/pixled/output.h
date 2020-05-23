#ifndef OUTPUT_H
#define OUTPUT_H

#include "api/output.h"

namespace base {
	class rgb : public api::rgb {
		private:
			int values[3];

		public:
			rgb() : rgb(0, 0, 0) {}
			rgb(int r, int g, int b) {
				values[RGB::R] = r;
				values[RGB::G] = g;
				values[RGB::B] = b;
			}

			int operator[](RGB rgb) override {
				return values[rgb];
			}
	};

	template<int _length, typename rgb>
	class RgbArray : public api::RgbArray<_length, rgb> {
		private:
			rgb values[_length];

		public:
			rgb& operator[](int i) override {
				return values[i];
			}

			const rgb& operator[](int i) const override {
				return values[i];
			}
	};
}
#endif
