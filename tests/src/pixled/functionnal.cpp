#include "pixled/functionnal.h"
#include "api/mock_functionnal.h"
#include "pixled/api/utils.h"
#include <random>

using ::testing::Return;
using ::testing::StrictMock;
using ::testing::AnyNumber;

using pixled::MockFunction;
using pixled::MockBinary;
using pixled::Coordinates;

class OperatorTest : public ::testing::Test {
	protected:
		Coordinates c {12, 38};
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
	StrictMock<MockBinary<float>> mock {f1, f2};

	EXPECT_CALL(*f1_copy, call(c, t)).WillOnce(Return(10));
	EXPECT_CALL(*f2_copy, call(c, t)).WillOnce(Return(14));
	//EXPECT_CALL(mock, call(c, t));

	mock(c, t);
}

/*
 *TEST_F(BinaryTest, simple_by_rvalue) {
 *    StrictMock<MockFunction<float>> f1;
 *    StrictMock<MockFunction<float>>* f1_move = new StrictMock<MockFunction<float>>;
 *    StrictMock<MockFunction<float>> f2;
 *    StrictMock<MockFunction<float>>* f2_move = new StrictMock<MockFunction<float>>;
 *
 *    EXPECT_CALL(f1, move).WillOnce(Return(f1_move));
 *    EXPECT_CALL(f2, move).WillOnce(Return(f2_move));
 *    EXPECT_CALL(*f1_move, call(c, t));
 *    EXPECT_CALL(*f2_move, call(c, t));
 *
 *    StrictMock<MockBinary<float>> mock {std::move(f1), std::move(f2)};
 *
 *    mock(c, t);
 *}
 */

/*
 *TEST_F(BinaryTest, nested_by_rvalue) {
 *    StrictMock<MockFunction<float>> f1;
 *    StrictMock<MockFunction<float>> f2;
 *
 *    StrictMock<MockFunction<float>> f3;
 *    StrictMock<MockFunction<float>>* f3_move = new StrictMock<MockFunction<float>>;
 *
 *    EXPECT_CALL(f3, move).WillOnce(Return(f3_move));
 *
 *    EXPECT_CALL(f1, call(c, t));
 *    EXPECT_CALL(f2, call(c, t));
 *    EXPECT_CALL(*f3_move, call(c, t));
 *
 *    // Lvalues to f1 and f2
 *    StrictMock<MockBinary<float>> mock_to_move {f1, f2, 0};
 *    // Rvalue to mock_to_move and f3
 *    StrictMock<MockBinary<float>> mock {std::move(mock_to_move), std::move(f3)};
 *
 *    mock(c, t);
 *
 *    // f1 and f2 can still be used
 *    EXPECT_CALL(f1, call(c, t));
 *    EXPECT_CALL(f2, call(c, t));
 *    f1(c, t);
 *    f2(c, t);
 *}
 */

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

	MockBinary<float> mock_1 {f1, f2, 0};
	//EXPECT_CALL(mock_1, copy).WillOnce(Return(new MockBinary<float> {f1, f2, 2}));

	MockBinary<float> mock_2 {mock_1, f3, 1};

	//EXPECT_CALL(mock_1, copy).WillOnce(Return(new MockBinary<float> {f1, f2, 2}));
	//EXPECT_CALL(mock_1, copy).WillOnce(Return(new MockBinary<float> {f1, f2, 2}));
	//EXPECT_CALL(mock_2, copy).WillOnce(Return(new MockBinary<float> {mock_1, f3, 1}));
	// Plus_1 can be safely reused, without memory issues.
	//MockBinary<float> mock_3 {mock_1, mock_2, 1};

	//mock_3(c, t);
	mock_2(c, t);
}

/*
 *TEST_F(BinaryTest, nested_by_lvalue_and_rvalue) {
 *    MockFunction<float> f1;
 *    MockFunction<float> f2;
 *    MockFunction<float> f3;
 *
 *    EXPECT_CALL(f1, call(c, t));
 *    EXPECT_CALL(f2, call(c, t));
 *    EXPECT_CALL(f3, call(c, t)).Times(2);
 *
 *    // First argument is forwarded as rvalue, second by lvalue
 *    MockBinary<float> mock {MockBinary<float>(f1, f2, 0), f3};
 *
 *    // f3 can be safely reused
 *    MockBinary<float> other_mock {mock, f3};
 *
 *    other_mock(c, t);
 *}
 */

class PlusOperator : public OperatorTest {};

TEST_F(PlusOperator, simple_plus_by_lvalue) {
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

	pixled::Plus<float> plus = plus_1 + f1;

	EXPECT_CALL(*f1_copy_1_copy, call(c, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f1_copy_2, call(c, t)).WillRepeatedly(Return(10));
	EXPECT_CALL(*f2_copy_copy, call(c, t)).WillRepeatedly(Return(14));

	ASSERT_EQ(plus(c, t), 34);
}

/*
 *TEST_F(PlusOperator, nested_plus_by_rvalue) {
 *    MockFunction<float> f1;
 *    MockFunction<float> f2;
 *    MockFunction<float> f3;
 *    MockFunction<float>* f3_move = new MockFunction<float>;
 *
 *    EXPECT_CALL(f3, move).WillOnce(Return(f3_move));
 *
 *    EXPECT_CALL(f1, call(c, t)).WillOnce(Return(7));
 *    EXPECT_CALL(f2, call(c, t)).WillOnce(Return(17));
 *    EXPECT_CALL(*f3_move, call(c, t)).WillOnce(Return(3));
 *
 *    pixled::Plus<float> plus = f1 + f2 + std::move(f3);
 *
 *    ASSERT_EQ(plus(c, t), 27);
 *}
 */

/*
 *TEST_F(PlusOperator, nested_plus_by_lvalue) {
 *    MockFunction<float> f1;
 *    MockFunction<float>* f1_copy {new MockFunction<float>};
 *    MockFunction<float>* f1_copy_copy {new MockFunction<float>};
 *    MockFunction<float> f2;
 *    MockFunction<float>* f2_copy {new MockFunction<float>};
 *    MockFunction<float>* f2_copy_copy {new MockFunction<float>};
 *    MockFunction<float> f3;
 *    MockFunction<float>* f3_copy {new MockFunction<float>};
 *
 *    //EXPECT_CALL(f1, copy).WillOnce(Return(f1_copy));
 *    //EXPECT_CALL(f1, copy).WillRepeatedly(Return(&f1));
 *    EXPECT_CALL(*f1_copy, copy).WillOnce(Return(f1_copy_copy));
 *    EXPECT_CALL(*f1_copy_copy, copy).WillOnce(Return(f1_copy_copy));
 *    EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
 *    EXPECT_CALL(*f2_copy, copy).WillOnce(Return(f2_copy_copy));
 *    EXPECT_CALL(f3, copy).WillOnce(Return(f3_copy));
 *
 *    EXPECT_CALL(*f1_copy_copy, call(c, t)).WillRepeatedly(Return(7));
 *    EXPECT_CALL(*f2_copy_copy, call(c, t)).WillRepeatedly(Return(17));
 *    EXPECT_CALL(*f3_copy, call(c, t)).WillRepeatedly(Return(3));
 *
 *    //pixled::Plus<float> plus {f1, f2};
 *
 *    //auto plus_1 = f1 + f2;
 *
 *    //pixled::Plus<float> plus = plus_1 + f3;
 *
 *    // Plus_1 can be safely reused, without memory issues.
 *    //pixled::Plus<float> other_plus = plus_1 + plus;
 *
 *    //ASSERT_EQ(plus(c, t), 27);
 *    //ASSERT_EQ(other_plus(c, t), 7+17+27);
 *}
 */

/*
 *TEST_F(PlusOperator, nested_plus_by_lvalue_and_rvalue) {
 *    MockFunction<float> f1;
 *    MockFunction<float> f2;
 *    MockFunction<float> f3;
 *
 *    EXPECT_CALL(f1, call(c, t)).WillRepeatedly(Return(7));
 *    EXPECT_CALL(f2, call(c, t)).WillRepeatedly(Return(17));
 *    EXPECT_CALL(f3, call(c, t)).WillRepeatedly(Return(3));
 *
 *    // First argument is forwarded as rvalue, second by lvalue
 *    pixled::Plus<float> plus = f1 + f2 + f3;
 *
 *    // f3 can be safely reused
 *    pixled::Plus<float> other_plus = plus + f3;
 *
 *    ASSERT_EQ(plus(c, t), 27);
 *    ASSERT_EQ(other_plus(c, t), 30);
 *}
 *
 *TEST_F(PlusOperator, move_assignment) {
 *    MockFunction<float> f1;
 *    MockFunction<float>* f1_move = new MockFunction<float>;
 *    MockFunction<float> f2;
 *    MockFunction<float>* f2_move = new MockFunction<float>;
 *    MockFunction<float> f3;
 *
 *    EXPECT_CALL(f1, move).WillOnce(Return(f1_move));
 *    EXPECT_CALL(f2, move).WillOnce(Return(f2_move));
 *
 *    EXPECT_CALL(f3, call(c, t)).WillRepeatedly(Return(8));
 *    EXPECT_CALL(*f1_move, call(c, t)).WillRepeatedly(Return(13));
 *    EXPECT_CALL(*f2_move, call(c, t)).WillRepeatedly(Return(31));
 *
 *    auto plus = std::move(f1) + std::move(f2);
 *
 *    auto other_plus = std::move(plus) + f3;
 *
 *    ASSERT_EQ(other_plus(c, t), 52);
 *}
 */

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

	pixled::Multiplies<float> product = f1 * f2;

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
