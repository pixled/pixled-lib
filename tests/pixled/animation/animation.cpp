#include "pixled/animation/animation.h"
#include "pixled/chroma/chroma.h"
#include "../../mocks/mock_function.h"

#include <random>

using namespace testing;

TEST(RainbowTest, test) {
	pixled::Constant<pixled::time> period(12);

	pixled::animation::Rainbow h {period};
	auto r = pixled::chroma::hsb(h, 0.5f, 0.4f);

	auto color = r({0, 0}, 0);
	ASSERT_FLOAT_EQ(color.hue(), 180.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.brightness(), 0.4f);

	color = r({2, 8}, 12);
	ASSERT_FLOAT_EQ(color.hue(), 180.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.brightness(), 0.4f);

	color = r({2, 8}, 6);
	ASSERT_FLOAT_EQ(color.hue(), 180.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.brightness(), 0.4f);

	color = r({2, 8}, 3);
	ASSERT_FLOAT_EQ(color.hue(), 360.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.brightness(), 0.4f);

	color = r({2, 8}, 9);
	ASSERT_FLOAT_EQ(color.hue(), 0.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.brightness(), 0.4f);
}

class SequenceTest : public ::testing::Test {
	protected:
		NiceMock<pixled::MockFunction<pixled::color>> f1;
		NiceMock<pixled::MockFunction<pixled::color>> f2;
		NiceMock<pixled::MockFunction<pixled::color>> f3;
		std::vector<std::pair<pixled::FctWrapper<pixled::color>, pixled::time>> anims;

		// Sequence constructor initialization
		pixled::animation::Sequence seq {
			{
				// A temporary anim
				{std::move(f1), 10},
				// A reference
				{f2, 5}
			}
		};
		pixled::point fake_point {8, 3};

		void SetUp() override {
			// Add items using the add function
			seq.add(f3, 13);
		}
};

TEST_F(SequenceTest, sequence_test) {
	for(pixled::time T = 0; T < 10; T++) {
		for(pixled::time t = T*28; t < T*28 + 10; t++) {
			EXPECT_CALL(*f1.last_copy, call(fake_point, t));
			seq(fake_point, t);
		}
		for(pixled::time t = T*28 + 10; t < T*28 + 15; t++) {
			EXPECT_CALL(*f2.last_copy, call(fake_point, t));
			seq(fake_point, t);
		}
		for(pixled::time t = T*28 + 15; t < (T+1)*28; t++) {
			EXPECT_CALL(*f3.last_copy, call(fake_point, t));
			seq(fake_point, t);
		}
	}
}

TEST_F(SequenceTest, copy_test) {
	pixled::FctWrapper<pixled::color> copy(seq); 

	ASSERT_THAT(&*copy, WhenDynamicCastTo<const pixled::animation::Sequence*>(Not(IsNull())));

	for(pixled::time T = 0; T < 10; T++) {
		for(pixled::time t = T*28; t < T*28 + 10; t++) {
			EXPECT_CALL(*f1.last_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
		for(pixled::time t = T*28 + 10; t < T*28 + 15; t++) {
			EXPECT_CALL(*f2.last_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
		for(pixled::time t = T*28 + 15; t < (T+1)*28; t++) {
			EXPECT_CALL(*f3.last_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
	}
}

TEST(BlinkTest, test) {
	std::mt19937 rd;
	std::uniform_int_distribution<uint8_t> rd_color;

	NiceMock<pixled::MockFunction<pixled::color>> anim;

	pixled::point p(6, -4);
	pixled::animation::Blink blink(anim, 12);

	for(pixled::time T = 0; T < 10; T++) {
		for(pixled::time t = 12*T + 1; t < 12*T + 6; t++) {
			pixled::color c;
			c.setRgb(rd_color(rd), rd_color(rd), rd_color(rd));

			EXPECT_CALL(*anim.last_copy, call(p, t))
				.WillOnce(Return(c));
			ASSERT_EQ(blink(p, t), c);
		}

		pixled::color black;
		black.setRgb(0, 0, 0);
		for(pixled::time t = 12*T + 7; t < 12*T + 12; t++) {
			ASSERT_EQ(blink(p, t), black);
		}
	}
}
