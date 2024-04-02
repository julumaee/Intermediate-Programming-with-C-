/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "canvas.h"
#include <iostream>
#include <algorithm>

Canvas::Canvas()
{
	
}

// Just delete the list, the individual items are handled by main
Canvas::~Canvas()
{
}

// Add an item at the end of the list
void Canvas::Add(CanvasItem* item)
{
	items.push_back(item);
	itemcount += 1;
}

// Find and remove pointer from list
// But don't free the memory, leave that to main
// If pointer is not found, do nothing
void Canvas::Remove(CanvasItem* item)
{
	// TODO instead of a single item, should work for a list
	// This removes the frame for the logo in the collage
	// Your code here

	size_t index;

	if (item == nullptr) {
		return;
	} else {

		for(size_t i=0; i<itemcount; i++)
		{
			CanvasItem* item_i = items[i];
			if (item_i == item)
			{
				index = i;
				break;
			}
		}

		items.erase(items.begin() + index);
		itemcount -= 1;
	}

}

// Find given items from list and swap their positions
// Swap only if both pointers are found
void Canvas::Swap(CanvasItem* item1, CanvasItem* item2)
{
	if (item1 == nullptr || item2 == nullptr) {
		return;
	}

	size_t index1;
	size_t index2;

	for(size_t i=0; i<itemcount; i++)
	{
		CanvasItem* item = items[i];
		if (item == item1)
		{
			index1 = i;
		} else if (item == item2)
		{
			index2 = i;
		}
	}
	std::swap(items[index1], items[index2]);
}

// Draws all items in the list in order
// Blends the pixels colors of the items with their item color
// Draws the items in their given position and scales them accordingly
// Blends drawn layers based on alpha channel (transparency)
void Canvas::draw(PNG* canvas) const
{
	for(size_t i=0; i<itemcount; i++) {
		CanvasItem* item = items[i];
		
		for(size_t x=0, xmax = item->width(); x<xmax; x++){
			for(size_t y=0, ymax = item->height(); y<ymax; y++){
				// This gets the pixel color blended with item color
				// Check canvasitem.cpp
				RGBAPixel coli = item->getBlendedPixel(x,y);
				Vector2 sc = item->scale();
				Vector2 pos = item->position();
				
				// A loop is needed in case it must be scaled up, or we end up with gaps
				for(int xs=0; xs < std::abs((int)(sc.x()-0.001))+1; xs++){
					for(int ys=0; ys < std::abs((int)(sc.y()-0.001))+1; ys++){
						// Determine the position on the canvas based on 
						// item position, scale, pixel position and adjacent pixel selection
						// TODO right now it just loops the pixels of the item
						// x1, y1 should be coordinates of the canvas to draw to
						// So we should add item position and adjacent pixel selection xs, ys
						// Multiply x and y by item scale
						
						int x1 = pos.x() + sc.x() * x;
						int y1 = pos.y() + sc.y() * y;

						x1 += xs;
						y1 += ys;
						
						// Check that it's within bounds
						if(x1 >= 0 && x1 < (int)canvas->width() && y1 >= 0 && y1 < (int)canvas->height()) {
							// Current color of the canvas
							RGBAPixel* colc = (*canvas)(x1,y1);
							
							// Multiply item color with alpha, canvas color with 255-alpha
							// Add them and divide by 255
							// In other words 255 = replace old pixel with new. 0 = don't draw.
							// 1-254 = partly new pixel, partly old
							
							colc->red = ((coli.red * coli.alpha) + (colc->red * (255 - coli.alpha))) / 255;
							colc->green = ((coli.green * coli.alpha) + (colc->green * (255 - coli.alpha))) / 255;
							colc->blue = ((coli.blue * coli.alpha) + (colc->blue * (255 - coli.alpha))) / 255;
							
							// We can keep the canvas opaque, no reason to change it
							colc->alpha = 255;
						}
					}
				}
			}
		}
	}
}
