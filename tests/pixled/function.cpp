#include "../mocks/mock_function.h"
#include "pixled/chrono/chrono.h"
#include "pixled/geometry/geometry.h"

using namespace testing;

using pixled::Constant;
using pixled::FctWrapper;

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
	pixled::base::Function<double>* copy = constant.copy();

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
		auto& test = dynamic_cast<const Constant<float>&>(*w);
		ASSERT_FLOAT_EQ(test({2, 6}, 24), 2.35);
	}
	catch(std::bad_cast&) {
		FAIL();
	}

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

/**
 * Tests basic pixled::Function features with a single parameter.
 *
 * Considering the tuple based implementation of pixled::Function, we assume
 * that this will work for any number of parameter if those tests pass.
 */
class UnaryTest : public Test {
	protected:
		pixled::point c {12, 38};
		pixled::time t {25};

		StrictMock<pixled::MockFunction<uint8_t>> fct;
		//StrictMock<pixled::MockFunction<uint8_t>>* last_fct_copy;
		//pixled::MockFctCopy<decltype(fct)> mock_copy {last_fct_copy};

		void SetUp() override {
			//mock_copy.setUp(fct);
		}
};

TEST_F(UnaryTest, lvalue_build) {
	StrictMock<pixled::MockFunction<uint8_t>>* fct_copy
		= new StrictMock<pixled::MockFunction<uint8_t>>;
	EXPECT_CALL(fct, copy).WillOnce(Return(fct_copy));

	pixled::MockUnary<float, uint8_t> unary {fct};

	EXPECT_CALL(unary, call(c, t));
	EXPECT_CALL(*fct_copy, call(c, t));

	unary(c, t);
}

struct MockFunctionCopy : public StrictMock<pixled::MockFunction<uint8_t>> {
	MockFunctionCopy() {}

	MockFunctionCopy(MockFunctionCopy* copy) {
		ON_CALL(*this, copy)
			.WillByDefault(Return(copy));
		EXPECT_CALL(*this, copy).Times(1);
	}
};

TEST_F(UnaryTest, rvalue_build) {
	MockFunctionCopy* copy = new MockFunctionCopy;
	// Even if MockFunctionCopy() is technically moved it is still copied so
	// that it can be safely destroyed at the end of the call.
	pixled::MockUnary<float, uint8_t> unary {MockFunctionCopy(copy)};

	EXPECT_CALL(unary, call(c, t));
	EXPECT_CALL(*copy, call(c, t));

	unary(c, t);
}

TEST_F(UnaryTest, constant_build) {
	pixled::MockUnary<float, uint8_t> unary {27};

	EXPECT_CALL(unary, call(c, t));
	ASSERT_EQ(unary(c, t), 27);
}

TEST_F(UnaryTest, fct_wrapper) {
	// First copy to initialize `unary`
	StrictMock<pixled::MockFunction<uint8_t>>* fct_copy
		= new StrictMock<pixled::MockFunction<uint8_t>>;
	EXPECT_CALL(fct, copy).WillOnce(Return(fct_copy));

	// This mock is not supposed to be called
	pixled::MockUnary<float, uint8_t> unary {fct};

	// Second copy to initialize `unary_wrapper`, since `unary` itself is
	// copied into `unary_wrapper`, leaving `unary` unchanged and usable.
	StrictMock<pixled::MockFunction<uint8_t>>* fct_copy_copy
		= new StrictMock<pixled::MockFunction<uint8_t>>;
	EXPECT_CALL(*fct_copy, copy).WillOnce(Return(fct_copy_copy));
	// Makes a copy of unary
	pixled::FctWrapper<float> unary_wrapper {unary};

	// Assert that the copy is also a MockUnary
	ASSERT_THAT(
			&unary_wrapper.get(),
			(WhenDynamicCastTo<const decltype(unary)*>(Not(IsNull())))
			);

	// Call to unary_copy...
	EXPECT_CALL(
			dynamic_cast<const decltype(unary)&>(unary_wrapper.get()),
			call(c, t)
			);
	// ... that itself triggers a call to the last `fct` copy
	EXPECT_CALL(
			*fct_copy_copy,
			call(c, t)
			);

	// Actual call
	unary_wrapper.get()(c, t);
}

/**
 * Some additional tests for pixled::Function with two parameters.
 */
typedef UnaryTest BinaryTest;

TEST_F(BinaryTest, lvalue_build) {
	using pixled::MockFunction;
	using pixled::MockBinary;

	StrictMock<MockFunction<float>> f1;
	StrictMock<MockFunction<float>>* f1_copy = new StrictMock<MockFunction<float>>;
	StrictMock<MockFunction<float>> f2;
	StrictMock<MockFunction<float>>* f2_copy = new StrictMock<MockFunction<float>>;

	EXPECT_CALL(f1, copy).WillOnce(Return(f1_copy));
	EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
	StrictMock<MockBinary<float, float, float>> mock {f1, f2};

	EXPECT_CALL(mock, call(c, t));
	EXPECT_CALL(*f1_copy, call(c, t)).WillOnce(Return(10));
	EXPECT_CALL(*f2_copy, call(c, t)).WillOnce(Return(14));

	mock(c, t);
}

TEST_F(BinaryTest, rvalue_build) {
	using pixled::MockFunction;
	using pixled::MockBinary;

	StrictMock<MockFunction<float>> f1;
	StrictMock<MockFunction<float>>* f1_copy = new StrictMock<MockFunction<float>>;
	StrictMock<MockFunction<float>> f2;
	StrictMock<MockFunction<float>>* f2_copy = new StrictMock<MockFunction<float>>;

	EXPECT_CALL(f1, copy).WillOnce(Return(f1_copy));
	EXPECT_CALL(f2, copy).WillOnce(Return(f2_copy));
	StrictMock<MockBinary<float, float, float>> mock {std::move(f1), std::move(f2)};

	EXPECT_CALL(mock, call(c, t));
	EXPECT_CALL(*f1_copy, call(c, t)).WillOnce(Return(10));
	EXPECT_CALL(*f2_copy, call(c, t)).WillOnce(Return(14));

	mock(c, t);
}

TEST_F(BinaryTest, nested_lvalue_build) {
	using pixled::MockFunction;
	using pixled::MockBinary;

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

	MockBinary<float, float, float> mock_1 {f1, f2, 0};
	MockBinary<float, float, float> mock_2 {mock_1, f3, 1};

	EXPECT_CALL(mock_1, call).Times(0);

	EXPECT_CALL(mock_2, call(c, t));
	EXPECT_CALL(dynamic_cast<const decltype(mock_1)&>(mock_2.arg<0>()), call(c, t));
	EXPECT_CALL(*f1_copy_copy, call(c, t));
	EXPECT_CALL(*f2_copy_copy, call(c, t));
	EXPECT_CALL(*f3_copy, call(c, t)).Times(1);
	mock_2(c, t);
}

TEST(Cast, lvalue) {
	const auto& t = pixled::chrono::T();
	auto function = pixled::Cast<float>(t);

	ASSERT_FLOAT_EQ(function({0, 0}, 10), 10.f);
}

TEST(Cast, rvalue) {
	auto function = pixled::Cast<int>(pixled::geometry::X());

	ASSERT_FLOAT_EQ(function({14.5, 0}, 10), 14);
}
