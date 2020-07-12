#include "pixled/api/functionnal.h"
#include "gmock/gmock.h"

using ::testing::DoAll;
using ::testing::Invoke;

namespace pixled {
	template<typename T>
		class MockFunction : public api::Function<T> {
			public:
				MOCK_METHOD(T, call, (api::Coordinates, Time), (const));
				T operator()(api::Coordinates c, Time t) const override {
					return call(c, t);
				}
				MOCK_METHOD(MockFunction<T>*, copy, (), (const, override));
		};

	template<typename R, typename P1, typename P2>
		class MockBinary : public api::BinaryFunction<R, P1, P2, MockBinary<R, P1, P2>> {
			public:
				MOCK_METHOD(R, call, (api::Coordinates, Time), (const));
				R operator()(api::Coordinates c, Time t) const override {
					return call(c, t);
				}

				template<typename Arg1, typename Arg2>
					MockBinary(Arg1&& arg1, Arg2&& arg2, int expected_calls = 1)
					: api::BinaryFunction<R, P1, P2, MockBinary<R, P1, P2>>(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2))
					{
						ON_CALL(*this, call)
							.WillByDefault(DoAll(
								Invoke(&*this->f1, &api::Function<P1>::operator()),
								Invoke(&*this->f2, &api::Function<P2>::operator())
								));
						EXPECT_CALL(*this, call).Times(expected_calls);
					}
		};
}
