#include "pixled/functionnal.h"
#include "api/mock_functionnal.h"
#include "pixled/api/utils.h"
#include <random>

using ::testing::Return;
using ::testing::StrictMock;
using ::testing::AnyNumber;

using pixled::MockFunction;
using pixled::MockBinary;
using pixled::api::Point;

class OperatorTest : public ::testing::Test {
	protected:
		Point c {12, 38};
		Time t {25};
};

class BinaryTest : public OperatorTest {};

TEST_F(BinaryTest, build_by_lvalue) {
	StrictMock<MockFunction<float>> f1;
	StrictMock<MockFunction<float>>* f1_copy = new StrictMock<MockFunction<float>>;
	StrictMock<MockFunction<float>> f2;
	StrictMock<MockFunction<float>>* f2_copy = new StrictMock<MockFunction<float>>;

	EXPECT_CALL(f1, copy).WillOnce(Return(f1_copy));
	EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
	StrictMock<MockBinary<float, float, float>> mock {f1, f2};

	EXPECT_CALL(*f1_copy, call(c, t)).WillOnce(Return(10));
	EXPECT_CALL(*f2_copy, call(c, t)).WillOnce(Return(14));

	mock(c, t);
}

TEST_F(BinaryTest, nested_by_lvalue) {
	MockFunction<float> f1;
	MockFunction<float>* f1_copy {new MockFunction<float>};
	MockFunction<float>* f1_copy_copy {new MockFunction<float>};
	MockFunction<float> f2;
	MockFunction<float>* f2_copy {new MockFunction<float>};
	MockFunction<float>* f2_copy_copy {new MockFunction<float>};
	MockFunction<float> f3;
	MockFunction<float>* f3_copy {new MockFunction<float>};

	EXPECT_CALL(f1, copy).WillOnce(Return(f1_copy));
	EXPECT_CALL(*f1_copy, copy).WillOnce(Return(f1_copy_copy));
	EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
	EXPECT_CALL(*f2_copy, copy).WillOnce(Return(f2_copy_copy));
	EXPECT_CALL(f3, copy).WillOnce(Return(f3_copy));

	EXPECT_CALL(*f1_copy_copy, call(c, t));
	EXPECT_CALL(*f2_copy_copy, call(c, t));
	EXPECT_CALL(*f3_copy, call(c, t)).Times(1);

	MockBinary<float, float, float> mock_1 {f1, f2, 0};

	MockBinary<float, float, float> mock_2 {mock_1, f3, 1};

	mock_2(c, t);
}

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

class SinTest : public OperatorTest {};

TEST_F(SinTest, constant_sin) {
	float i = 2.7;
	pixled::Sin<float> sin {i};

	ASSERT_EQ(sin(c, t), std::sin(i));
}

TEST_F(SinTest, complex_sin) {
	MockFunction<float> f1;
	MockFunction<float>* f1_copy {new MockFunction<float>};
	MockFunction<float>* f1_copy_copy {new MockFunction<float>};

	MockFunction<float> f2;
	MockFunction<float>* f2_copy {new MockFunction<float>};
	MockFunction<float>* f2_copy_copy {new MockFunction<float>};

	EXPECT_CALL(f1, copy).WillOnce(Return(f1_copy));
	EXPECT_CALL(*f1_copy, copy).WillOnce(Return(f1_copy_copy));
	EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
	EXPECT_CALL(*f2_copy, copy).WillOnce(Return(f2_copy_copy));

	auto product = f1 * f2;

	std::mt19937 engine;
	std::uniform_real_distribution<float> random_f {0, 100};

	pixled::Sin<float> sin {product};
	for(int i = 0; i < 100; i++) {
		float f1_result = random_f(engine);
		float f2_result = random_f(engine);

		EXPECT_CALL(*f1_copy_copy, call(c, t)).WillOnce(Return(f1_result));
		EXPECT_CALL(*f2_copy_copy, call(c, t)).WillOnce(Return(f2_result));

		ASSERT_FLOAT_EQ(sin(c, t), std::sin(f1_result * f2_result));
	}
}
