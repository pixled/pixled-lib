#ifndef MOCK_LED_H
#define MOCK_LED_H

#include "gmock/gmock.h"
#include "pixled/api/pixel.h"
#include "pixled/pixel.h"

class MockPixel : public pixled::Pixel {
	public:
	MOCK_METHOD(pixled::Color&, color, (), (override));
	MOCK_METHOD(const pixled::Color&, color, (), (const, override));

};
#endif
