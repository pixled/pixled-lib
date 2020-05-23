#include "pixled/animation.h"
#include "pixled/led.h"
#include "pixled/output.h"

template<int length>
using RgbArray = base::RgbArray<length, base::rgb>;

template<int length>
using Strip = base::Strip<length, base::Led<base::Color>, base::RgbArray<length, base::rgb>>;

template<int length>
using Animation = base::Animation<RgbArray<length>, Strip<length>>;
