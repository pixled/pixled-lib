#ifndef FUNCTIONNAL_API_H
#define FUNCTIONNAL_API_H

#define IMPLEM_BINARY(ClassName) \
	using Type = typename api::Function<T>::Type;\
	template<typename Arg1, typename Arg2>\
		ClassName(Arg1&& arg1, Arg2&& arg2)\
			: api::BinaryFunction<T, ClassName>(\
					std::forward<Arg1>(arg1),\
					std::forward<Arg2>(arg2))\
		{}\
	template<typename Arg>\
		ClassName(Arg&& arg1, T c)\
			: api::BinaryFunction<T, ClassName>(\
					std::forward<Arg>(arg1),\
					api::Constant<T>(c)\
					)\
		{}\
\
	template<typename Arg>\
		ClassName(T c, Arg&& arg2)\
			: api::BinaryFunction<T, ClassName>(\
					api::Constant<T>(c),\
					std::forward<Arg>(arg2)\
					)\
		{}\
\
	template<typename Arg>\
		ClassName(T c1, T c2)\
			: api::BinaryFunction<T, ClassName>(\
					api::Constant<T>(c1),\
					api::Constant<T>(c2)\
					)\
		{}\
\
\
\
	ClassName(const ClassName& other)\
		: api::BinaryFunction<T, ClassName>(other) {}\
\
	ClassName(ClassName&& other)\
		: api::BinaryFunction<T, ClassName>(std::move(other)) {}\
\
	ClassName& operator=(const ClassName& other) {\
		api::BinaryFunction<T, ClassName>::operator=(other);\
		return *this;\
	}\
\
	ClassName& operator=(ClassName&& other) {\
		api::BinaryFunction<T, ClassName>::operator=(std::move(other));\
		return *this;\
	}\

#define IMPLEM_UNARY(ClassName) \
	using Type = typename api::Function<T>::Type;\
	template<typename Arg>\
		ClassName(Arg&& arg)\
			: api::UnaryFunction<T, ClassName>(\
					std::forward<Arg>(arg))\
		{}\
\
		ClassName(T c)\
			: api::UnaryFunction<T, ClassName>(\
					api::Constant<T>(c))\
		{}\
\
\
	ClassName(const ClassName& other)\
		: api::UnaryFunction<T, ClassName>(other) {}\
\
	ClassName(ClassName&& other)\
		: api::UnaryFunction<T, ClassName>(std::move(other)) {}\
\
	ClassName& operator=(const ClassName& other) {\
		api::UnaryFunction<T, ClassName>::operator=(other);\
		return *this;\
	}\
\
	ClassName& operator=(ClassName&& other) {\
		api::UnaryFunction<T, ClassName>::operator=(std::move(other));\
		return *this;\
	}\

namespace api {
	template<typename T>
	class Function {
		public:
			typedef T Type;

			virtual T operator()() const = 0;
			virtual ~Function() {}
			virtual Function<T>* move() = 0;
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

			Function<T>* move() override {
				return new Constant<T>(value);
			}
	};

	template<typename T, template<typename> class FctImplem>
		class BinaryFunction : public Function<T> {
			protected:
			const api::Function<T>* f1;
			bool f1_owned = false;
			const api::Function<T>* f2;
			bool f2_owned = false;

			public:
			using Type = typename Function<T>::Type;

			BinaryFunction(const api::Function<T>& f1, const api::Function<T>& f2)
				: f1(&f1), f2(&f2) {}
			BinaryFunction(api::Function<T>&& f1, api::Function<T>&& f2)
				: f1(f1.move()), f2(f2.move()) {
					f1_owned = true;
					f2_owned = true;
				}

			BinaryFunction(const api::Function<T>& f1, api::Function<T>&& f2)
				: f1(&f1), f2(f2.move()) {
					f2_owned = true;
				}

			BinaryFunction(api::Function<T>&& f1, const api::Function<T>& f2)
				: f1(f1.move()), f2(&f2) {
					f1_owned = true;
				}

			// Simple copy, no ownership transfer.
			BinaryFunction(const BinaryFunction& other) :
				f1(*other.f1), f2(*other.f2) {}

			// Ownership is transfered to this
			BinaryFunction(BinaryFunction&& other) :
				f1(other.f1), f2(other.f2),
				f1_owned(other.f1_owned), f2_owned(other.f2_owned) {

				other.f1_owned = false;
				other.f2_owned = false;
			}

			BinaryFunction& operator=(const BinaryFunction& other) {
				if(f1_owned)
					delete f1;
				if(f2_owned)
					delete f2;

				f1_owned = false;
				f2_owned = false;
				f1 = other.f1;
				f2 = other.f2;
			}
			BinaryFunction& operator=(BinaryFunction&& other) {
				if(f1_owned)
					delete f1;
				if(f2_owned)
					delete f2;

				f1 = other.f1;
				f2 = other.f2;
				f1_owned = other.f1_owned;
				f2_owned = other.f1_owned;

				other.f1_owned = false;
				other.f2_owned = false;
			}

			protected:
			Function<T>* move() override {
				FctImplem<T>* moved = new FctImplem<T>(*f1, *f2);
				moved->f1_owned = f1_owned;
				moved->f2_owned = f2_owned;
				f1_owned = false;
				f2_owned = false;
				return moved;
			}

			virtual ~BinaryFunction() {
				if(f1_owned)
					delete f1;
				if(f2_owned)
					delete f2;
			}
		};

	template<typename T, template<typename> class FctImplem>
	class UnaryFunction : Function<T> {
		protected:
			const api::Function<T>* f;
			bool f_owned = false;
		public:
			using Type = typename Function<T>::Type;

			UnaryFunction(const api::Function<T>& f)
				: f(&f) {}
			UnaryFunction(api::Function<T>&& f)
				: f(f.move()) {
					f_owned = true;
				}

			// Simple copy, no ownership transfer.
			UnaryFunction(const UnaryFunction& other) :
				f(*other.f) {}

			// Ownership is transfered to this
			UnaryFunction(UnaryFunction&& other) :
				f(f), f_owned(other.f_owned) {
				other.f_owned = false;
			}

			UnaryFunction& operator=(const UnaryFunction& other) {
				if(f_owned)
					delete f;

				f_owned = false;
				f = other.f;
			}
			UnaryFunction& operator=(UnaryFunction&& other) {
				if(f_owned)
					delete f;

				f = other.f;
				f_owned = other.f_owned;

				other.f_owned = false;
			}

			protected:
			Function<T>* move() override {
				FctImplem<T>* moved = new FctImplem<T>(*f);
				moved->f_owned = f_owned;
				f_owned = false;
				return moved;
			}

			virtual ~UnaryFunction() {
				if(f_owned)
					delete f;
			}

	};
}
#endif
