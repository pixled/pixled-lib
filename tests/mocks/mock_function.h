#include "pixled/function.h"
#include "gmock/gmock.h"

using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::AtMost;

namespace pixled {

	template<typename T>
		class MockFunction : public base::Function<T> {
			public:
				const MockFunction<T>* origin = nullptr;
				mutable MockFunction<T>* last_copy;

				MockFunction() {
					ON_CALL(*this, copy)
						.WillByDefault(Invoke([this] () {
									return new testing::NiceMock<MockFunction<T>>(*this);
									}));
				}
				MockFunction(const MockFunction<T>& other) : MockFunction() {
					if(other.origin == nullptr)
						this->origin = &other;
					else
						this->origin = other.origin;
					this->origin->last_copy = this;
				}

				MOCK_METHOD(T, call, (Point, Time), (const));
				T operator()(Point c, Time t) const override {
					return call(c, t);
				}
				MOCK_METHOD(MockFunction<T>*, copy, (), (const, override));
		};

	template<typename R, typename P>
		class MockUnary : public Function<MockUnary<R, P>, R, P> {
			public:
				MOCK_METHOD(R, call, (Point, Time), (const));
				R operator()(Point c, Time t) const override {
					return call(c, t);
				}

				MockUnary(const MockUnary<R, P>& other)
					: MockUnary(other.template arg<0>()) {
					}

				template<typename Arg>
					MockUnary(Arg&& arg0)
					: Function<MockUnary<R, P>, R, P>(std::forward<Arg>(arg0))
					{
						ON_CALL(*this, call)
							.WillByDefault(
								Invoke(&(this->template arg<0>()), &base::Function<P>::operator())
								);
					}
		};

	template<typename R, typename P1, typename P2>
		class MockBinary : public Function<MockBinary<R, P1, P2>, R, P1, P2> {
			public:
				MOCK_METHOD(R, call, (Point, Time), (const));
				R operator()(Point c, Time t) const override {
					return call(c, t);
				}

				MockBinary(const MockBinary<R, P1, P2>& other)
					: MockBinary(
							other.template arg<0>(), other.template arg<1>()
							) {
					}

				template<typename Arg1, typename Arg2>
					MockBinary(Arg1&& arg1, Arg2&& arg2, int expected_calls = 1)
					: Function<MockBinary<R, P1, P2>, R, P1, P2>(
							std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)
							) {
						ON_CALL(*this, call)
							.WillByDefault(DoAll(
								Invoke(&(this->template arg<0>()), &base::Function<P1>::operator()),
								Invoke(&(this->template arg<1>()), &base::Function<P2>::operator())
								));
					}
		};
}
