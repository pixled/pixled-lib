#ifndef PIXLED_GEOMETRY_H
#define PIXLED_GEOMETRY_H

#include <functional>
#include <cmath>
#include <iostream>
#include <vector>

namespace pixled {
	/**
	 * Predefined PI constant.
	 */
	static const float PI = 3.14159265358979323846f;

	/**
	 * Type used to define point coordinates.
	 */
	typedef float coordinate;

	/**
	 * A basic 2D point.
	 */
	struct point {
		/**
		 * x coordinate.
		 */
		coordinate x;
		/**
		 * y coordinate.
		 */
		coordinate y;
		/**
		 * point default constructor.
		 *
		 * The point is initialized at (0, 0).
		 */
		point() : point(0, 0) {}

		/**
		 * point constructor.
		 *
		 * @param x x coordinate
		 * @param y y coordinate
		 */
		point(coordinate x, coordinate y)
			: x(x), y(y) {}
	};

	/**
	 * Basic class used to represent angles, with radian / degree conversion.
	 */
	class angle {
		private:
			friend angle operator+(const angle&, const angle&);
			friend angle operator-(const angle&, const angle&);

			// value in radian
			float value;
			angle(float value) : value(value) {}

		public:

			/**
			 * Builds an angle from the specified value, in radian.
			 *
			 * @param value value of the angle in radian
			 */
			static angle fromRad(float value);
			/**
			 * Builds an angle from the specified value, in degree.
			 *
			 * @param value value of the angle in degree
			 */
			static angle fromDeg(float value);

			/**
			 * Returns the value of this angle, in radian.
			 *
			 * @return value in radian
			 */
			float toRad() const {
				return value;
			}

			/**
			 * Returns the value of this angle, in degree.
			 *
			 * @return value in degree
			 */
			float toDeg() const {
				return value * 180.f / PI;
			}

			/**
			 * Adds `a` to this angle.
			 *
			 * @param a angle to add
			 * @return reference to this angle
			 */
			angle& operator+=(const angle& a) {
				value+=a.value;
				return *this;
			}

			/**
			 * Substracts `a` from this angle.
			 *
			 * @param a angle to substract
			 * @return reference to this angle
			 */
			angle& operator-=(const angle& a) {
				value-=a.value;
				return *this;
			}
	};

	/**
	 * Sums `a` to `b`.
	 *
	 * @return An angle with value `a+b`
	 */
	angle operator+(const angle& a, const angle& b);

	/**
	 * Substracts `b` from `a`.
	 *
	 * @return An angle with value `a-b`
	 */
	angle operator-(const angle& a, const angle& b);

	/**
	 * A Line with equation a*x + b*y + c = 0
	 */
	struct line {
		/**
		 * a
		 */
		coordinate a;
		/**
		 * b
		 */
		coordinate b;
		/**
		 * c
		 */
		coordinate c;
		/**
		 * line constructor.
		 *
		 * @param a a
		 * @param b b
		 * @param c c
		 */
		line(coordinate a, coordinate b, coordinate c)
			: a(a), b(b), c(c) {}

		/**
		 * Builds a line passing through `p` with the specified angle from the
		 * horizontal.
		 */
		line(point p, angle a);
		/**
		 * Builds a line passing through the two specified points.
		 */
		line(point p0, point p1);
	};

	/**
	 * A point hash function object.
	 */
	struct point_hash {
		/**
		 * Computes an hash value for the point p.
		 *
		 * The hash is computed as follows (what is probably not an optimal
		 * hash function):
		 * ```cpp
		 * auto hash1 = std::hash<coordinate>{}(p.x);
		 * auto hash2 = std::hash<coordinate>{}(p.y);
		 * return hash1 ^ hash2;
		 * ```
		 *
		 * @return hash value of `p`
		 */
		std::size_t operator()(const point& p) const;
	};

	/**
	 * Checks if the two points are equal, i.e. if their x/y coordinates are
	 * equal.
	 *
	 * @return true iff `p1` == `p2`
	 */
	bool operator==(const point& p1, const point& p2);

	/**
	 * A function object that can be used to check point equality.
	 */
	struct point_equal {
		/**
		 * Checks if the two points are equal.
		 *
		 * @return true iff `p1` == `p2`
		 */
		bool operator()(const point& p1, const point& p2) const;
	};

	/**
	 * Point output stream operator.
	 */
	std::ostream& operator<<(std::ostream& o, const point& p);

	/**
	 * Returns the euclidian distance between the two points.
	 *
	 * @param p1 point 1
	 * @param p2 point 2
	 * @return distance between p1 and p2
	 */
	float distance(const point& p1, const point& p2);
	/**
	 * Computes the cosine of `a`.
	 *
	 * @param a angle
	 * @return cos(a)
	 */
	float cos(const angle& a);
	/**
	 * Computes the sine of `a`.
	 *
	 * @param a angle
	 * @return sin(a)
	 */
	float sin(const angle& a);
	/**
	 * Computes the tangent of `a`.
	 *
	 * @param a angle
	 * @return tan(a)
	 */
	float tan(const angle& a);


	/**
	 * A basic box class.
	 */
	class box {
		protected:
			/**
			 * Position of the bottom left corner of the box.
			 */
			point _position;
			/**
			 * Box width.
			 */
			coordinate _width;
			/**
			 * Box height.
			 */
			coordinate _height;
			/**
			 * Default box constructor.
			 *
			 * The box is initialized at (0, 0), with a null width and height.
			 */
			box();

		public:
			/**
			 * box constructor.
			 *
			 * @param position position of the bottom left corner of the box
			 * @param width box width
			 * @param height box height
			 */
			box(point position, coordinate width, coordinate height);

			/**
			 * Position of the bottom left corner of the box.
			 */
			point position() const {return _position;}
			/**
			 * Box width.
			 */
			coordinate width() const {return _width;}
			/**
			 * Box height.
			 */
			coordinate height() const {return _height;}
	};

	/**
	 * Class used to represent the bounding box of a set of point, i.e. the
	 * smallest box that contains all the points.
	 */
	class bounding_box : public box {
		private:
			bool init = false;
		public:
			/**
			 * Initializes a box that only contains (0, 0).
			 */
			bounding_box();
			/**
			 * Builds a bounding_box that wraps all the specified points.
			 *
			 * stretchTo() can be used to extend the bounding box afterwards.
			 */
			bounding_box(std::vector<point> points);

			/**
			 * Stretch the bounding box so that it contains the specified
			 * point.
			 *
			 * @param p point that must be contained in the box.
			 */
			void stretchTo(point p);
	};

	/**
	 * Class used to represent an [archimedean
	 * spiral](https://en.wikipedia.org/wiki/Archimedean_spiral) of equation
	 * `r = a + b * theta`.
	 */
	class spiral {
		private:
			float a;
			float b;
			point center;

		public:
			/**
			 * Spiral constructor.
			 *
			 * @param a a
			 * @param b b
			 * @param center center of the spiral
			 */
			spiral(float a, float b, point center)
				: a(a), b(b), center(center) {}

			/**
			 * Returns the point of the spiral at the specified angle.
			 *
			 * Notice that the angle might be greater than 360° to represent
			 * spiral loops.
			 *
			 * @param theta angle
			 * @return point of the spiral
			 */
			point operator()(angle theta);
	};
}

#endif
