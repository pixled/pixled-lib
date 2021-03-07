#include "pixled/geometry/geometry.h"
#include "pixled/arithmetic/arithmetic.h"

#include "../../mocks/mock_function.h"

#include <random>

using ::testing::Return;

using pixled::MockFunction;
using pixled::Point;
using pixled::Time;

class OperatorTest : public ::testing::Test {
	protected:
		Point c {12, 38};
		Time t {25};
};

class SinTest : public OperatorTest {};

TEST_F(SinTest, constant_sin) {
	float i = 2.7;
	pixled::geometry::Sin<float> sin {i};

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

	pixled::geometry::Sin<float> sin {product};
	for(int i = 0; i < 100; i++) {
		float f1_result = random_f(engine);
		float f2_result = random_f(engine);

		EXPECT_CALL(*f1_copy_copy, call(c, t)).WillOnce(Return(f1_result));
		EXPECT_CALL(*f2_copy_copy, call(c, t)).WillOnce(Return(f2_result));

		ASSERT_FLOAT_EQ(sin(c, t), std::sin(f1_result * f2_result));
	}
}

