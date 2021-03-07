#ifndef FUNCTIONNAL_API_H
#define FUNCTIONNAL_API_H

#include <utility>
#include "pixel.h"
#include "time.h"
#include "geometry.h"

namespace pixled {
	namespace base {
		/**
		 * Generic Function interface, that can be used as arguments for
		 * other Functions.
		 *
		 * Notice that Function parameters are voluntarily not fixed in
		 * this base class. This allows Functions to be used as other
		 * Functions parameters, since when a Function is passed as a
		 * parameter, the only thing that matters is its return type, that
		 * can actually be considered as the type of the parameter.
		 *
		 * @tparam R return type
		 *
		 * @see pixled::VarFunction
		 */
		template<typename R>
			class Function {
				public:
					/**
					 * Function return type.
					 */
					typedef R Type;

					/**
					 * Computes the value of this Function on point `p` at
					 * time `t`.
					 *
					 * @param p point
					 * @param t time
					 * @return Result of this Function, evaluated on point
					 * `p` at time `t`. Notice that evaluating a function
					 * usually requires the recursive evaluation of other
					 * Functions (that are actually _parameters_ of this
					 * function) until a Constant is reached for example.
					 */
					virtual R operator()(Point p, Time t) const = 0;

					/**
					 * Returns a dynamically allocated copy of this
					 * function.
					 *
					 * @return copy of this function
					 */
					virtual Function<R>* copy() const = 0;

					virtual ~Function() {}
			};
	}

	/**
	 * A base::Function that returns a constant value on any Point at any
	 * Time.
	 *
	 * @tparam T type of the Constant
	 */
	template<typename T>
		class Constant : public base::Function<T> {
			private:
				T _value;

			public:
				/**
				 * Constant constructor.
				 *
				 * Initializes the constant with the specified `value`.
				 */
				Constant(const T& value) :
					_value(value) {}

				/**
				 * Returns the `value` specified in the constructor, on any
				 * Point at any Time.
				 *
				 * @return constant value
				 */
				T operator()(Point, Time) const override {return _value;};

				/**
				 * Returns a dynamically copy of this Constant, with the
				 * same value.
				 *
				 * @return copy of this Constant
				 */
				Constant<T>* copy() const override {
					return new Constant<T>(_value);
				}
		};

	/**
	 * A smart pointer used to manage dynamically allocated virtual
	 * base::Function instances.
	 *
	 * @tparam R function return type
	 */
	template<typename R>
		class FctWrapper {
			private:
				const base::Function<R>* fct;

			public:
				/**
				 * Function return type.
				 */
				typedef R Type;

				/**
				 * Initializes this wrapper with a **copy** of the input
				 * function.
				 *
				 * Doing so, this FctWrapper automatically takes the
				 * ownership of a dynamically allocated copy of `fct`, that
				 * does not need to be dynamically allocated and that can
				 * be safely destroyed once this FctWrapper has been
				 * initialized.
				 *
				 * @param fct function to wrap
				 */
				FctWrapper(const base::Function<R>& fct)
					: fct(fct.copy()) {
					}

				/**
				 * Initializes this FctWrapper with a Constant `value`.
				 *
				 * @param value value of the Constant
				 */
				FctWrapper(R value)
					: fct(new Constant<R>(value)) {
					}

				/**
				 * FctWrapper copy constructor.
				 *
				 * This FctWrapper is initialized with a copy of the
				 * wrapped function of `other`, that is left unchanged.
				 *
				 * @param other FctWrapper to copy from
				 */
				FctWrapper(const FctWrapper<R>& other)
					: fct(other.fct->copy()) {
					}

				/**
				 * FctWrapper move constructor.
				 *
				 * This FctWrapper is initialized with the wrapped function
				 * of `other`, that is left dangling.
				 *
				 * @param other FctWrapper to move from
				 */
				FctWrapper(FctWrapper<R>&& other) {
					fct = other.fct;
					other.fct = nullptr;
				}

				/**
				 * FctWrapper copy assignment.
				 *
				 * If this FctWrapper is not dangling, the internal
				 * function is destroyed.
				 *
				 * Then, the internal function is replaced with a copy of
				 * the wrapped function of other, that is left unchanged.
				 *
				 * @param other FctWrapper to copy from
				 */
				FctWrapper& operator=(const FctWrapper<R>& other) {
					if(fct!=nullptr)
						delete fct;
					fct = other.fct->copy();
					return *this;
				}

				/**
				 * FctWrapper move assignment.
				 *
				 * If this FctWrapper is not dangling, the internal
				 * function is destroyed.
				 *
				 * Then, the internal function is replaced with the the
				 * wrapped function of other, that is left dangling.
				 *
				 * @param other FctWrapper to move from
				 */
				FctWrapper& operator=(FctWrapper<R>&& other) {
					if(fct!=nullptr)
						delete fct;
					fct = other.fct;
					other.fct = nullptr;
					return *this;
				}


				/**
				 * Indirection operator.
				 *
				 * Returns a reference to the wrapped function.
				 *
				 * @return wrapped function
				 */
				const base::Function<R>& operator*() const {
					return *fct;
				}

				/**
				 * Gets a reference to the wrapped function.
				 */
				const base::Function<R>& get() const {
					return *fct;
				}

				/**
				 * FctWrapper destructor.
				 *
				 * If this FctWrapper is not dangling, the internal
				 * function is destroyed.
				 */
				~FctWrapper() {
					if(fct!=nullptr)
						delete fct;
				}
		};

	template<typename Implem, typename R, typename... Args>
		class VarFunction : public base::Function<R> {
			protected:
				std::tuple<const FctWrapper<Args>...> args;

			public:
				using Type = typename base::Function<R>::Type;

				template<typename... Fct>
					VarFunction(Fct&& ... fcts) : args(std::forward<Fct>(fcts)...) {
					}

				template<std::size_t i>
					typename std::tuple_element<i, decltype(args)>::type::Type call(Point p, Time t) const {
						return (*std::get<i>(args))(p, t);
					}
				template<std::size_t i>
					const base::Function<typename std::tuple_element<i, decltype(args)>::type::Type>& arg() const {
						return *std::get<i>(args);
					}

			protected:
				base::Function<R>* copy() const override {
					return new Implem(static_cast<const Implem&>(*this));
				}
		};

	template<typename To, typename From>
		class Cast : public base::Function<To> {
			private:
				const FctWrapper<From> f;

			public:
				Cast(const base::Function<From>& from)
					: f(from) {}
				Cast(base::Function<From>&& from)
					: f(std::move(from)) {}

				To operator()(Point c, Time t) const override {
					return (*this->f)(c, t);
				}

				Cast<To, From>* copy() const override {
					return new Cast(*f);
				}
		};
}
#endif
