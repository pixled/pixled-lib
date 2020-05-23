#ifndef OUTPUT_API_H
#define OUTPUT_API_H
#include <type_traits>

enum RGB : int {
	R = 0,
	G = 1,
	B = 2
};

namespace api {
	class rgb {
		public:
			virtual int operator[](RGB) = 0;
	};
	template<int _length, typename rgb_t>
	class RgbArray {
		static_assert(std::is_base_of<rgb, rgb_t>::value, "The specified rgb_t does not implement api::rgb.");
		public:
			static constexpr int length() {return _length;}
			virtual rgb& operator[](int i) = 0;
			virtual const rgb& operator[](int i) const = 0;

	};
}
#endif
