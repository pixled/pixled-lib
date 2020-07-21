#include "mapping.h"
#include "api/utils.h"

#include <map>
#include <limits>

namespace pixled {
	std::ostream& operator<<(std::ostream& o, const api::Mapping& m) {
		std::map<long, std::map<long, std::size_t>> leds;
		long min_x = std::numeric_limits<long>::max();
		for(auto led : m) {
			if(std::lround(led.first.x) < min_x)
				min_x = std::lround(led.first.x);
			leds[std::lround(led.first.y)][std::lround(led.first.x)]=led.second;
		}
		if(leds.size() > 0) {
			auto line = leds.rbegin();
			long y = line->first;
			long prev_y = line->first;
			while(line!=leds.rend()) {
				for(auto blank = prev_y+1; blank < y; blank++)
					o << std::endl;

				auto column = line->second.begin();
				long x = column->first;
				long prev_x = min_x-1;
				while(column!=line->second.end()) {
					long current_cell = prev_x;
					bool first = true;
					if(prev_x == min_x-1 && x != min_x)
						first = false;
					while(current_cell+1 < x) {
						if(first) {
							o << "|   ";
							first = false;
						}
						else {
							o << "    ";
						}
						current_cell++;
					}

					//for(auto blank = prev_x+1; blank <= x; blank++)
						//o << "    ";
					std::string index = std::to_string(column->second);
					//std::string index = std::to_string(x);
					o << "|" << index;
					if(index.length() ==  1)
						o << "  ";
					else if (index.length() == 2)
						o << " ";
					prev_x = x;
					column++;
					x = std::lround(column->first);
				}

				o<< "|" << std::endl;
				prev_y = y;
				line++;
				y=line->first;
			}
		} else {
			std::cout << "<empty>" << std::endl;
		}
		return o;
	}

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
			api::Point led_p1 {
				turtle_position.x + i * (p.x - turtle_position.x) / (num_led),
				turtle_position.y + i * (p.y - turtle_position.y) / (num_led)
			};
			api::Point led_p2 {
				turtle_position.x + (i+1) * (p.x - turtle_position.x) / (num_led),
				turtle_position.y + (i+1) * (p.y - turtle_position.y) / (num_led)
			};
			api::Point led_point {
				led_p1.x + (led_p2.x - led_p1.x) / 2,
				led_p1.y + (led_p2.y - led_p1.y) / 2
			};
			_leds.push_back({led_point, current_led_index++});
		}
		turtle_position = p;
	}

	void TurtleMapping::jump(api::Point p) {
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

	LedPanel::LedPanel(std::size_t width, std::size_t height, PANEL_LINKING linking) {
		switch(linking) {
			case LEFT_RIGHT_LEFT_RIGHT:
				drawLeftRightLeftRight(width, height);
				break;
			case LEFT_RIGHT_RIGHT_LEFT:
				drawHorizontalSnake(width, height);
				//drawLeftRightRightLeft(width, height);
				break;
			case RIGHT_LEFT_RIGHT_LEFT:
				drawRightLeftRightLeft(width, height);
				break;
			case RIGHT_LEFT_LEFT_RIGHT:
				forward(width);
				turnLeft(180);
				drawHorizontalSnake(width, height);
				break;
			default:
				break;
		}
	}

	void LedPanel::drawLeftRightLeftRight(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		for(std::size_t h = 0; h < height; h++) {
			jump(api::Point(0, h));
			forward(width, width);
		}
	}
	
	void LedPanel::drawRightLeftRightLeft(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnLeft(180);
		for(std::size_t h = 0; h < height; h++) {
			jump(api::Point(width, h));
			forward(width, width);
		}
	}
	void LedPanel::drawHorizontalSnake(std::size_t width, std::size_t height) {
		bool left_to_right = false;
		if(api::Cos(orientation()) > 0)
			left_to_right = true;
		// init in (0, 0), angle = 0
		for(std::size_t h = 0; h < height; h++) {
			forward(width, width);
			if(left_to_right) {
				turnLeft(180);
				jump(api::Point(width, h+1));
			}
			else {
				turnRight(180);
				jump(api::Point(0, h+1));
			}
			left_to_right = !left_to_right;
		}
	}
}
