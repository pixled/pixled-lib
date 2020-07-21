#include "pixled/functionnal/random.h"
#include "gmock/gmock.h"

using ::testing::ElementsAreArray;
using ::testing::Not;

using pixled::Time;

// For a given t, RandomT is supposed to yield a random value that is the same
// whatever the current Point is.
// Moreover, random sequences must be reproducible
TEST(RandomT, uniform_int_test) {
	pixled::RandomT engine (10);
	pixled::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 rd_xy;
	std::uniform_real_distribution<float> xy(-10, 10);

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
	std::uniform_real_distribution<float> xy(-10, 10);

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
	std::uniform_real_distribution<float> xy(-10, 10);

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

