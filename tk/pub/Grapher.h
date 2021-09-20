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
#include <vector>

class Grapher
{
public:
    Grapher(unsigned int maxPoints);

    void setBarLocation(double y);

    void setMaxY(double y);
    void setPixelPadding(unsigned int pixelPadding) { padding = pixelPadding; };
    void setColors(Color pointColor, Color barColor);

    void addPoint(double y);
    std::vector<double>& getData() { return data; };
    
    void render(PixelSetter& givenPixelSetter, int x, int y, unsigned int width, unsigned int height) const;

private:
    std::vector<double> data;
    double barY = 0.0;
    double maxY = 1.0;
    unsigned int padding = 1;
    Color pointColor { 255, 0, 0 };
    Color barColor { 0, 255, 0 };
};

