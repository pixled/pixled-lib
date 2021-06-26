#include "mapping.h"

#include <map>
#include <limits>

namespace pixled { namespace mapping {
	std::ostream& operator<<(std::ostream& o, const Mapping& m) {
		std::map<long, std::map<long, index_t>> leds;
		long min_x = std::numeric_limits<long>::max();
		for(auto led : m.leds()) {
			if(std::lround(led.location.x) < min_x)
				min_x = std::lround(led.location.x);
			leds[std::lround(led.location.y)][std::lround(led.location.x)]=led.index;
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

	void TurtleMapping::moveTo(point p, index_t num_led) {
		for(index_t i = 0; i < num_led; i++) {
			point led_p1 {
				turtle_position.x + i * (p.x - turtle_position.x) / (num_led),
				turtle_position.y + i * (p.y - turtle_position.y) / (num_led)
			};
			point led_p2 {
				turtle_position.x + (i+1) * (p.x - turtle_position.x) / (num_led),
				turtle_position.y + (i+1) * (p.y - turtle_position.y) / (num_led)
			};
			point led_point {
				led_p1.x + (led_p2.x - led_p1.x) / 2,
				led_p1.y + (led_p2.y - led_p1.y) / 2
			};
			this->push({led_point, current_led_index++});
		}
		turtle_position = p;
	}

	void TurtleMapping::jump(point p) {
		turtle_position = p;
	}

	point TurtleMapping::position() const {
		return turtle_position;
	}

	angle TurtleMapping::orientation() const {
		return turtle_orientation;
	}

	index_t TurtleMapping::ledIndex() const {
		return current_led_index;
	}

	void TurtleMapping::forward(coordinate distance, index_t num_led) {
		moveTo({
			turtle_position.x + distance * std::cos(turtle_orientation.toRad()),
			turtle_position.y + distance * std::sin(turtle_orientation.toRad())
			}, num_led);
	}

	void TurtleMapping::turnLeft(angle angle) {
		turtle_orientation += angle;
	}

	void TurtleMapping::turnRight(angle angle) {
		turtle_orientation -= angle;
	}

	LedStrip::LedStrip(index_t length) : length(length) {
		forward(length, length);
	}

	LedPanel::LedPanel(index_t width, index_t height, PANEL_LINKING linking)
		: _width(width), _height(height) {
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
				turnLeft(angle::fromDeg(180));
				drawHorizontalSnakeFromBottom(width, height);
				break;
			case TOP_DOWN_TOP_DOWN_FROM_LEFT:
				drawTopDownTopDownFromLeft(width, height);
				break;
			case DOWN_TOP_DOWN_TOP_FROM_LEFT:
				drawDownTopDownTopFromLeft(width, height);
				break;
			case TOP_DOWN_DOWN_TOP_FROM_LEFT:
				jump(point(0, height));
				turnRight(angle::fromDeg(90));
				drawVerticalSnakeFromLeft(width, height);
				break;
			case DOWN_TOP_TOP_DOWN_FROM_LEFT:
				turnLeft(angle::fromDeg(90));
				drawVerticalSnakeFromLeft(width, height);
				break;
			case LEFT_RIGHT_LEFT_RIGHT_FROM_TOP:
				drawLeftRightLeftRightFromTop(width, height);
				break;
			case RIGHT_LEFT_RIGHT_LEFT_FROM_TOP:
				drawRightLeftRightLeftFromTop(width, height);
				break;
			case LEFT_RIGHT_RIGHT_LEFT_FROM_TOP:
				jump(point(0, height-1));
				drawHorizontalSnakeFromTop(width, height);
				break;
			case RIGHT_LEFT_LEFT_RIGHT_FROM_TOP:
				jump(point(width, height-1));
				turnLeft(angle::fromDeg(180));
				drawHorizontalSnakeFromTop(width, height);
				break;
			case TOP_DOWN_TOP_DOWN_FROM_RIGHT:
				drawTopDownTopDownFromRight(width, height);
				break;
			case DOWN_TOP_DOWN_TOP_FROM_RIGHT:
				drawDownTopDownTopFromRight(width, height);
				break;
			case TOP_DOWN_DOWN_TOP_FROM_RIGHT:
				jump(point(width-1, height));
				turnRight(angle::fromDeg(90));
				drawVerticalSnakeFromRight(width, height);
				break;
			case DOWN_TOP_TOP_DOWN_FROM_RIGHT:
				jump(point(width-1, 0));
				turnLeft(angle::fromDeg(90));
				drawVerticalSnakeFromRight(width, height);
				break;
		}
	}

	void LedPanel::drawLeftRightLeftRightFromBottom(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		for(index_t h = 0; h < height; h++) {
			jump(point(0, h));
			forward(width, width);
		}
	}
	
	void LedPanel::drawRightLeftRightLeftFromBottom(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		turnLeft(angle::fromDeg(180));
		for(index_t h = 0; h < height; h++) {
			jump(point(width, h));
			forward(width, width);
		}
	}

	void LedPanel::drawLeftRightLeftRightFromTop(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		for(index_t h = 1; h <= height; h++) {
			jump(point(0, height-h));
			forward(width, width);
		}
	}
	
	void LedPanel::drawRightLeftRightLeftFromTop(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		turnLeft(angle::fromDeg(180));
		for(index_t h = 1; h <= height; h++) {
			jump(point(width, height-h));
			forward(width, width);
		}
	}

	void LedPanel::drawHorizontalSnakeFromBottom(index_t width, index_t height) {
		bool left_to_right = false;
		if(cos(orientation()) > 0)
			left_to_right = true;
		// init in (0, 0), angle = 0
		for(index_t h = 0; h < height; h++) {
			forward(width, width);
			if(left_to_right) {
				turnLeft(angle::fromDeg(180));
				jump(point(width, h+1));
			}
			else {
				turnRight(angle::fromDeg(180));
				jump(point(0, h+1));
			}
			left_to_right = !left_to_right;
		}
	}

	void LedPanel::drawHorizontalSnakeFromTop(index_t width, index_t height) {
		bool left_to_right = false;
		if(cos(orientation()) > 0)
			left_to_right = true;
		// init in (0, 0), angle = 0
		for(index_t h = 1; h <= height; h++) {
			forward(width, width);
			if(left_to_right) {
				turnLeft(angle::fromDeg(180));
				jump(point(width, height-1-h));
			}
			else {
				turnRight(angle::fromDeg(180));
				jump(point(0, height-1-h));
			}
			left_to_right = !left_to_right;
		}
	}

	void LedPanel::drawTopDownTopDownFromLeft(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		turnRight(angle::fromDeg(90));
		for(index_t w = 0; w < width; w++) {
			jump(point(w, height));
			forward(height, height);
		}
	}
	
	void LedPanel::drawDownTopDownTopFromLeft(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		turnLeft(angle::fromDeg(90));
		for(index_t w = 0; w < width; w++) {
			jump(point(w, 0));
			forward(height, height);
		}
	}
	void LedPanel::drawVerticalSnakeFromLeft(index_t width, index_t height) {
		bool down_to_top = false;
		if(sin(orientation()) > 0)
			down_to_top = true;
		// init in (0, 0), angle = 0
		for(index_t w = 0; w < width; w++) {
			forward(height, height);
			if(down_to_top) {
				turnLeft(angle::fromDeg(180));
				jump(point(w+1, height));
			}
			else {
				turnRight(angle::fromDeg(180));
				jump(point(w+1, 0));
			}
			down_to_top = !down_to_top;
		}
	}

	void LedPanel::drawTopDownTopDownFromRight(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		turnRight(angle::fromDeg(90));
		for(index_t w = 1; w <= width; w++) {
			jump(point(width-w, height));
			forward(height, height);
		}
	}
	
	void LedPanel::drawDownTopDownTopFromRight(index_t width, index_t height) {
		// init in (0, 0), angle = 0
		turnLeft(angle::fromDeg(90));
		for(index_t w = 1; w <= width; w++) {
			jump(point(width-w, 0));
			forward(height, height);
		}
	}
	void LedPanel::drawVerticalSnakeFromRight(index_t width, index_t height) {
		bool down_to_top = false;
		if(sin(orientation()) > 0)
			down_to_top = true;
		// init in (0, 0), angle = 0
		for(index_t w = 1; w <= width; w++) {
			forward(height, height);
			if(down_to_top) {
				turnLeft(angle::fromDeg(180));
				jump(point(width-w-1, height));
			}
			else {
				turnRight(angle::fromDeg(180));
				jump(point(width-w-1, 0));
			}
			down_to_top = !down_to_top;
		}
	}
}}
