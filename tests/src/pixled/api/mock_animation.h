#ifndef MOCK_ANIMATION_H
#define MOCK_ANIMATION_H
#include <pixled.h>
#include "gmock/gmock.h"
#include "pixled/api/pixel.h"

class MockAnimation : public pixled::api::Animation {
	public:
	MOCK_METHOD(void, compute, (pixled::api::Color&, int, int), (override));

};
#endif
