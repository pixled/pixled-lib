#ifndef FUNCTIONNAL_H
#define FUNCTIONNAL_H
#include "api/functionnal.h"
#include "led.h"
#include <cmath>

namespace pixled {
	class hsb : public api::Function<base::Color> {
		private:
			api::Function<float>& h;
			api::Function<float>& s;
			api::Function<float>& b;
		public:
			hsb(api::Function<float>& h, api::Function<float>& s, api::Function<float>& b)
				: h(h), s(s), b(b) {}

			base::Color operator()() const {
				base::Color color;
				color.setHsv(h(), s(), b());
				return color;
			}
	};

	class rgb : public api::Function<base::Color> {
		private:
			api::Function<uint8_t>& r;
			api::Function<uint8_t>& g;
			api::Function<uint8_t>& b;

		public:
			rgb(api::Function<uint8_t>& r, api::Function<uint8_t>& g, api::Function<uint8_t>& b)
				: r(r), g(g), b(b) {}

			base::Color operator()() const {
				base::Color color;
				color.setRgb(r(), g(), b());
				return color;
			}
	};

	template<typename T>
	class Constant : public api::Function<T> {
		private:
			T value;
		public:
			using Type = typename api::Function<T>::Type;
			Constant(T& value) :
				value(value) {}
			T operator()() const {return value;};
	};

	template<typename T>
		class Plus : public api::BinaryFunction<T, Plus> {

			public:
				IMPLEM_BINARY(Plus)

				T operator()() const override {
					return (*this->f1)() + (*this->f2)();
				}
		};

	template<typename Arg1, typename Arg2>
	Plus<typename std::remove_reference<Arg1>::type::Type> operator+(Arg1&& f1, Arg2&& f2) {
		static_assert(
				std::is_same<typename std::remove_reference<Arg1>::type::Type,
				typename std::remove_reference<Arg2>::type::Type>::value,
				"The two argument functions must return the same type of values.");
		return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
	}

	template<typename T>
		class Multiplies : public api::BinaryFunction<T, Multiplies> {
			public:
				IMPLEM_BINARY(Multiplies)
   /*             using Type = typename api::Function<T>::Type;*/
				//template<typename Arg1, typename Arg2>
					//Multiplies(Arg1&& arg1, Arg2&& arg2)
						//: api::BinaryFunction<T, Multiplies>(
								//std::forward<Arg1>(arg1),
								//std::forward<Arg2>(arg2))
					//{}
				//Multiplies(const Multiplies& other)
					//: api::BinaryFunction<T, Multiplies>(other) {}

				//Multiplies(Multiplies&& other)
					//: api::BinaryFunction<T, Multiplies>(std::move(other)) {}

				//Multiplies& operator=(const Multiplies& other) {
					//api::BinaryFunction<T, Multiplies>::operator=(other);
					//return *this;
				//}

				//Multiplies& operator=(Multiplies&& other) {
					//api::BinaryFunction<T, Multiplies>::operator=(std::move(other));
					//return *this;
				/*}*/

				T operator()() const override {
					return (*this->f1)() * (*this->f2)();
				}
		};

	template<typename Arg1, typename Arg2>
	Multiplies<typename Arg1::Type> operator*(Arg1&& f1, Arg2&& f2) {
		static_assert(
				std::is_same<typename Arg1::Type, typename Arg1::Type>::value,
				"The two argument functions must return the same type of values.");
		return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
	}

	template<typename T>
		class Divides : public api::BinaryFunction<T, Divides> {
			public:
				IMPLEM_BINARY(Divides)
   /*             using Type = typename api::Function<T>::Type;*/
				//template<typename Arg1, typename Arg2>
					//Divides(Arg1&& arg1, Arg2&& arg2)
						//: api::BinaryFunction<T, Divides>(
								//std::forward<Arg1>(arg1),
								//std::forward<Arg2>(arg2))
					//{}
				//Divides(const Divides& other)
					//: api::BinaryFunction<T, Divides>(other) {}

				//Divides(Divides&& other)
					//: api::BinaryFunction<T, Divides>(std::move(other)) {}

				//Divides& operator=(const Divides& other) {
					//api::BinaryFunction<T, Divides>::operator=(other);
					//return *this;
				//}

				//Divides& operator=(Divides&& other) {
					//api::BinaryFunction<T, Divides>::operator=(std::move(other));
					//return *this;
				/*}*/

				T operator()() const override {
					return (*this->f1)() / (*this->f2)();
				}
		};

	template<typename Arg1, typename Arg2>
	Divides<typename Arg1::Type> operator/(Arg1&& f1, Arg2&& f2) {
		static_assert(
				std::is_same<typename Arg1::Type, typename Arg1::Type>::value,
				"The two argument functions must return the same type of values.");
		return {std::forward<Arg1>(f1), std::forward<Arg2>(f2)};
	}

	template<typename T>
		class sin : public api::Function<T> {
			private:
				api::Function<float>& f;
			public:
				sin(api::Function<float>& f) :
					f(f) {}
				T operator()() {
					return std::sin(f());
				}
		};
}

#endif
