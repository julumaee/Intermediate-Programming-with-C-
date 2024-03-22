/**
 * @file rgbapixel.h
 * Definition of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */

#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
using std::uint8_t;

class RGBAPixel
{
    public:
        uint8_t red;    // Value of red color in channel
        uint8_t green;  // Value of green color in channel
        uint8_t blue;   // Value of blue color in channel
        uint8_t alpha;  // The transparency of the pixel (0 = fully transparent)

    RGBAPixel() : red(255), green(255), blue(255), alpha(255) {}
    RGBAPixel(uint8_t _r, uint8_t _g, uint8_t _b) : red(_r), green(_g), blue(_b), alpha(255) {}
};

#endif