#include "pixled/functionnal/functionnal.h"
#include "../api/mock_functionnal.h"
#include "pixled/api/utils.h"

using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::StrictMock;

using pixled::MockFunction;
using pixled::MockBinary;
using pixled::api::Point;
using pixled::Time;

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
