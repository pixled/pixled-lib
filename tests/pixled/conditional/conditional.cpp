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
		led l {p, 5};
		pixled::time t {25};
};

class IfOperator : public OperatorTest {};

TEST_F(IfOperator, simple_if_test) {
	NiceMock<pixled::MockFunction<bool>> condition;
	NiceMock<pixled::MockFunction<long>> if_statement;
	NiceMock<pixled::MockFunction<long>> else_statement;

	auto if_fct = If<long>(condition, if_statement, else_statement);

	EXPECT_CALL(*condition.last_copy, call(l, t)).WillOnce(Return(true));
	EXPECT_CALL(*if_statement.last_copy, call(l, t)).WillOnce(Return(12));
	EXPECT_CALL(*else_statement.last_copy, call(l, t)).Times(0);
	ASSERT_EQ(if_fct(l, t), 12);

	EXPECT_CALL(*condition.last_copy, call(l, t)).WillOnce(Return(false));
	EXPECT_CALL(*if_statement.last_copy, call(l, t)).Times(0);
	EXPECT_CALL(*else_statement.last_copy, call(l, t)).WillOnce(Return(72));
	ASSERT_EQ(if_fct(l, t), 72);
}

class EqualOperator : public OperatorTest {};

TEST_F(EqualOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() == geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 0}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{2, 4}, 3}, 0), chroma::RED);
}

TEST_F(EqualOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() == 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 127}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{0, 2}, 8}, 0), chroma::RED);

}

TEST_F(EqualOperator, constant_function) {
	auto if_fct = If<color>(
			2 == geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 7}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{0, 2}, 4}, 0), chroma::RED);
}

class NotEqualOperator : public OperatorTest {};

TEST_F(NotEqualOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() != geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 9}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{2, 4}, 18}, 0), chroma::BLUE);
}

TEST_F(NotEqualOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() != 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 4}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{0, 2}, 3}, 0), chroma::BLUE);

}

TEST_F(NotEqualOperator, constant_function) {
	auto if_fct = If<color>(
			2 != geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 0}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{0, 2}, 10}, 0), chroma::BLUE);
}

class LessThanOperator : public OperatorTest {};

TEST_F(LessThanOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() < geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 6}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{2, 4}, 3}, 0), chroma::BLUE);
}

TEST_F(LessThanOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() < 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 5}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{0, 2}, 3}, 0), chroma::BLUE);

}

TEST_F(LessThanOperator, constant_function) {
	auto if_fct = If<color>(
			2 < geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 8}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{4, 2}, 7}, 0), chroma::BLUE);
}

class LessThanOrEqualOperator : public OperatorTest {};

TEST_F(LessThanOrEqualOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() <= geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 1}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{5, 4}, 6}, 0), chroma::RED);
}

TEST_F(LessThanOrEqualOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() <= 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 3}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{3, 2}, 1}, 0), chroma::RED);

}

TEST_F(LessThanOrEqualOperator, constant_function) {
	auto if_fct = If<color>(
			2 <= geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 4}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{0, 2}, 0}, 0), chroma::RED);
}

class GreaterThanOperator : public OperatorTest {};

TEST_F(GreaterThanOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() > geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 3}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{4, 2}, 9}, 0), chroma::BLUE);
}

TEST_F(GreaterThanOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() < 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 7}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{0, 2}, 0}, 0), chroma::BLUE);

}

TEST_F(GreaterThanOperator, constant_function) {
	auto if_fct = If<color>(
			2 > geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 4}, 0), chroma::RED);
	ASSERT_EQ(if_fct({{1, 4}, 5}, 0), chroma::BLUE);
}

class GreaterThanOrEqualOperator : public OperatorTest {};

TEST_F(GreaterThanOrEqualOperator, two_functions) {
	auto if_fct = If<color>(
			geometry::X() >= geometry::Y(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 0}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{4, 5}, 7}, 0), chroma::RED);
}

TEST_F(GreaterThanOrEqualOperator, function_constant) {
	auto if_fct = If<color>(
			geometry::X() >= 2,
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 2}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{1, 3}, 4}, 0), chroma::RED);

}

TEST_F(GreaterThanOrEqualOperator, constant_function) {
	auto if_fct = If<color>(
			2 >= geometry::X(),
			chroma::rgb(0, 0, 255),
			chroma::rgb(255, 0, 0)
			);

	ASSERT_EQ(if_fct({{2, 2}, 16}, 0), chroma::BLUE);
	ASSERT_EQ(if_fct({{3, 0}, 22}, 0), chroma::RED);
}
