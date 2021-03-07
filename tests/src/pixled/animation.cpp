#include <pixled.h>
#include "api/mock_pixel.h"
#include "api/mock_functionnal.h"

using namespace testing;

using pixled::Time;

TEST(RainbowTest, test) {
	pixled::Constant<Time> period(12);

	pixled::Rainbow h {period};
	auto r = pixled::hsb(h, 0.5f, 0.4f);

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
		NiceMock<pixled::MockFunction<pixled::Color>> f1;
		NiceMock<pixled::MockFunction<pixled::Color>> f2;
		NiceMock<pixled::MockFunction<pixled::Color>> f3;

		pixled::Sequence seq;
		pixled::Point fake_point {8, 3};

		void SetUp() override {
			seq.add(f1, 10);
			seq.add(f2, 5);
			seq.add(f3, 13);
		}
};

TEST_F(SequenceTest, sequence_test) {
	for(Time T = 0; T < 10; T++) {
		for(Time t = T*28; t < T*28 + 10; t++) {
			EXPECT_CALL(*f1.last_copy, call(fake_point, t));
			seq(fake_point, t);
		}
		for(Time t = T*28 + 10; t < T*28 + 15; t++) {
			EXPECT_CALL(*f2.last_copy, call(fake_point, t));
			seq(fake_point, t);
		}
		for(Time t = T*28 + 15; t < (T+1)*28; t++) {
			EXPECT_CALL(*f3.last_copy, call(fake_point, t));
			seq(fake_point, t);
		}
	}
}

TEST_F(SequenceTest, copy_test) {
	pixled::FctWrapper<pixled::Color> copy(seq); 

	ASSERT_THAT(&*copy, WhenDynamicCastTo<const pixled::Sequence*>(Not(IsNull())));

	for(Time T = 0; T < 10; T++) {
		for(Time t = T*28; t < T*28 + 10; t++) {
			EXPECT_CALL(*f1.last_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
		for(Time t = T*28 + 10; t < T*28 + 15; t++) {
			EXPECT_CALL(*f2.last_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
		for(Time t = T*28 + 15; t < (T+1)*28; t++) {
			EXPECT_CALL(*f3.last_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
	}
}

TEST(BlinkTest, test) {
	std::mt19937 rd;
	std::uniform_int_distribution<uint8_t> rd_color;

	NiceMock<pixled::MockFunction<pixled::Color>> anim;

	pixled::Point p(6, -4);
	pixled::Blink blink(anim, 12);

	for(Time T = 0; T < 10; T++) {
		for(Time t = 12*T + 1; t < 12*T + 6; t++) {
			pixled::Color c;
			c.setRgb(rd_color(rd), rd_color(rd), rd_color(rd));

			EXPECT_CALL(*anim.last_copy, call(p, t))
				.WillOnce(Return(c));
			ASSERT_EQ(blink(p, t), c);
		}

		pixled::Color black;
		black.setRgb(0, 0, 0);
		for(Time t = 12*T + 7; t < 12*T + 12; t++) {
			ASSERT_EQ(blink(p, t), black);
		}
	}
}
