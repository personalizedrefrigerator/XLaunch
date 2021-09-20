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

#include "PixelSetter.h"

class X11PixelSetter : public PixelSetter
{
public:
    void setAt(int x, int y) override;
    Color getAt(int x, int y) const override;
    inline void setColor(int r, int g, int b) override { colorR = r; colorG = g; colorB = b; };
    void setData(char* dataArray, int length, int width, int height);
    char * getDataPtr() const override;
    long getDataLength() const override;

private:
    int width = 0,
        height = 0;
    char* data = nullptr;
    int dataLength = 0;

    // Color values.
    int colorR = 0,
            colorG = 0,
            colorB = 0;
};

