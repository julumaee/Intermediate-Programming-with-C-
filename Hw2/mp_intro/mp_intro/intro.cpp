#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
	PNG pic(inputFile);
	PNG rotated(pic.width(), pic.height());

	for (size_t y = 0; y < pic.height(); y++)
	{
		for (size_t x = 0; x < pic.width(); x++)
		{
			RGBAPixel* originalPixel = pic(x, y);
			*(rotated(rotated.width() - 1 - x, rotated.height() - 1 - y)) = *originalPixel;
		}
	}
	rotated.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	
	// Define unique colors
    RGBAPixel green1(141, 156, 128);
    RGBAPixel green2(194, 203, 128);
    RGBAPixel red1(236, 189, 193);
	RGBAPixel red2(251, 234, 233);

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			if ((x + y) % 2 == 0)
			{
				if (y % 3 == 1)
				    *png(x, y) = green1;
				else
					*png(x, y) = red1;
			}
            else if ((x + y) % 13 == 1)
                *png(x, y) = green2;
            else if ((x + y) % 9 == 2)
                *png(x, y) = red1;
			else
				*png(x, y) = red2;
		}
	}
	return png;
}
