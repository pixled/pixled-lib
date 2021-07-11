#include "pixled/arithmetic/arithmetic.h"
#include "pixled/geometry/geometry.h"
#include "../../mocks/mock_function.h"
#include "pixled/chroma/chroma.h"

using ::testing::Test;
using ::testing::Return;

using pixled::MockFunction;
using namespace pixled;

class OperatorTest : public Test {
	protected:
		point c {12, 38};
		led l {c, 4};
		pixled::time t {25};
};

class PlusOperator : public OperatorTest {};

TEST_F(PlusOperator, test) {
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

	EXPECT_CALL(*f1_copy_1_copy, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(l, t)).WillRepeatedly(Return(14));

	ASSERT_EQ(plus(l, t), 34);
}

TEST_F(PlusOperator, two_functions) {
	auto plus = geometry::X() + geometry::Y();
	ASSERT_EQ(plus({{2, 3}, 0}, 0), 5);
}

TEST_F(PlusOperator, constant_function) {
	auto plus = 5 + geometry::Y();
	ASSERT_EQ(plus({{2, 3}, 7}, 0), 8);
}

TEST_F(PlusOperator, function_constant) {
	auto plus = geometry::X() + 5;
	ASSERT_EQ(plus({{2, 3}, 5}, 0), 7);
}

class MinusOperator : public OperatorTest {};

TEST_F(MinusOperator, test) {
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

	EXPECT_CALL(*f1_copy_1_copy, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(l, t)).WillRepeatedly(Return(14));

	ASSERT_EQ(minus(l, t), -14);
}

TEST_F(MinusOperator, two_functions) {
	auto minus = geometry::X() - geometry::Y();
	ASSERT_EQ(minus({{2, 3}, 12}, 0), -1);
}

TEST_F(MinusOperator, constant_function) {
	auto minus = 5 - geometry::Y();
	ASSERT_EQ(minus({{2, 3}, 9}, 0), 2);
}

TEST_F(MinusOperator, function_constant) {
	auto minus = geometry::X() - 5;
	ASSERT_EQ(minus({{2, 3}, 23}, 0), -3);
}

class MultiplyOperator : public OperatorTest {};

TEST_F(MultiplyOperator, test) {
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

	auto mult_1 = f1 * f2;

	auto mult = mult_1 * f1;

	EXPECT_CALL(*f1_copy_1_copy, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(l, t)).WillRepeatedly(Return(14));

	ASSERT_FLOAT_EQ(mult(l, t), 1400);
}

TEST_F(MultiplyOperator, two_functions) {
	auto multiply = geometry::X() * geometry::Y();
	ASSERT_EQ(multiply({{2, 3}, 8}, 0), 6);
}

TEST_F(MultiplyOperator, constant_function) {
	auto multiply = 5 * geometry::Y();
	ASSERT_EQ(multiply({{2, 3}, 8}, 0), 15);
}

TEST_F(MultiplyOperator, function_constant) {
	auto multiply = geometry::X() * 5;
	ASSERT_EQ(multiply({{2, 3}, 5}, 0), 10);
}

class DivideOperator : public OperatorTest {};

TEST_F(DivideOperator, test) {
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

	auto div_1 = f1 / f2;

	auto div = div_1 / f1;

	EXPECT_CALL(*f1_copy_1_copy, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(l, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(l, t)).WillRepeatedly(Return(14));

	ASSERT_FLOAT_EQ(div(l, t), 1 / 14.f);
}

TEST_F(DivideOperator, two_functions) {
	auto divide = geometry::X() / geometry::Y();
	ASSERT_EQ(divide({{6, 3}, 1}, 0), 2);
}

TEST_F(DivideOperator, constant_function) {
	auto divide = 10 / geometry::Y();
	ASSERT_EQ(divide({{2, 2}, 2}, 0), 5);
}

TEST_F(DivideOperator, function_constant) {
	auto divide = geometry::X() / 5;
	ASSERT_EQ(divide({{15, 3}, 0}, 0), 3);
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

	EXPECT_CALL(*f1_copy_1_copy, call(l, t)).WillRepeatedly(Return(24));
	EXPECT_CALL(*f1_copy_2, call(l, t)).WillRepeatedly(Return(24));
	EXPECT_CALL(*f2_copy_copy, call(l, t)).WillRepeatedly(Return(10));

	ASSERT_EQ(modulus(l, t), (24 % 10) % 24);
}

TEST_F(ModulusOperator, two_functions) {
	auto modulus = Cast<int>(geometry::X()) % Cast<int>(geometry::Y());
	ASSERT_EQ(modulus({{6, 4}, 2}, 0), 2);
}

TEST_F(ModulusOperator, constant_function) {
	auto modulus = 10 % Cast<int>(geometry::Y());
	ASSERT_EQ(modulus({{2, 3}, 8}, 0), 1);
}

TEST_F(ModulusOperator, function_constant) {
	auto modulus = Cast<int>(geometry::X()) % 5;
	ASSERT_EQ(modulus({{14, 3}, 0}, 0), 4);
}
