#include "pixled/random/random.h"
#include "gmock/gmock.h"

#define NUM_PERIOD 50000

using ::testing::ElementsAreArray;
using ::testing::Not;

template<typename Container>
float mean(Container& data) {
	float mean = 0;
	for(auto i : data)
		mean += i;
	return mean / data.size();
}

template<typename Container>
float variance(Container& data) {
	std::vector<float> distances;
	float _mean = mean(data);
	for(auto d : data)
		distances.push_back(std::pow(d - _mean, 2));
	return mean(distances);
}


// For a given t, RandomT is supposed to yield a random value that is the same
// whatever the current point is.
TEST(RandomT, uniform_int_test) {
	pixled::random::RandomT engine (10);
	pixled::random::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 _rd;
	std::uniform_real_distribution<float> xy(-10, 10);
	std::uniform_int_distribution<pixled::index_t> index(0, 100);

	std::array<int, NUM_PERIOD> values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < NUM_PERIOD; i++) {
		pixled::point p {xy(_rd), xy(_rd)};
		pixled::led l {p, index(_rd)};
		int rd_int = rd(l, 10 * i);
		values[i] = rd_int;
		// Since period = 10, the value must keep constant for 10 iterations
		for(pixled::time t = 10 * i; t < 10 * (i + 1); t++) {
			int next_rd_int = rd(l, t);
			ASSERT_EQ(next_rd_int, rd_int);
		}
	}

	ASSERT_NEAR(mean(values), 12, 1);
	ASSERT_NEAR(variance(values), std::pow(24, 2) / 12, 5);

}

TEST(RandomT, uniform_float_test) {
	pixled::random::RandomT engine (10);
	pixled::random::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 _rd;
	std::uniform_real_distribution<float> xy(-10, 10);
	std::uniform_int_distribution<pixled::index_t> index(0, 100);

	std::array<float, NUM_PERIOD> values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < NUM_PERIOD; i++) {
		pixled::point p {xy(_rd), xy(_rd)};
		pixled::led l {p, index(_rd)};
		float rd_float = rd(l, 10 * i);
		values[i] = rd_float;
		// Since period = 10, the value must keep constant for 10 iterations
		for(pixled::time t = 10 * i; t < 10 * (i + 1); t++) {
			float next_rd_float = rd(l, t);
			ASSERT_FLOAT_EQ(next_rd_float, rd_float);
		}
	}

	ASSERT_NEAR(mean(values), 12, 1);
	ASSERT_NEAR(variance(values), std::pow(24, 2) / 12, 5);
}

TEST(RandomT, auto_seed) {
	auto random_1 = pixled::random::RandomT(1);
	auto random_2 = pixled::random::RandomT(1);

	auto dist_1 = pixled::random::UniformDistribution<int>(0, 255, random_1);
	auto dist_2 = pixled::random::UniformDistribution<int>(0, 255, random_2);

	std::array<int, 1000> values_1;
	std::array<int, 1000> values_2;

	for(int i = 0; i < 1000; i++) {
		values_1[i] = dist_1({{0, 0}, 0}, i);
		values_2[i] = dist_2({{0, 0}, 0}, i);
	}

	ASSERT_THAT(values_1, Not(ElementsAreArray(values_2)));
}

// For a given t, RandomXYT is supposed to yield independent random value sequences for each point.
TEST(RandomXYT, uniform_int_test) {
	pixled::random::RandomXYT engine (10);
	pixled::random::UniformDistribution<int> rd(1, 25, engine);
	std::mt19937 _rd;
	std::uniform_real_distribution<float> xy(-10, 10);
	std::uniform_int_distribution<pixled::index_t> index(0, 100);

	pixled::point p1 {xy(_rd), xy(_rd)};
	pixled::led l1 {p1, index(_rd)};
	pixled::point p2 {xy(_rd), xy(_rd)};
	pixled::led l2 {p2, index(_rd)};
	pixled::point p3 {xy(_rd), xy(_rd)};
	pixled::led l3 {p3, index(_rd)};
	std::array<int, NUM_PERIOD> p1_values;
	std::array<int, NUM_PERIOD> p2_values;
	std::array<int, NUM_PERIOD> p3_values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < NUM_PERIOD; i++) {
		// p1
		int rd_int_1 = rd(l1, 10 * i);
		p1_values[i] = rd_int_1;
		// p2
		int rd_int_2 = rd(l2, 10 * i);
		p2_values[i] = rd_int_2;
		// p3
		int rd_int_3 = rd(l3, 10 * i);
		p3_values[i] = rd_int_3;
		// Since period = 10, the value must keep constant for 10 iterations
		for(pixled::time t = 10 * i; t < 10 * (i + 1); t++) {
			// p1
			int next_rd_int_1 = rd(l1, t);
			ASSERT_EQ(next_rd_int_1, rd_int_1);
			// p2
			int next_rd_int_2 = rd(l2, t);
			ASSERT_EQ(next_rd_int_2, rd_int_2);
			// p3
			int next_rd_int_3 = rd(l3, t);
			ASSERT_EQ(next_rd_int_3, rd_int_3);
		}
	}

	ASSERT_NEAR(mean(p1_values), 12, 1);
	ASSERT_NEAR(variance(p1_values), std::pow(24, 2) / 12, 5);

	ASSERT_NEAR(mean(p2_values), 12, 1);
	ASSERT_NEAR(variance(p2_values), std::pow(24, 2) / 12, 5);

	ASSERT_NEAR(mean(p3_values), 12, 1);
	ASSERT_NEAR(variance(p3_values), std::pow(24, 2) / 12, 5);

	ASSERT_THAT(p1_values, Not(ElementsAreArray(p2_values)));
	ASSERT_THAT(p1_values, Not(ElementsAreArray(p3_values)));
	ASSERT_THAT(p2_values, Not(ElementsAreArray(p3_values)));
}

// For a given t, RandomXYT is supposed to yield independent random value sequences for each point.
TEST(RandomXYT, normal_float_test) {
	pixled::random::RandomXYT engine (10);
	pixled::random::NormalDistribution<float> rd(180, 100, engine);
	std::mt19937 _rd;
	std::uniform_real_distribution<float> xy(-10, 10);
	std::uniform_int_distribution<pixled::index_t> index(0, 100);

	pixled::point p1 {xy(_rd), xy(_rd)};
	pixled::led l1 {p1, index(_rd)};
	pixled::point p2 {xy(_rd), xy(_rd)};
	pixled::led l2 {p2, index(_rd)};
	pixled::point p3 {xy(_rd), xy(_rd)};
	pixled::led l3 {p3, index(_rd)};
	std::array<int, NUM_PERIOD> p1_values;
	std::array<int, NUM_PERIOD> p2_values;
	std::array<int, NUM_PERIOD> p3_values;

	// First run from t = 0 to t = 10 * 100
	for(unsigned long i = 0; i < NUM_PERIOD; i++) {
		// p1
		int rd_int_1 = rd(l1, 10 * i);
		p1_values[i] = rd_int_1;
		// p2
		int rd_int_2 = rd(l2, 10 * i);
		p2_values[i] = rd_int_2;
		// p3
		int rd_int_3 = rd(l3, 10 * i);
		p3_values[i] = rd_int_3;
		// Since period = 10, the value must keep constant for 10 iterations
		for(pixled::time t = 10 * i; t < 10 * (i + 1); t++) {
			// p1
			int next_rd_int_1 = rd(l1, t);
			ASSERT_EQ(next_rd_int_1, rd_int_1);
			// p2
			int next_rd_int_2 = rd(l2, t);
			ASSERT_EQ(next_rd_int_2, rd_int_2);
			// p3
			int next_rd_int_3 = rd(l3, t);
			ASSERT_EQ(next_rd_int_3, rd_int_3);
		}
	}

	ASSERT_NEAR(mean(p1_values), 180, 10);
	ASSERT_NEAR(variance(p1_values), std::pow(100, 2), 200);

	ASSERT_NEAR(mean(p2_values), 180, 10);
	ASSERT_NEAR(variance(p2_values), std::pow(100, 2), 200);

	ASSERT_NEAR(mean(p3_values), 180, 10);
	ASSERT_NEAR(variance(p3_values), std::pow(100, 2), 200);

	ASSERT_THAT(p1_values, Not(ElementsAreArray(p2_values)));
	ASSERT_THAT(p1_values, Not(ElementsAreArray(p3_values)));
	ASSERT_THAT(p2_values, Not(ElementsAreArray(p3_values)));
}

TEST(RandomXYT, auto_seed) {
	auto random_1 = pixled::random::RandomXYT(1);
	auto random_2 = pixled::random::RandomXYT(1);

	auto dist_1 = pixled::random::UniformDistribution<int>(0, 255, random_1);
	auto dist_2 = pixled::random::UniformDistribution<int>(0, 255, random_2);

	std::array<int, 1000> values_1;
	std::array<int, 1000> values_2;

	for(int i = 0; i < 1000; i++) {
		values_1[i] = dist_1({{0, 0}, 0}, i);
		values_2[i] = dist_2({{0, 0}, 0}, i);
	}

	ASSERT_THAT(values_1, Not(ElementsAreArray(values_2)));
}
