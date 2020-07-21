#include "gtest/gtest.h"
#include <pixled.h>
#include "api/mock_pixel.h"
#include "api/mock_functionnal.h"

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
