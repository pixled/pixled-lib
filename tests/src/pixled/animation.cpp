#include <pixled.h>
#include "api/mock_pixel.h"
#include "api/mock_functionnal.h"

using ::testing::WhenDynamicCastTo;
using ::testing::Not;
using ::testing::IsNull;
using ::testing::AnyNumber;
using ::testing::AtMost;
using ::testing::Return;

using pixled::MockFunction;
using pixled::Time;
using pixled::MockFctCopy;

TEST(RainbowTest, test) {
	MockFunction<Time>* last_copy;
	MockFunction<Time> period;
	EXPECT_CALL(period, copy).Times(AtMost(1))
		.WillRepeatedly(Invoke(MockFctCopy<MockFunction<Time>>(last_copy)));

	pixled::Rainbow h {period};
	auto r = pixled::hsb(h, 0.5f, 0.4f);

	EXPECT_CALL(*last_copy, call)
		.Times(AnyNumber())
		.WillRepeatedly(Return(12));
	auto color = r({0, 0}, 0);
	ASSERT_FLOAT_EQ(color.hue(), 180.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.value(), 0.4f);

	color = r({2, 8}, 12);
	ASSERT_FLOAT_EQ(color.hue(), 180.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.value(), 0.4f);

	color = r({2, 8}, 6);
	ASSERT_FLOAT_EQ(color.hue(), 180.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.value(), 0.4f);

	color = r({2, 8}, 3);
	ASSERT_FLOAT_EQ(color.hue(), 360.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.value(), 0.4f);

	color = r({2, 8}, 9);
	ASSERT_FLOAT_EQ(color.hue(), 0.f);
	ASSERT_FLOAT_EQ(color.saturation(), 0.5f);
	ASSERT_FLOAT_EQ(color.value(), 0.4f);
}

class SequenceTest : public ::testing::Test {
	protected:
		MockFunction<pixled::Color>* last_f1_copy;
		MockFunction<pixled::Color> f1;

		MockFunction<pixled::Color>* last_f2_copy;
		MockFunction<pixled::Color> f2;

		MockFunction<pixled::Color>* last_f3_copy;
		MockFunction<pixled::Color> f3;

		pixled::Sequence seq;
		pixled::api::Point fake_point {8, 3};

		void SetUp() override {
			EXPECT_CALL(f1, copy)
				.WillRepeatedly(Invoke(MockFctCopy<MockFunction<pixled::Color>>(last_f1_copy)));

			EXPECT_CALL(f2, copy)
				.WillRepeatedly(Invoke(MockFctCopy<MockFunction<pixled::Color>>(last_f2_copy)));

			EXPECT_CALL(f3, copy)
				.WillRepeatedly(Invoke(MockFctCopy<MockFunction<pixled::Color>>(last_f3_copy)));

			seq.add(f1, 10);
			seq.add(f2, 5);
			seq.add(f3, 13);
		}
};

TEST_F(SequenceTest, sequence_test) {
	for(Time T = 0; T < 10; T++) {
		for(Time t = T*28; t < T*28 + 10; t++) {
			EXPECT_CALL(*last_f1_copy, call(fake_point, t));
			seq(fake_point, t);
		}
		for(Time t = T*28 + 10; t < T*28 + 15; t++) {
			EXPECT_CALL(*last_f2_copy, call(fake_point, t));
			seq(fake_point, t);
		}
		for(Time t = T*28 + 15; t < (T+1)*28; t++) {
			EXPECT_CALL(*last_f3_copy, call(fake_point, t));
			seq(fake_point, t);
		}
	}
}

TEST_F(SequenceTest, copy_test) {
	pixled::api::FctWrapper<pixled::Color> copy(seq); 

	ASSERT_THAT(&*copy, WhenDynamicCastTo<const pixled::Sequence*>(Not(IsNull())));

	for(Time T = 0; T < 10; T++) {
		for(Time t = T*28; t < T*28 + 10; t++) {
			EXPECT_CALL(*last_f1_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
		for(Time t = T*28 + 10; t < T*28 + 15; t++) {
			EXPECT_CALL(*last_f2_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
		for(Time t = T*28 + 15; t < (T+1)*28; t++) {
			EXPECT_CALL(*last_f3_copy, call(fake_point, t));
			(*copy)(fake_point, t);
		}
	}
}
