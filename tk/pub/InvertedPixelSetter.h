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

/**
 * Applies simple color effects to the PixelSetter it wraps.
 */

#include "PixelSetterWrapper.h"

class InvertedPixelSetter : public PixelSetterWrapper
{
public:
    InvertedPixelSetter(PixelSetter* pixelSetter) : PixelSetterWrapper(pixelSetter) {};
    void setAt(int x, int y);

    float multiplyRed = 1.0f,
            multiplyGreen = 1.0f,
            multiplyBlue = 1.0f;
};

