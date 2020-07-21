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
		LEFT_RIGHT_LEFT_RIGHT,
		LEFT_RIGHT_RIGHT_LEFT,
		RIGHT_LEFT_RIGHT_LEFT,
		RIGHT_LEFT_LEFT_RIGHT,
		TOP_DOWN_TOP_DOWN,
		TOP_DOWN_DOWN_TOP,
		DOWN_TOP_DOWN_TOP,
		DOWN_TOP_TOP_DOWN
	};

	class LedPanel : public TurtleMapping {
		private:
			void drawLeftRightLeftRight(std::size_t width, std::size_t height);
			void drawLeftRightRightLeft(std::size_t width, std::size_t height);
		public:
			LedPanel(std::size_t width, std::size_t height, PANEL_LINKING linking);

	};
}
#endif
