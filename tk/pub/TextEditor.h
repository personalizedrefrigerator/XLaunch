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
#include "TextDrawer.h"

#include <string>
#include <unordered_map>
#include <functional>

class TextEditor
{
public:
	TextEditor() : content(""), lastKeyCode(0) {};
	void handleKeyChange(int keyCode);
	void render(PixelSetter& display, int x, int y, int maxWidth);
	std::string& getContent() { return content; };
	void setTextSize(unsigned int pxWidth, unsigned int pxHeight);
	void setNewLineCallback(std::function<void(std::string&)> callback);

private:
	TextDrawer textRenderer = TextDrawer();
	char shift(char character);
	std::unordered_map<char, char> shiftMap = {{'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
			{'/', '?'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
			{',', '<'}, {'.', '>'}, {'\\', '|'}, {';', ':'}, {'\'', '"'}, {'-', '_'}, {'=', '+'},
			{'[', '{'}, {']', '}'}, {'`', '~'}};
	std::string content;
	int lastKeyCode;
	int fromEnd = 0;
	unsigned int pixelWidth = 1, pixelHeight = 2;
	std::function<void(std::string&)> newLineCallback;
	bool hasNewLineCallback = false;
};

