/**
 *  XLaunch - Dialog for choosing items from a menu.
 *   Copyright (C) 2021  Henry Heino
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "Color.h"

class PixelSetter
{
public:
    virtual void setAt(int x, int y) = 0;
    virtual Color getAt(int x, int y) const = 0;
    virtual void setColor(int r, int g, int b) = 0;
    virtual char * getDataPtr() const = 0;
    virtual long getDataLength() const = 0;
    void clear(unsigned char clearValue);
    inline void drawRect(int x, int y, int w, int h, PixelSetter& pixelSetter);
    virtual ~PixelSetter() {};
};

void PixelSetter::drawRect(int startX, int startY, int width, int height, PixelSetter& drawer)
{
    int y;
    int maxX = startX + width;
    int maxY = startY + height;

    for(int x = startX; x < maxX; x++)
    {
        for(y = startY; y < maxY; y++)
        {
            drawer.setAt(x, y);
        }
    }
}

