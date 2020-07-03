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

	template<typename T>
		class MockBinary : public api::BinaryFunction<T, MockBinary> {
			public:
				MOCK_METHOD(T, call, (api::Coordinates, Time), (const));
				T operator()(api::Coordinates c, Time t) const override {
					return call(c, t);
				}

				template<typename Arg1, typename Arg2>
					MockBinary(Arg1&& arg1, Arg2&& arg2, int expected_calls = 1)
					: api::BinaryFunction<T, MockBinary>(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2))
					{
						ON_CALL(*this, call)
							.WillByDefault(DoAll(
								Invoke(&*this->f1, &api::Function<T>::operator()),
								Invoke(&*this->f2, &api::Function<T>::operator())
								));
						EXPECT_CALL(*this, call).Times(expected_calls);
					}
		};
}
