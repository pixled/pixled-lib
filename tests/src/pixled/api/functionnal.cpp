#include "mock_functionnal.h"

using ::testing::WhenDynamicCastTo;
using ::testing::IsNull;
using ::testing::Not;

using pixled::api::Constant;

TEST(Constant, build) {
	static_assert(
		std::is_same<Constant<double>::Type, double>::value,
		"Constant<double>::Type must be double"
		);

	Constant<double> constant {3.45};

	ASSERT_FLOAT_EQ(constant({2, 4}, 8), 3.45);
}

TEST(Constant, copy) {
	Constant<double> constant {3.45};
	pixled::api::Function<double>* copy = constant.copy();

	ASSERT_THAT(copy, WhenDynamicCastTo<Constant<double>*>(Not(IsNull())));
	ASSERT_EQ((*copy)({3, 5}, 4), 3.45);

	delete copy;
}
