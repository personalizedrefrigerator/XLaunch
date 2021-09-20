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

/// A wrapper around another PixelSetter.

class PixelSetterWrapper : public PixelSetter
{
public:
    PixelSetterWrapper(PixelSetter * wrapAround) : givenPixelSetter(wrapAround) {};
    virtual void setAt(int x, int y) override;
    virtual Color getAt(int x, int y) const override;
    virtual void setColor(int r, int g, int b) override;
    virtual char * getDataPtr() const override;
    virtual long getDataLength() const override;

    // Warning: setPixelSetter does NOT delete givenPixelSetter!
    bool setPixelSetter(PixelSetter * newPixelSetter); // Returns true on success.

private:
    PixelSetter * givenPixelSetter; // PixelSetterWrapper is NOT responsible for deleting givenPixelSetter.
};

