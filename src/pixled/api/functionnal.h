#ifndef FUNCTIONNAL_API_H
#define FUNCTIONNAL_API_H

namespace api {
	template<typename T>
	class Function {
		public:
			virtual T operator()() const = 0;
			virtual ~Function() {}
			virtual Function<T>* move() = 0;
	};

	template<typename T, template<typename> class FctImplem>
		class BinaryFunction : public Function<T> {
			protected:
			const api::Function<T>* f1;
			bool f1_owned = false;
			const api::Function<T>* f2;
			bool f2_owned = false;

			public:
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
				f1(other.f1->copy()), f2(other.f2->copy()) {}

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
}
#endif
