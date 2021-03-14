#include "pixled/conditional/conditional.h"
#include "../../mocks/mock_function.h"

using namespace testing;

using pixled::point;
using pixled::conditional::If;

class OperatorTest : public Test {
	protected:
		point p {12, 38};
		pixled::time t {25};
};

class IfOperator : public OperatorTest {};

TEST_F(IfOperator, simple_if_test) {
	NiceMock<pixled::MockFunction<bool>> condition;
	NiceMock<pixled::MockFunction<long>> if_statement;
	NiceMock<pixled::MockFunction<long>> else_statement;

	auto if_fct = If<long>(condition, if_statement, else_statement);

	EXPECT_CALL(*condition.last_copy, call(p, t)).WillOnce(Return(true));
	EXPECT_CALL(*if_statement.last_copy, call(p, t)).WillOnce(Return(12));
	EXPECT_CALL(*else_statement.last_copy, call(p, t)).Times(0);
	ASSERT_EQ(if_fct(p, t), 12);

	EXPECT_CALL(*condition.last_copy, call(p, t)).WillOnce(Return(false));
	EXPECT_CALL(*if_statement.last_copy, call(p, t)).Times(0);
	EXPECT_CALL(*else_statement.last_copy, call(p, t)).WillOnce(Return(72));
	ASSERT_EQ(if_fct(p, t), 72);
}
