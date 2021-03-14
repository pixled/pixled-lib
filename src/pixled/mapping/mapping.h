#ifndef PIXLED_MAPPING_H
#define PIXLED_MAPPING_H

#include "../geometry.h"
#include <unordered_map>
#include <vector>

namespace pixled { 
	class Mapping {
		public:
			typedef std::vector<std::pair<point, std::size_t>>::const_iterator map_iterator;
			virtual map_iterator begin() const = 0;
			virtual map_iterator end() const = 0;
			virtual const std::vector<std::pair<point, std::size_t>>& leds() const = 0;
	};

	namespace mapping {
		std::ostream& operator<<(std::ostream& o, const Mapping& m);

		class TurtleMapping : public Mapping {
			private:
				std::vector<std::pair<point, std::size_t>> _leds;

				point turtle_position {0, 0};
				angle turtle_orientation = 0.;
				std::size_t current_led_index = 0;
				void moveTo(point p, std::size_t num_led);

			public:
				using typename Mapping::map_iterator;
				map_iterator begin() const override;
				map_iterator end() const override;
				const std::vector<std::pair<point, std::size_t>>& leds() const override;

				point position() const;
				angle orientation() const;
				std::size_t ledIndex() const;

				void forward(coordinate distance, std::size_t num_led = 0);
				void turnLeft(angle angle);
				void turnRight(angle angle);
				void jump(point p);
		};

		class StripMapping : public TurtleMapping {
			private:
				std::vector<point> coordinates;
			public:
				StripMapping(std::size_t num_led);
		};

		enum PANEL_LINKING {
			LEFT_RIGHT_LEFT_RIGHT_FROM_BOTTOM,
			LEFT_RIGHT_RIGHT_LEFT_FROM_BOTTOM,
			RIGHT_LEFT_RIGHT_LEFT_FROM_BOTTOM,
			RIGHT_LEFT_LEFT_RIGHT_FROM_BOTTOM,
			LEFT_RIGHT_LEFT_RIGHT_FROM_TOP,
			LEFT_RIGHT_RIGHT_LEFT_FROM_TOP,
			RIGHT_LEFT_RIGHT_LEFT_FROM_TOP,
			RIGHT_LEFT_LEFT_RIGHT_FROM_TOP,
			TOP_DOWN_TOP_DOWN_FROM_LEFT,
			TOP_DOWN_DOWN_TOP_FROM_LEFT,
			DOWN_TOP_DOWN_TOP_FROM_LEFT,
			DOWN_TOP_TOP_DOWN_FROM_LEFT,
			TOP_DOWN_TOP_DOWN_FROM_RIGHT,
			TOP_DOWN_DOWN_TOP_FROM_RIGHT,
			DOWN_TOP_DOWN_TOP_FROM_RIGHT,
			DOWN_TOP_TOP_DOWN_FROM_RIGHT
		};

		class LedPanel : public TurtleMapping {
			private:
				std::size_t _width;
				std::size_t _height;

				void drawLeftRightLeftRightFromBottom(std::size_t width, std::size_t height);
				void drawRightLeftRightLeftFromBottom(std::size_t width, std::size_t height);
				void drawHorizontalSnakeFromBottom(std::size_t width, std::size_t height);

				void drawLeftRightLeftRightFromTop(std::size_t width, std::size_t height);
				void drawRightLeftRightLeftFromTop(std::size_t width, std::size_t height);
				void drawHorizontalSnakeFromTop(std::size_t width, std::size_t height);

				void drawTopDownTopDownFromLeft(std::size_t width, std::size_t height);
				void drawDownTopDownTopFromLeft(std::size_t width, std::size_t height);
				void drawVerticalSnakeFromLeft(std::size_t width, std::size_t height);

				void drawTopDownTopDownFromRight(std::size_t width, std::size_t height);
				void drawDownTopDownTopFromRight(std::size_t width, std::size_t height);
				void drawVerticalSnakeFromRight(std::size_t width, std::size_t height);
			public:
				LedPanel(std::size_t width, std::size_t height, PANEL_LINKING linking);

				std::size_t width() const {return _width;}
				std::size_t height() const {return _height;}
		};
	}
}
#endif
