#ifndef FUNCTIONNAL_API_H
#define FUNCTIONNAL_API_H

#include <utility>
#include "animation.h"
#include "geometry.h"

namespace pixled {
	namespace api {
		template<typename T>
			class Function {
				public:
					typedef T Type;

					virtual T operator()(Point c, Time t) const = 0;
					virtual ~Function() {}
					virtual Function<T>* copy() const = 0;
			};

		template<typename T>
			class Constant : public api::Function<T> {
				private:
					T value;
				public:
					using Type = typename api::Function<T>::Type;
					Constant(T value) :
						value(value) {}
					T operator()(Point, Time) const override {return value;};

					Function<T>* copy() const override {
						return new Constant<T>(value);
					}
			};

		template<typename T>
			class FctWrapper {
				private:
					const Function<T>* fct;

				public:
					FctWrapper(const Function<T>& fct)
						: fct(fct.copy()) {
						}
					FctWrapper(T constant)
						: fct(new Constant<T>(constant)) {
						}

					FctWrapper(const FctWrapper<T>& other) {
						fct = other.fct->copy();
					}
					FctWrapper(FctWrapper<T>&& other) {
						fct = other.fct;
						other.fct = nullptr;
					}
					FctWrapper& operator=(const FctWrapper<T>& other) {
						if(fct!=nullptr)
							delete fct;
						fct = other.fct->copy();
						return *this;
					}
					FctWrapper& operator=(FctWrapper<T>&& other) {
						if(fct!=nullptr)
							delete fct;
						fct = other.fct;
						other.fct = nullptr;
						return *this;
					}

					~FctWrapper() {
						if(fct!=nullptr)
							delete fct;
					}

					const api::Function<T>& operator*() const {
						return *fct;
					}
			};

		template<typename R, typename P, typename FctImplem>
			class UnaryFunction : public Function<R> {
				protected:
					const FctWrapper<P> f;

				public:
					using Type = typename Function<R>::Type;

					template<typename Arg>
						UnaryFunction(Arg&& arg)
						: f(std::forward<Arg>(arg)) {}

				protected:
					Function<R>* copy() const override {
						return new FctImplem(*f);
					}
			};

		template<typename R, typename P1, typename P2, typename FctImplem>
			class BinaryFunction : public Function<R> {
				protected:
					const FctWrapper<P1> f1;
					const FctWrapper<P2> f2;

				public:
					using Type = typename Function<R>::Type;

					template<typename Arg1, typename Arg2>
						BinaryFunction(Arg1&& arg1, Arg2&& arg2) :
							f1(std::forward<Arg1>(arg1)), f2(std::forward<Arg2>(arg2)) {
							}

				protected:
					Function<R>* copy() const override {
						return new FctImplem(*f1, *f2);
					}
			};

		template<typename R, typename P1, typename P2, typename P3, class FctImplem>
			class TernaryFunction : public Function<R> {
				protected:
					const FctWrapper<P1> f1;
					const FctWrapper<P2> f2;
					const FctWrapper<P3> f3;

				public:
					using Type = typename Function<R>::Type;

					template<typename Arg1, typename Arg2, typename Arg3>
						TernaryFunction(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3) :
							f1(std::forward<Arg1>(arg1)), f2(std::forward<Arg2>(arg2)), f3(std::forward<Arg3>(arg3)) {
							}

				protected:
					Function<R>* copy() const override {
						return new FctImplem(*f1, *f2, *f3);
					}
			};

		template<typename To, typename From>
			class Cast : public Function<To> {
				private:
					const FctWrapper<From> f;

				public:
					Cast(const Function<From>& from)
						: f(from) {}
					Cast(Function<From>&& from)
						: f(std::move(from)) {}

					To operator()(Point c, Time t) const override {
						return (*this->f)(c, t);
					}

					Cast<To, From>* copy() const override {
						return new Cast(*f);
					}
			};
	}
}
#endif
