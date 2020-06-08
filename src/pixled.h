#include "pixled/animation.h"
#include "pixled/led.h"
#include "pixled/output.h"

using Strip = base::Strip<base::Led<base::Color>>;

using AnimationRuntime = base::AnimationRuntime<base::Color, Strip>;
