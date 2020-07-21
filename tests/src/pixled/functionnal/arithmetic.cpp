#include "pixled/functionnal/arithmetic.h"
#include "../api/mock_functionnal.h"

using pixled::MockFunction;
using ::testing::Return;
using pixled::api::Point;
using pixled::Time;

class OperatorTest : public ::testing::Test {
	protected:
		Point c {12, 38};
		Time t {25};
};

class PlusOperator : public OperatorTest {};

TEST_F(PlusOperator, simple_plus) {
	MockFunction<float> f1;
	MockFunction<float>* f1_copy_1 {new MockFunction<float>};
	MockFunction<float>* f1_copy_1_copy {new MockFunction<float>};
	MockFunction<float>* f1_copy_2 {new MockFunction<float>};
	MockFunction<float> f2;
	MockFunction<float>* f2_copy {new MockFunction<float>};
	MockFunction<float>* f2_copy_copy {new MockFunction<float>};

    EXPECT_CALL(f1, copy)
		.WillOnce(Return(f1_copy_1))
		.WillOnce(Return(f1_copy_2));
    EXPECT_CALL(*f1_copy_1, copy).WillOnce(Return(f1_copy_1_copy));
    EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
    EXPECT_CALL(*f2_copy, copy).WillOnce(Return(f2_copy_copy));

	auto plus_1 = f1 + f2;

	auto plus = plus_1 + f1;

	EXPECT_CALL(*f1_copy_1_copy, call(c, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(c, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(c, t)).WillRepeatedly(Return(14));

	ASSERT_EQ(plus(c, t), 34);
}

class MinusOperator : public OperatorTest {};

TEST_F(MinusOperator, simple_minus) {
	MockFunction<float> f1;
	MockFunction<float>* f1_copy_1 {new MockFunction<float>};
	MockFunction<float>* f1_copy_1_copy {new MockFunction<float>};
	MockFunction<float>* f1_copy_2 {new MockFunction<float>};
	MockFunction<float> f2;
	MockFunction<float>* f2_copy {new MockFunction<float>};
	MockFunction<float>* f2_copy_copy {new MockFunction<float>};

    EXPECT_CALL(f1, copy)
		.WillOnce(Return(f1_copy_1))
		.WillOnce(Return(f1_copy_2));
    EXPECT_CALL(*f1_copy_1, copy).WillOnce(Return(f1_copy_1_copy));
    EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
    EXPECT_CALL(*f2_copy, copy).WillOnce(Return(f2_copy_copy));

	auto minus_1 = f1 - f2;

	auto minus = minus_1 - f1;

	EXPECT_CALL(*f1_copy_1_copy, call(c, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(c, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(c, t)).WillRepeatedly(Return(14));

	ASSERT_EQ(minus(c, t), -14);
}

class ModulusOperator : public OperatorTest {};

TEST_F(ModulusOperator, test) {
	MockFunction<long> f1;
	MockFunction<long>* f1_copy_1 {new MockFunction<long>};
	MockFunction<long>* f1_copy_1_copy {new MockFunction<long>};
	MockFunction<long>* f1_copy_2 {new MockFunction<long>};
	MockFunction<long> f2;
	MockFunction<long>* f2_copy {new MockFunction<long>};
	MockFunction<long>* f2_copy_copy {new MockFunction<long>};

    EXPECT_CALL(f1, copy)
		.WillOnce(Return(f1_copy_1))
		.WillOnce(Return(f1_copy_2));
    EXPECT_CALL(*f1_copy_1, copy).WillOnce(Return(f1_copy_1_copy));
    EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
    EXPECT_CALL(*f2_copy, copy).WillOnce(Return(f2_copy_copy));

	auto modulus_1 = f1 % f2;

	auto modulus = modulus_1 % f1;

	EXPECT_CALL(*f1_copy_1_copy, call(c, t)).WillRepeatedly(Return(24));
	EXPECT_CALL(*f1_copy_2, call(c, t)).WillRepeatedly(Return(24));
	EXPECT_CALL(*f2_copy_copy, call(c, t)).WillRepeatedly(Return(10));

	ASSERT_EQ(modulus(c, t), (24 % 10) % 24);
}
