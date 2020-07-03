#ifndef MOCK_OUTPUT_H
#define MOCK_OUTPUT_H

#include "gmock/gmock.h"
#include <pixled.h>

class MockOutputFormat : public pixled::api::OutputFormat {
	public:
		MOCK_METHOD(void, write, (const pixled::api::Color&, uint8_t* const&), (override));

};

#endif
