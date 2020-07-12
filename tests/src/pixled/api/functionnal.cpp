#include "mock_functionnal.h"

using ::testing::AtMost;
using ::testing::Return;
using ::testing::WhenDynamicCastTo;
using ::testing::IsNull;
using ::testing::Not;

using pixled::api::Constant;
using pixled::api::FctWrapper;

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

class FctWrapperTest : public ::testing::Test {
	protected:
	pixled::MockFunction<float> fct;
	pixled::MockFunction<float>* copy = new pixled::MockFunction<float>;

	void SetUp() override {
		EXPECT_CALL(fct, copy).Times(AtMost(1))
			.WillOnce(Return(copy));
	}
};

TEST_F(FctWrapperTest, build) {
	FctWrapper<float> w {fct};

	ASSERT_EQ(&*w, copy);
}

TEST_F(FctWrapperTest, build_from_constant) {
	FctWrapper<float> w {2.35};

	try{
		dynamic_cast<const Constant<float>&>(*w);
	}
	catch(std::bad_cast&) {
		FAIL();
	}
	ASSERT_FLOAT_EQ((*w)({2, 6}, 24), 2.35);

	// Unused
	delete copy;
}

TEST_F(FctWrapperTest, copy_constructor) {
	// w1 is copied, so the internal copied ptr will be copied again
	pixled::MockFunction<float>* copy_copy = new pixled::MockFunction<float>;
	EXPECT_CALL(*copy, copy)
		.WillOnce(Return(copy_copy));

	FctWrapper<float> w1 {fct};
	FctWrapper<float> w2 {w1};

	ASSERT_EQ(&*w2, copy_copy);
}

TEST_F(FctWrapperTest, move_constructor) {
	// This test implicitely ensure that no memory leaks / error occurs in the
	// process of moving the internal pointer of w1 to w2. Concretely, this
	// internal pointer is still freed once and exactly once.
	FctWrapper<float> w1 {fct};
	FctWrapper<float> w2 {std::move(w1)};

	ASSERT_EQ(&*w2, copy);
}

TEST_F(FctWrapperTest, copy_assignment) {
	// Initializes w2 with some fct
	pixled::MockFunction<float> fct_2;
	pixled::MockFunction<float>* copy_2 = new pixled::MockFunction<float>;
	EXPECT_CALL(fct_2, copy)
		.WillOnce(Return(copy_2));
	FctWrapper<float> w2 {fct_2};

	pixled::MockFunction<float>* copy_copy = new pixled::MockFunction<float>;
	EXPECT_CALL(*copy, copy)
		.WillOnce(Return(copy_copy));

	FctWrapper<float> w1 {fct};

	// Copy assign w1 to w2
	w2 = w1;

	ASSERT_EQ(&*w2, copy_copy);
}

TEST_F(FctWrapperTest, move_assignment) {
	// Initializes w2 with some fct
	pixled::MockFunction<float> fct_2;
	pixled::MockFunction<float>* copy_2 = new pixled::MockFunction<float>;
	EXPECT_CALL(fct_2, copy).Times(AtMost(1))
		.WillOnce(Return(copy_2));
	FctWrapper<float> w2 {fct_2};

	FctWrapper<float> w1 {fct};
	// Move w1 to w2
	// Notice that the internal w1 pointer does not need to be copied
	w2 = std::move(w1);

	ASSERT_EQ(&*w2, copy);
}
