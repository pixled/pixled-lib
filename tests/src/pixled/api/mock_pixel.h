#ifndef MOCK_LED_H
#define MOCK_LED_H

#include "gmock/gmock.h"
#include "pixled/api/pixel.h"
#include "pixled/pixel.h"

class MockColor : public pixled::Color {
	public:
		MOCK_METHOD(uint8_t, red, (), (const, override));
		MOCK_METHOD(uint8_t, green, (), (const, override));
		MOCK_METHOD(uint8_t, blue, (), (const, override));

		MOCK_METHOD(float, hue, (), (const, override));
		MOCK_METHOD(float, saturation, (), (const, override));
		MOCK_METHOD(float, value, (), (const, override));

		MOCK_METHOD(void, setRgb, (uint8_t, uint8_t, uint8_t), (override));
		MOCK_METHOD(void, setHsv, (float, float, float), (override));
};

class MockPixel : public pixled::Pixel {
	public:
	MOCK_METHOD(pixled::Color&, color, (), (override));
	MOCK_METHOD(const pixled::Color&, color, (), (const, override));

};
#endif
