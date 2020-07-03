#include "gtest/gtest.h"
#include "api/mock_led.h"
#include "pixled.h"

using ::testing::Return;

TEST(OutputFormat, RGB) {
	pixled::RGB rgb;
	MockColor color;
	EXPECT_CALL(color, red)
		.WillRepeatedly(Return(24));
	EXPECT_CALL(color, green)
		.WillRepeatedly(Return(72));
	EXPECT_CALL(color, blue)
		.WillRepeatedly(Return(238));

	uint8_t buffer[30];

	rgb.write(color, &buffer[9]);

	ASSERT_EQ(buffer[9], 24);
	ASSERT_EQ(buffer[9+1], 72);
	ASSERT_EQ(buffer[9+2], 238);
}

TEST(OutputFormat, GBR) {
	pixled::GBR rgb;
	MockColor color;
	EXPECT_CALL(color, red)
		.WillRepeatedly(Return(24));
	EXPECT_CALL(color, green)
		.WillRepeatedly(Return(72));
	EXPECT_CALL(color, blue)
		.WillRepeatedly(Return(238));

	uint8_t buffer[30];

	rgb.write(color, &buffer[9]);

	ASSERT_EQ(buffer[9], 72);
	ASSERT_EQ(buffer[9+1], 238);
	ASSERT_EQ(buffer[9+2], 24);
}

TEST(OutputFormat, RGBW) {
	pixled::RGBW rgbw;
	MockColor color;
	EXPECT_CALL(color, red)
		.WillRepeatedly(Return(24));
	EXPECT_CALL(color, green)
		.WillRepeatedly(Return(72));
	EXPECT_CALL(color, blue)
		.WillRepeatedly(Return(238));

	uint8_t buffer[40];

	rgbw.write(color, &buffer[8]);

	ASSERT_EQ(buffer[8], 24);
	ASSERT_EQ(buffer[8+1], 72);
	ASSERT_EQ(buffer[8+2], 238);
	ASSERT_EQ(buffer[8+3], 0);

}
/*
 *TEST(rgb, fields) {
 *    base::rgb rgb(234, 28, 128);
 *
 *    ASSERT_EQ(rgb[R], 234);
 *    ASSERT_EQ(rgb[G], 28);
 *    ASSERT_EQ(rgb[B], 128);
 *}
 *
 *TEST(RgbArray, assign_rgb) {
 *    RgbArray<4> rgbArray;
 *
 *    rgbArray[2] = base::rgb(12, 255, 4);
 *
 *    ASSERT_EQ(rgbArray[2][R], 12);
 *    ASSERT_EQ(rgbArray[2][G], 255);
 *    ASSERT_EQ(rgbArray[2][B], 4);
 *}
 */
