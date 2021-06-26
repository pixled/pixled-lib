#ifndef FUNCTIONNAL_API_H
#define FUNCTIONNAL_API_H

#include <utility>
#include "color.h"
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
		 * @see pixled::Function
		 */
		template<typename R>
			class Function {
				public:
					/**
					 * Function return type.
					 */
					typedef R Type;

					/**
					 * @anchor function_call_operator
					 *
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
					virtual R operator()(point p, time t) const = 0;

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
	 * A base::Function that returns a constant value on any point at any
	 * time.
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
				 * point at any time.
				 *
				 * @return constant value
				 */
				T operator()(point, time) const override {return _value;};

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

	/**
	 * Generic pixled function, the base of any animation components.
	 *
	 * `R` denotes the return type of this Function.
	 *
	 * `Args` is a list of **primitive** arguments of the function, e.g.
	 * `float`, `int`, `std::string`, or any other type defined in the pixled
	 * namespace, e.g. pixled::point, pixled::line, pixled::time,
	 * pixled::color...
	 *
	 * Particularly interesting Function implementations are
	 * base::Function<color> implementations, i.e. functions that return
	 * colors, since they define pixled _animations_ that can be passed to a
	 * pixled::Runtime. 
	 * 
	 *
	 * The purpose of the Function class is that it can be built using a list
	 * of other base::Functions that **return** instances of primitive types defined
	 * by `Args`.
	 *
	 * For this mechanism to work properly, the currently derived class
	 * (`Implem`) should import Function constructors with a `using` directive.
	 *
	 * @par Example
	 *
	 * ```cpp
	 * class F : public pixled::Function<F, point, point, int, float> {
	 *     public:
	 *        // Import constructors
	 *        using pixled::Function<F, int, point, float>::Function;
	 *
	 *        ...
	 * }
	 * ```
	 *
	 * `F` can then be constructed passing base::Function instances that
	 * returns the specified type for each argument. Constants can also be
	 * passed.
	 *
	 * \note
	 * It is possible to pass function arguments in almost all the way
	 * available in C++, by l-value or r-value, since FctWrapper knows how to
	 * handle all those cases without memory issues. Moreover, notice that f is
	 * copyable, function parameters can be safely destroyed without altering
	 * the Function instance.
	 *
	 * \par
	 * ```cpp
	 * F build_f() {
	 *     // Required to use the * operator properly.
	 *     // This directive can also be called at the namespace level.
	 *     using namespace pixled;
	 *
	 *     // A function that returns a pixled::time
	 *     auto time_fct = 2 * pixled::chrono::T();
	 *
	 *     return F(
	 *         // A constant point, passed by r-value
	 *         pixled::point(1, 1),
	 *         // An function that returns a time, passed by l-value
	 *         time_fct,
	 *         // A function that returns a float, passed by r-value
	 *         pixled::X()
	 *     );
	 * }
	 *
	 * int main(int argc, char** argv) {
	 *     // Builds an f instance
	 *     F f = build_f();
	 *
	 *     // Apply F on p=point(2, 0) at t=10
	 *     std::cout << f(pixled::point(2, 0), 10) << std::endl;
	 * }
	 * ```
	 *
	 * See the complete example below for the complete implementation and
	 * more details about the output.
	 *
	 *
	 * @tparam Implem final Function implementation (CRTP scheme)
	 * @tparam R base::Function return type (fundamental type)
	 * @tparam Args argument types (fundamental types returned by other
	 * functions)
	 */
	template<typename Implem, typename R, typename... Args>
		class Function : public base::Function<R> {
			protected:
				/**
				 * Tuple containing functionnal arguments, that are likely to
				 * be call by the call operator implementation defined in
				 * `Implem`.
				 *
				 * They also be accessed with arg() and call() operators.
				 */
				std::tuple<const FctWrapper<Args>...> args;

			public:
				/**
				 * Return type of this Function.
				 */
				using Type = typename base::Function<R>::Type;

				/**
				 * Function constructor.
				 *
				 * The specified arguments list should be the same size as
				 * `Args`, and each specified argument should be either a
				 * constant of the corresponding type in `Args`, or a
				 * base::Function returning this type.
				 *
				 * Functions specified as arguments can be passed either by
				 * l-value or r-value.
				 *
				 * @tparam Fcts Constructor argument types <b>(automatically
				 * deduced)</b>
				 *
				 * @param fcts functionnal arguments
				 */
				template<typename... Fcts>
					Function(Fcts&& ... fcts) : args(std::forward<Fcts>(fcts)...) {
					}

				/**
				 * Returns a reference to the functionnal argument at index i.
				 *
				 * Indexing starts from 0, and follows the same order as
				 * specified in `args`.
				 *
				 * @tparam i argument index
				 *
				 * @return functionnal argument at position i
				 */
				template<std::size_t i>
					const base::Function<typename std::tuple_element<i, decltype(args)>::type::Type>& arg() const {
						return *std::get<i>(args);
					}

				/**
				 * Calls the functionnal argument at index i with the specified
				 * arguments.
				 *
				 * This helper method is very useful to implement the call
				 * operator of this base::Function.
				 *
				 * Indexing starts from 0, and follows the same order as
				 * specified in `args`.
				 *
				 * See the Function example for an example use case.
				 *
				 * @tparam i argument index
				 *
				 * @param p point
				 * @param t time
				 * @return result of the call to functionnal argument at
				 * position i with the specified parameters
				 *
				 * @see \function_call_operator
				 */
				template<std::size_t i>
					typename std::tuple_element<i, decltype(args)>::type::Type call(point p, time t) const {
						return (*std::get<i>(args))(p, t);
					}

			protected:
				/**
				 * \copydoc pixled::base::Function::copy()
				 */
				base::Function<R>* copy() const override {
					return new Implem(static_cast<const Implem&>(*this));
				}
		};

	namespace detail {
		template<typename To, typename From>
			class Cast : public base::Function<To> {
				private:
					const FctWrapper<From> f;

				public:
					Cast(const base::Function<From>& from)
						: f(from) {}
					Cast(base::Function<From>&& from)
						: f(std::move(from)) {}

					To operator()(point c, time t) const override {
						return (*this->f)(c, t);
					}

					Cast<To, From>* copy() const override {
						return new Cast(*f);
					}
			};
	}

	template<typename To, typename From>
		detail::Cast<To, typename From::Type> Cast(From&& from) {
			return detail::Cast<To, typename From::Type>(std::move(from));
		};

	template<typename To, typename From>
		detail::Cast<To, typename From::Type> Cast(const From& from) {
			return detail::Cast<To, typename From::Type>(from);
		};
}
#endif
