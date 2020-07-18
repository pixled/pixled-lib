#ifndef PIXLED_MAPPING_H
#define PIXLED_MAPPING_H

#include "api/geometry.h"
#include "api/mapping.h"
#include <unordered_map>

namespace pixled {

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
	};

	class StripMapping : public TurtleMapping {
		private:
			std::vector<api::Point> coordinates;
		public:
			StripMapping(std::size_t num_led);

	};
}
#endif
