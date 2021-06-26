#ifndef PIXLED_MAPPING_H
#define PIXLED_MAPPING_H

#include "../mapping.h"

namespace pixled { 

	/**
	 * Namespace containing predefined extensions of the Mapping class.
	 */
	namespace mapping {
		/**
		 * Mapping output stream operator.
		 *
		 * Builds a fancy 2D string representation of a Mapping that can easily
		 * be used for debug purpose on embedded systems.
		 */
		std::ostream& operator<<(std::ostream& o, const Mapping& m);

		/**
		 * A [turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics)
		 * based mapping.
		 *
		 * Leds are regularly dropped by the "turtle" as it moves in the space.
		 */
		class TurtleMapping : public Mapping {
			private:
				point turtle_position {0, 0};
				angle turtle_orientation = angle::fromDeg(0.);
				index_t current_led_index = 0;
				void moveTo(point p, index_t num_led);

			public:
				/**
				 * Current position of the turtle.
				 */
				point position() const;
				/**
				 * Current orientation of the turtle.
				 */
				angle orientation() const;
				/**
				 * Current led index.
				 */
				index_t ledIndex() const;


				/**
				 * Moves the turtle `distance` forward, dropping `num_led`
				 * leds.
				 *
				 * Leds are placed to correspond as much as possible to the
				 * shape of a real led strip.
				 *
				 * For example, we might represent a led on a led strip as
				 * follows, including margins: `| o |`
				 *
				 * Now, if we represent the starting and final positions of the
				 * turtle by `+` , the generated mapping would look as follows
				 * if 3 leds are placed: `+ o | o | o +`. The positions of the
				 * leds correspond to `o`s. The margin between leds is computed
				 * to fit the total `distance` with the provided `num_led`.
				 *
				 * The most important aspect of this mechanism is to understand
				 * that the first led is not dropped at the current position of
				 * the turtle: it would be more accurate to say that the "input
				 * pin" of the led is placed at the current position.
				 *
				 * @param distance distance to cross
				 * @param num_led number of led to drop
				 */
				void forward(coordinate distance, index_t num_led = 0);
				/**
				 * Turns the turtle left by the specified angle.
				 *
				 * @param angle rotation
				 */
				void turnLeft(angle angle);
				/**
				 * Turns the turtle right by the specified angle.
				 *
				 * @param angle rotation
				 */
				void turnRight(angle angle);

				/**
				 * Places the turtle at position p, without dropping any led,
				 * keeping the same orientation().
				 *
				 * @param p point where the turtle should be placed
				 */
				void jump(point p);
		};

		/**
		 * A simple mapping representing a 1D led strip.
		 */
		class LedStrip : public TurtleMapping {
			private:
				std::vector<point> coordinates;
				index_t length;
			public:
				/**
				 * LedStrip constructor.
				 *
				 * @param length number of leds
				 */
				LedStrip(index_t length);

				/**
				 * Returns the number of leds in the strip.
				 *
				 * @return number of leds
				 */
				index_t getLength() const {
					return length;
				}
		};

		/**
		 * All possible panel linking techniques (at least, relatively
		 * reasonable ones).
		 *
		 * See the [Mapping
		 * wiki](https://github.com/pixled/pixled-lib/wiki/Mapping) for more
		 * detailed informations.
		 */
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

		/**
		 * A mapping representing a 2D led panel.
		 */
		class LedPanel : public TurtleMapping {
			private:
				index_t _width;
				index_t _height;

				void drawLeftRightLeftRightFromBottom(index_t width, index_t height);
				void drawRightLeftRightLeftFromBottom(index_t width, index_t height);
				void drawHorizontalSnakeFromBottom(index_t width, index_t height);

				void drawLeftRightLeftRightFromTop(index_t width, index_t height);
				void drawRightLeftRightLeftFromTop(index_t width, index_t height);
				void drawHorizontalSnakeFromTop(index_t width, index_t height);

				void drawTopDownTopDownFromLeft(index_t width, index_t height);
				void drawDownTopDownTopFromLeft(index_t width, index_t height);
				void drawVerticalSnakeFromLeft(index_t width, index_t height);

				void drawTopDownTopDownFromRight(index_t width, index_t height);
				void drawDownTopDownTopFromRight(index_t width, index_t height);
				void drawVerticalSnakeFromRight(index_t width, index_t height);
			public:
				/**
				 * LedPanel constructor.
				 *
				 * @param width panel width (led count)
				 * @param height panel height (led count)
				 * @param linking panel linking
				 */
				LedPanel(index_t width, index_t height, PANEL_LINKING linking);

				/**
				 * Panel width (led count).
				 */
				index_t width() const {return _width;}
				/**
				 * Panel height (led count).
				 */
				index_t height() const {return _height;}
		};
	}
}
#endif
