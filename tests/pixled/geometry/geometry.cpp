#include "pixled/geometry/geometry.h"
#include "gmock/gmock.h"

using namespace pixled::geometry;

TEST(X, test) {
	ASSERT_EQ(X()({{2, 4}, 3}, 18), 2);
}

TEST(Y, test) {
	ASSERT_EQ(Y()({{2, 4}, 3}, 18), 4);
}

TEST(I, test) {
	ASSERT_EQ(I()({{2, 4}, 3}, 18), 3);
}
