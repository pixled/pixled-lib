#include "pixled/functionnal/comparisons.h"
#include "../api/mock_functionnal.h"

using ::testing::AnyNumber;
using ::testing::Return;

using pixled::MockFunction;
using pixled::MockFctCopy;
using pixled::api::Point;
using pixled::Time;
using pixled::If;

class OperatorTest : public ::testing::Test {
	protected:
		Point p {12, 38};
		Time t {25};
};

class IfOperator : public OperatorTest {};

TEST_F(IfOperator, simple_if_test) {
	MockFunction<bool>* last_condition_copy;
	MockFunction<bool> condition;
	EXPECT_CALL(condition, copy).Times(AnyNumber())
		.WillRepeatedly(Invoke(MockFctCopy<MockFunction<bool>>(last_condition_copy)));

	MockFunction<long>* last_if_copy;
	MockFunction<long> if_statement;
	EXPECT_CALL(if_statement, copy).Times(AnyNumber())
		.WillRepeatedly(Invoke(MockFctCopy<MockFunction<long>>(last_if_copy)));

	MockFunction<long>* last_else_copy;
	MockFunction<long> else_statement;
	EXPECT_CALL(else_statement, copy).Times(AnyNumber())
		.WillRepeatedly(Invoke(MockFctCopy<MockFunction<long>>(last_else_copy)));

	auto if_fct = If<long>(condition, if_statement, else_statement);

	EXPECT_CALL(*last_condition_copy, call(p, t)).WillOnce(Return(true));
	EXPECT_CALL(*last_if_copy, call(p, t)).WillOnce(Return(12));
	EXPECT_CALL(*last_else_copy, call(p, t)).Times(0);
	ASSERT_EQ(if_fct(p, t), 12);

	EXPECT_CALL(*last_condition_copy, call(p, t)).WillOnce(Return(false));
	EXPECT_CALL(*last_if_copy, call(p, t)).Times(0);
	EXPECT_CALL(*last_else_copy, call(p, t)).WillOnce(Return(72));
	ASSERT_EQ(if_fct(p, t), 72);
}
