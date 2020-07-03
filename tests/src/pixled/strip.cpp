#include "api/mock_led.h"
#include "api/mock_output.h"

#include "pixled/led.h"
#include "pixled.h"

#include <cstdint>
#include <random>

using ::testing::_;
using ::testing::ByRef;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::TypedEq;

TEST(Strip, toArray) {
	pixled::Strip strip {10};
	uint8_t fake_colors[10][3];

	std::mt19937 gen;
	std::uniform_int_distribution<uint8_t> dist (0, 200);

	for(int i = 0; i < 10; i++) {
        fake_colors[i][0] = dist(gen);
        fake_colors[i][1] = dist(gen);
        fake_colors[i][2] = dist(gen);
		strip[i].color().setRgb(fake_colors[i][0], fake_colors[i][1], fake_colors[i][2]);
	}

	uint8_t rgbArray[30];
	MockOutputFormat format;
	for(int i = 0; i < 10; i++) {
		EXPECT_CALL(format, write(TypedEq<const pixled::api::Color&>(ByRef(strip[i].color())), &rgbArray[3*i]));
	}
	strip.toArray(format, rgbArray);
}
