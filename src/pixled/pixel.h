#ifndef PIXLED_LED_H
#define PIXLED_LED_H

#include <iostream>
#include "api/pixel.h"

namespace pixled {

	class Color : public api::Color {
		private:
			struct rgb_t {
				int r;
				int g;
				int b;
			};
			rgb_t rgb;

			struct hsv_t {
				float h;
				float s;
				float v;
			};
			hsv_t hsv;


		public:
			static void rgb_to_hsb(const rgb_t& rgb, hsv_t& hsb);
			static void hsb_to_rgb(const hsv_t& hsb, rgb_t& rgb);
			uint8_t red() const override {return rgb.r;}
			uint8_t green() const override {return rgb.g;}
			uint8_t blue() const override {return rgb.b;}

			float hue() const override {return hsv.h;}
			float saturation() const override {return hsv.s;}
			float value() const override {return hsv.v;}

			void setRgb(uint8_t r, uint8_t g, uint8_t b) override;
			void setHsv(float, float, float) override;
	};

	class Pixel : public api::Pixel {
		private:
			Color _color;
		public:
			Color& color() override {
				return _color;
			}

			const Color& color() const override {
				return _color;
			}
	};

	class StripMapping : public api::Mapping {
		private:
			std::vector<api::Coordinates> coordinates;
		public:
			using api::Mapping::coordinates_iterator;

			StripMapping(std::size_t length);

			std::size_t map(api::Coordinates c) const override;
			coordinates_iterator begin() const override;
			coordinates_iterator end() const override;


	};
}
#endif
