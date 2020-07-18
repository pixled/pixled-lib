#include "mapping.h"
#include "api/utils.h"

namespace pixled {
	typename TurtleMapping::map_iterator TurtleMapping::begin() const {
		return _leds.begin();
	}
	typename TurtleMapping::map_iterator TurtleMapping::end() const {
		return _leds.end();
	}
	const std::vector<std::pair<api::Point, std::size_t>>& TurtleMapping::leds() const {
		return _leds;
	}

	void TurtleMapping::moveTo(api::Point p, std::size_t num_led) {
		for(std::size_t i = 0; i < num_led; i++) {
			api::Point led_point {
				turtle_position.x + i * (p.x - turtle_position.x) / (num_led-1),
				turtle_position.y + i * (p.y - turtle_position.y) / (num_led-1)
			};
			_leds.push_back({led_point, current_led_index++});
		}
		turtle_position = p;
	}

	api::Point TurtleMapping::position() const {
		return turtle_position;
	}

	api::Angle TurtleMapping::orientation() const {
		return turtle_orientation;
	}

	std::size_t TurtleMapping::ledIndex() const {
		return current_led_index;
	}

	void TurtleMapping::forward(Coordinate distance, std::size_t num_led) {
		moveTo({
			turtle_position.x + distance * std::cos(turtle_orientation.toRad()),
			turtle_position.y + distance * std::sin(turtle_orientation.toRad())
			}, num_led);
	}

	void TurtleMapping::turnLeft(api::Angle angle) {
		turtle_orientation += angle;
	}

	void TurtleMapping::turnRight(api::Angle angle) {
		turtle_orientation -= angle;
	}

	StripMapping::StripMapping(std::size_t num_led) {
		forward(num_led, num_led);
	}
/*
 *    StripMapping::StripMapping(std::size_t length) {
 *        for(std::size_t i = 0; i < length; i++) {
 *            coordinates.push_back(api::Point(i, 0));
 *        }
 *    }
 *
 *    std::size_t StripMapping::map(api::Point c) const {
 *        return c.x;
 *    }
 *
 *    typename StripMapping::coordinates_iterator StripMapping::begin() const {
 *        return coordinates.begin();
 *    }
 *
 *    typename StripMapping::coordinates_iterator StripMapping::end() const {
 *        return coordinates.end();
 *    }
 */
}
