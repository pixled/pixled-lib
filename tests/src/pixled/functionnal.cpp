#include "pixled/functionnal.h"
#include "api/mock_functionnal.h"
#include "pixled/api/utils.h"
#include <random>

using ::testing::AnyNumber;
using ::testing::ElementsAreArray;
using ::testing::Not;
using ::testing::Return;
using ::testing::StrictMock;

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

// For a given t, RandomT is supposed to yield a random value that is the same
// whatever the current Point is.
// Moreover, random sequences must be reproducible
TEST(RandomT, uniform_int_test) {
	pixled::RandomT engine (10);
	pixled::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 rd_xy;
	std::uniform_int_distribution<long> xy(-10, 10);

	std::array<int, 100> values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < 100; i++) {
		pixled::api::Point p {xy(rd_xy), xy(rd_xy)};
		int rd_int = rd(p, 10 * i);
		values[i] = rd_int;
		// Since period = 10, the value must keep constant for 10 iterations
		for(Time t = 10 * i; t < 10 * (i + 1); t++) {
			int next_rd_int = rd(p, t);
			ASSERT_EQ(next_rd_int, rd_int);
		}
	}

	// A second run must yield exactly the same values
	for(unsigned long i = 0; i < 100; i++) {
		pixled::api::Point p {xy(rd_xy), xy(rd_xy)};
		int rd_int = rd(p, 10 * i);
		ASSERT_EQ(rd_int, values[i]);
	}
}

TEST(RandomT, uniform_float_test) {
	pixled::RandomT engine (10);
	pixled::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 rd_xy;
	std::uniform_int_distribution<long> xy(-10, 10);

	std::array<float, 100> values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < 100; i++) {
		pixled::api::Point p {xy(rd_xy), xy(rd_xy)};
		float rd_float = rd(p, 10 * i);
		values[i] = rd_float;
		// Since period = 10, the value must keep constant for 10 iterations
		for(Time t = 10 * i; t < 10 * (i + 1); t++) {
			float next_rd_float = rd(p, t);
			ASSERT_FLOAT_EQ(next_rd_float, rd_float);
		}
	}

	// A second run must yield exactly the same values
	for(unsigned long i = 0; i < 100; i++) {
		pixled::api::Point p {xy(rd_xy), xy(rd_xy)};
		float rd_float = rd(p, 10 * i);
		ASSERT_EQ(rd_float, values[i]);
	}
}

// For a given t, RandomXYT is supposed to yield independent random value sequences for each point.
// Moreover, produced sequences must be reproducible.
TEST(RandomXYT, uniform_int_test) {
	pixled::RandomXYT engine (10);
	pixled::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 rd_xy;
	std::uniform_int_distribution<long> xy(-10, 10);

	pixled::api::Point p1 {xy(rd_xy), xy(rd_xy)};
	pixled::api::Point p2 {xy(rd_xy), xy(rd_xy)};
	pixled::api::Point p3 {xy(rd_xy), xy(rd_xy)};
	std::array<int, 100> p1_values;
	std::array<int, 100> p2_values;
	std::array<int, 100> p3_values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < 100; i++) {
		// p1
		int rd_int_1 = rd(p1, 10 * i);
		p1_values[i] = rd_int_1;
		// p2
		int rd_int_2 = rd(p2, 10 * i);
		p2_values[i] = rd_int_2;
		// p3
		int rd_int_3 = rd(p3, 10 * i);
		p3_values[i] = rd_int_3;
		// Since period = 10, the value must keep constant for 10 iterations
		for(Time t = 10 * i; t < 10 * (i + 1); t++) {
			// p1
			int next_rd_int_1 = rd(p1, t);
			ASSERT_EQ(next_rd_int_1, rd_int_1);
			// p2
			int next_rd_int_2 = rd(p2, t);
			ASSERT_EQ(next_rd_int_2, rd_int_2);
			// p3
			int next_rd_int_3 = rd(p3, t);
			ASSERT_EQ(next_rd_int_3, rd_int_3);
		}
	}

	// A second run must yield exactly the same values
	for(unsigned long i = 0; i < 100; i++) {
		// p1
		int rd_int_1 = rd(p1, 10 * i);
		ASSERT_EQ(rd_int_1, p1_values[i]);
		// p2
		int rd_int_2 = rd(p2, 10 * i);
		ASSERT_EQ(rd_int_2, p2_values[i]);
		// p3
		int rd_int_3 = rd(p3, 10 * i);
		ASSERT_EQ(rd_int_3, p3_values[i]);
	}
	ASSERT_THAT(p1_values, Not(ElementsAreArray(p2_values)));
	ASSERT_THAT(p1_values, Not(ElementsAreArray(p3_values)));
	ASSERT_THAT(p2_values, Not(ElementsAreArray(p3_values)));
}

