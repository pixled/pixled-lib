#include "mapping.h"
#include "api/utils.h"

#include <map>
#include <limits>

namespace pixled {
	std::ostream& operator<<(std::ostream& o, const Mapping& m) {
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
	const std::vector<std::pair<Point, std::size_t>>& TurtleMapping::leds() const {
		return _leds;
	}

	void TurtleMapping::moveTo(Point p, std::size_t num_led) {
		for(std::size_t i = 0; i < num_led; i++) {
			Point led_p1 {
				turtle_position.x + i * (p.x - turtle_position.x) / (num_led),
				turtle_position.y + i * (p.y - turtle_position.y) / (num_led)
			};
			Point led_p2 {
				turtle_position.x + (i+1) * (p.x - turtle_position.x) / (num_led),
				turtle_position.y + (i+1) * (p.y - turtle_position.y) / (num_led)
			};
			Point led_point {
				led_p1.x + (led_p2.x - led_p1.x) / 2,
				led_p1.y + (led_p2.y - led_p1.y) / 2
			};
			_leds.push_back({led_point, current_led_index++});
		}
		turtle_position = p;
	}

	void TurtleMapping::jump(Point p) {
		turtle_position = p;
	}

	Point TurtleMapping::position() const {
		return turtle_position;
	}

	Angle TurtleMapping::orientation() const {
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

	void TurtleMapping::turnLeft(Angle angle) {
		turtle_orientation += angle;
	}

	void TurtleMapping::turnRight(Angle angle) {
		turtle_orientation -= angle;
	}

	StripMapping::StripMapping(std::size_t num_led) {
		forward(num_led, num_led);
	}

	LedPanel::LedPanel(std::size_t width, std::size_t height, PANEL_LINKING linking) {
		switch(linking) {
			case LEFT_RIGHT_LEFT_RIGHT_FROM_BOTTOM:
				drawLeftRightLeftRightFromBottom(width, height);
				break;
			case RIGHT_LEFT_RIGHT_LEFT_FROM_BOTTOM:
				drawRightLeftRightLeftFromBottom(width, height);
				break;
			case LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM:
				drawHorizontalSnakeFromBottom(width, height);
				break;
			case RIGHT_LEFT_LEFT_RIGHT_FROM_BOTTOM:
				forward(width);
				turnLeft(180);
				drawHorizontalSnakeFromBottom(width, height);
				break;
			case TOP_DOWN_TOP_DOWN_FROM_LEFT:
				drawTopDownTopDownFromLeft(width, height);
				break;
			case DOWN_TOP_DOWN_TOP_FROM_LEFT:
				drawDownTopDownTopFromLeft(width, height);
				break;
			case TOP_DOWN_DOWN_TOP_FROM_LEFT:
				jump(Point(0, height));
				turnRight(90);
				drawVerticalSnakeFromLeft(width, height);
				break;
			case DOWN_TOP_TOP_DOWN_FROM_LEFT:
				turnLeft(90);
				drawVerticalSnakeFromLeft(width, height);
				break;
			case LEFT_RIGHT_LEFT_RIGHT_FROM_TOP:
				drawLeftRightLeftRightFromTop(width, height);
				break;
			case RIGHT_LEFT_RIGHT_LEFT_FROM_TOP:
				drawRightLeftRightLeftFromTop(width, height);
				break;
			case LEFT_RIGHT_RIGHT_LEFT_FROM_TOP:
				jump(Point(0, height-1));
				drawHorizontalSnakeFromTop(width, height);
				break;
			case RIGHT_LEFT_LEFT_RIGHT_FROM_TOP:
				jump(Point(width, height-1));
				turnLeft(180);
				drawHorizontalSnakeFromTop(width, height);
				break;
			case TOP_DOWN_TOP_DOWN_FROM_RIGHT:
				drawTopDownTopDownFromRight(width, height);
				break;
			case DOWN_TOP_DOWN_TOP_FROM_RIGHT:
				drawDownTopDownTopFromRight(width, height);
				break;
			case TOP_DOWN_DOWN_TOP_FROM_RIGHT:
				jump(Point(width-1, height));
				turnRight(90);
				drawVerticalSnakeFromRight(width, height);
				break;
			case DOWN_TOP_TOP_DOWN_FROM_RIGHT:
				jump(Point(width-1, 0));
				turnLeft(90);
				drawVerticalSnakeFromRight(width, height);
				break;
		}
	}

	void LedPanel::drawLeftRightLeftRightFromBottom(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		for(std::size_t h = 0; h < height; h++) {
			jump(Point(0, h));
			forward(width, width);
		}
	}
	
	void LedPanel::drawRightLeftRightLeftFromBottom(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnLeft(180);
		for(std::size_t h = 0; h < height; h++) {
			jump(Point(width, h));
			forward(width, width);
		}
	}

	void LedPanel::drawLeftRightLeftRightFromTop(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		for(std::size_t h = 1; h <= height; h++) {
			jump(Point(0, height-h));
			forward(width, width);
		}
	}
	
	void LedPanel::drawRightLeftRightLeftFromTop(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnLeft(180);
		for(std::size_t h = 1; h <= height; h++) {
			jump(Point(width, height-h));
			forward(width, width);
		}
	}

	void LedPanel::drawHorizontalSnakeFromBottom(std::size_t width, std::size_t height) {
		bool left_to_right = false;
		if(Cos(orientation()) > 0)
			left_to_right = true;
		// init in (0, 0), angle = 0
		for(std::size_t h = 0; h < height; h++) {
			forward(width, width);
			if(left_to_right) {
				turnLeft(180);
				jump(Point(width, h+1));
			}
			else {
				turnRight(180);
				jump(Point(0, h+1));
			}
			left_to_right = !left_to_right;
		}
	}

	void LedPanel::drawHorizontalSnakeFromTop(std::size_t width, std::size_t height) {
		bool left_to_right = false;
		if(Cos(orientation()) > 0)
			left_to_right = true;
		// init in (0, 0), angle = 0
		for(std::size_t h = 1; h <= height; h++) {
			forward(width, width);
			if(left_to_right) {
				turnLeft(180);
				jump(Point(width, height-1-h));
			}
			else {
				turnRight(180);
				jump(Point(0, height-1-h));
			}
			left_to_right = !left_to_right;
		}
	}

	void LedPanel::drawTopDownTopDownFromLeft(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnRight(90);
		for(std::size_t w = 0; w < width; w++) {
			jump(Point(w, height));
			forward(height, height);
		}
	}
	
	void LedPanel::drawDownTopDownTopFromLeft(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnLeft(90);
		for(std::size_t w = 0; w < width; w++) {
			jump(Point(w, 0));
			forward(height, height);
		}
	}
	void LedPanel::drawVerticalSnakeFromLeft(std::size_t width, std::size_t height) {
		bool down_to_top = false;
		if(Sin(orientation()) > 0)
			down_to_top = true;
		// init in (0, 0), angle = 0
		for(std::size_t w = 0; w < width; w++) {
			forward(height, height);
			if(down_to_top) {
				turnLeft(180);
				jump(Point(w+1, height));
			}
			else {
				turnRight(180);
				jump(Point(w+1, 0));
			}
			down_to_top = !down_to_top;
		}
	}

	void LedPanel::drawTopDownTopDownFromRight(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnRight(90);
		for(std::size_t w = 1; w <= width; w++) {
			jump(Point(width-w, height));
			forward(height, height);
		}
	}
	
	void LedPanel::drawDownTopDownTopFromRight(std::size_t width, std::size_t height) {
		// init in (0, 0), angle = 0
		turnLeft(90);
		for(std::size_t w = 1; w <= width; w++) {
			jump(Point(width-w, 0));
			forward(height, height);
		}
	}
	void LedPanel::drawVerticalSnakeFromRight(std::size_t width, std::size_t height) {
		bool down_to_top = false;
		if(Sin(orientation()) > 0)
			down_to_top = true;
		// init in (0, 0), angle = 0
		for(std::size_t w = 1; w <= width; w++) {
			forward(height, height);
			if(down_to_top) {
				turnLeft(180);
				jump(Point(width-w-1, height));
			}
			else {
				turnRight(180);
				jump(Point(width-w-1, 0));
			}
			down_to_top = !down_to_top;
		}
	}

}
