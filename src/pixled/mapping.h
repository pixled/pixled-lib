#ifndef PIXLED_MAPPING_H
#define PIXLED_MAPPING_H

#include "api/geometry.h"
#include "api/mapping.h"
#include <unordered_map>

namespace pixled {

	std::ostream& operator<<(std::ostream& o, const api::Mapping& m);

	class TurtleMapping : public api::Mapping {
		private:
			std::vector<std::pair<api::Point, std::size_t>> _leds;
			
			api::Point turtle_position {0, 0};
			api::Angle turtle_orientation = 0.;
			std::size_t current_led_index = 0;
			void moveTo(api::Point p, std::size_t num_led);

		public:
			using typename api::Mapping::map_iterator;
			map_iterator begin() const override;
			map_iterator end() const override;
			const std::vector<std::pair<api::Point, std::size_t>>& leds() const;

			api::Point position() const;
			api::Angle orientation() const;
			std::size_t ledIndex() const;

			void forward(Coordinate distance, std::size_t num_led = 0);
			void turnLeft(api::Angle angle);
			void turnRight(api::Angle angle);
			void jump(api::Point p);
	};

	class StripMapping : public TurtleMapping {
		private:
			std::vector<api::Point> coordinates;
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

	};
}
#endif
