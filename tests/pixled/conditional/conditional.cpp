#include "pixled/conditional/conditional.h"
#include "pixled/geometry/geometry.h"
#include "pixled/chroma/chroma.h"
#include "../../mocks/mock_function.h"

using namespace testing;

using pixled::point;
using pixled::conditional::If;

using namespace pixled;

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

class EqualOperator : public OperatorTest {};

TEST_F(EqualOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() == geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({2, 2}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({2, 4}, 0), chroma::RED);
}

TEST_F(EqualOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() == 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({2, 2}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({0, 2}, 0), chroma::RED);

}

TEST_F(EqualOperator, constant_function) {
	auto if_fct = If<color>(
			2 == geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({2, 2}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({0, 2}, 0), chroma::RED);
}
