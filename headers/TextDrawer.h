#pragma once
#include "PixelSetter.h"
#include <string>
#include <unordered_map>

class TextDrawer
{
protected:
	int charWidth = 6;
	int charHeight = 6;
	const unsigned short charactersNumber = 97;
	int cursorLocation = -2;
	std::unordered_map<char, unsigned int> indicies = {};
	std::string characters[97][7] = { { "\b",
		"111111",
		"100001",
		"100001",
		"100001",
		"100001",
		"111111" }, { "1",
		"000010",
		"000110",
		"001010",
		"000010",
		"000010",
		"001111" },{ "2",
		"000000",
		"111111",
		"000001",
		"111111",
		"100000",
		"111111" },{ "3",
		"000000",
		"111110",
		"000001",
		"111111",
		"000001",
		"111111" },{ "4",
		"000000",
		"100001",
		"100001",
		"111111",
		"000001",
		"000001" },{ "5",
		"000000",
		"111111",
		"100000",
		"111111",
		"000001",
		"111111" },{ "6",
		"000000",
		"111111",
		"100000",
		"111111",
		"100001",
		"111111" },{ "7",
		"111111",
		"000001",
		"000001",
		"000001",
		"000001",
		"000001" },{ "8",
		"000000",
		"111111",
		"100001",
		"111111",
		"100001",
		"111111" },{ "9",
		"000000",
		"111111",
		"100001",
		"111111",
		"000001",
		"111111" },{ "0",
		"000000",
		"011110",
		"100101",
		"101001",
		"110001",
		"011110" },{ "*",
		"000000",
		"010101",
		"001110",
		"111111",
		"001110",
		"010101" },{ "-",
		"000000",
		"000000",
		"000000",
		"111111",
		"000000",
		"000000" },{ "+",
		"000000",
		"000100",
		"000100",
		"111111",
		"000100",
		"000100" },{ "=",
		"000000",
		"000000",
		"111111",
		"000000",
		"111111",
		"000000" },{ "/",
		"000001",
		"000010",
		"000100",
		"001000",
		"010000",
		"100000" },{ "E",
		"111111",
		"100000",
		"111111",
		"100000",
		"100000",
		"111111" },{ "R",
		"111110",
		"100010",
		"111110",
		"110000",
		"101000",
		"101000" },{ "O",
		"000000",
		"011110",
		"100001",
		"100001",
		"100001",
		"011110" },{ "!",
		"001000",
		"001000",
		"001000",
		"001000",
		"000000",
		"001000" },{ "?",
		"111100",
		"100100",
		"001100",
		"001000",
		"000000",
		"001000" },{ ",",
		"000000",
		"000000",
		"000000",
		"000000",
		"110000",
		"010000" },{ "A",
		"011110",
		"100001",
		"100001",
		"111111",
		"100001",
		"100001" },{ "B",
		"000000",
		"011110",
		"010001",
		"011111",
		"010001",
		"011111" },{ "C",
		"000000",
		"001111",
		"010000",
		"010000",
		"010000",
		"001111" },{ "D",
		"000000",
		"111100",
		"100010",
		"100001",
		"100001",
		"111110" },{ "E",
		"111110",
		"010000",
		"011111",
		"010000",
		"010000",
		"001111" },{ "F",
		"011111",
		"010000",
		"011111",
		"010000",
		"010000",
		"010000" },{ "G",
		"000000",
		"011111",
		"010000",
		"010011",
		"010001",
		"001111" },{ "H",
		"010001",
		"010001",
		"011111",
		"010001",
		"010001",
		"010001" },{ "I",
		"011111",
		"001000",
		"001000",
		"001000",
		"001000",
		"111111" },{ "J",
		"111111",
		"000100",
		"000100",
		"000100",
		"001100",
		"111000" },{ "K",
		"010010",
		"010100",
		"011000",
		"011000",
		"010100",
		"010010" },{ "L",
		"010000",
		"010000",
		"010000",
		"010000",
		"010000",
		"011111" },{ "M",
		"000000",
		"000000",
		"100010",
		"110110",
		"101010",
		"101010" },{ "N",
		"000000",
		"100001",
		"110001",
		"101001",
		"100101",
		"100011" },{ "P",
		"111111",
		"100001",
		"111111",
		"100000",
		"100000",
		"100000" },{ "Q",
		"000000",
		"111111",
		"100001",
		"100101",
		"111111",
		"000001" },{ "S",
		"111111",
		"100000",
		"111111",
		"000001",
		"000001",
		"111111" },{ "T",
		"111111",
		"001000",
		"001000",
		"001000",
		"001000",
		"001000" },{ "U",
		"000000",
		"000000",
		"100001",
		"100001",
		"100001",
		"111111" },{ "V",
		"000000",
		"000000",
		"100010",
		"100010",
		"010100",
		"001000" },{ "W",
		"100010",
		"101010",
		"101010",
		"101010",
		"101010",
		"111110" },{ "X",
		"100001",
		"010010",
		"001100",
		"001100",
		"010010",
		"100001" },{ "Y",
		"100001",
		"010010",
		"001100",
		"001100",
		"001100",
		"001100" },{ "Z",
		"111111",
		"000100",
		"001000",
		"010000",
		"100000",
		"111111" },{ ":",
		"000000",
		"000000",
		"001000",
		"000000",
		"000000",
		"001000" },{ ".",
		"000000",
		"000000",
		"000000",
		"000000",
		"000000",
		"001000" },{ "(",
		"000110",
		"001000",
		"010000",
		"010000",
		"001000",
		"000110" },{ ")",
		"011000",
		"000100",
		"000010",
		"000010",
		"000100",
		"011000" }, { "[",
		"111111",
		"100000",
		"100000",
		"100000",
		"100000",
		"111111" },{ "]",
		"111111",
		"000001",
		"000001",
		"000001",
		"000001",
		"111111" },{ " ",
		"000000",
		"000000",
		"000000",
		"000000",
		"000000",
		"000000" },{ "a",
		"000000",
		"011110",
		"000001",
		"011101",
		"100011",
		"111101" },{ "b",
		"010000",
		"010000",
		"010000",
		"011110",
		"010001",
		"011110" },{ "c",
		"000000",
		"000000",
		"000000",
		"011100",
		"100000",
		"011100" },{ "d",
		"000010",
		"000010",
		"000010",
		"011110",
		"100010",
		"111110" },{ "e",
		"000000",
		"011110",
		"100001",
		"111110",
		"100000",
		"011110" },{ "f",
		"000110",
		"001010",
		"001000",
		"111110",
		"001000",
		"001000" },{ "g",
		"000000",
		"011110",
		"100001",
		"011111",
		"000001",
		"011110" },{ "h",
		"010000",
		"010000",
		"010000",
		"011110",
		"010001",
		"010001" },{ "i",
		"000000",
		"001000",
		"000000",
		"001000",
		"001000",
		"001000" },{ "j",
		"000000",
		"000100",
		"000000",
		"000100",
		"000100",
		"011000" },{ "k",
		"000000",
		"010000",
		"010100",
		"011000",
		"010100",
		"010010" },{ "l",
		"000000",
		"010000",
		"010000",
		"010000",
		"010000",
		"010000" },{ "m",
		"000000",
		"000000",
		"000000",
		"110110",
		"101010",
		"101010" },{ "n",
		"000000",
		"000000",
		"000000",
		"011100",
		"010010",
		"010010" },{ "o",
		"000000",
		"000000",
		"000000",
		"001100",
		"010010",
		"001100" },{ "p",
		"000000",
		"000000",
		"011100",
		"010010",
		"011100",
		"010000" },{ "q",
		"000000",
		"000000",
		"011110",
		"010001",
		"001111",
		"000001" },{ "r",
		"000000",
		"000000",
		"001110",
		"010000",
		"010000",
		"010000" },{ "s",
		"000000",
		"011110",
		"100000",
		"011100",
		"000010",
		"111100" },{ "t",
		"000000",
		"001000",
		"001000",
		"111110",
		"001000",
		"000100" },{ "u",
		"000000",
		"000000",
		"000000",
		"010100",
		"010100",
		"011100" },{ "v",
		"000000",
		"000000",
		"000000",
		"010001",
		"001010",
		"000100" },{ "w",
		"000000",
		"000000",
		"000000",
		"010101",
		"010101",
		"001010" },{ "x",
		"000000",
		"000000",
		"000000",
		"001010",
		"000100",
		"001010" },{ "y",
		"000000",
		"000000",
		"010100",
		"011100",
		"000100",
		"011000" },{ "z",
		"000000",
		"111110",
		"000100",
		"001000",
		"010000",
		"011110" }, { "{",
		"000011",
		"001100",
		"011000",
		"001000",
		"001100",
		"000011" }, { "}",
		"111100",
		"000010",
		"000010",
		"000001",
		"000010",
		"111100" }, { "\"",
		"001010",
		"001010",
		"000000",
		"000000",
		"000000",
		"000000" }, { "\'",
		"000100",
		"000100",
		"000000",
		"000000",
		"000000",
		"000000" }, { "|",
		"001000",
		"001000",
		"001000",
		"001000",
		"001000",
		"001000" }, { "@",
		"000000",
		"011110",
		"101001",
		"110101",
		"101011",
		"011110" }, { "%",
		"000000",
		"010010",
		"000100",
		"001000",
		"010010",
		"000000" }, { "#",
		"000010",
		"010010",
		"111111",
		"010010",
		"111111",
		"010010" }, { "&",
		"011100",
		"100000",
		"010100",
		"101010",
		"011110",
		"000001" }, { "$",
		"000010",
		"001110",
		"010100",
		"001100",
		"000110",
		"011100" }, { "^",
		"001000",
		"010100",
		"100010",
		"000000",
		"000000",
		"000000" }, { "`",
		"001000",
		"000100",
		"000000",
		"000000",
		"000000",
		"000000" }, { "_",
		"000000",
		"000000",
		"000000",
		"000000",
		"000000",
		"111111" }, { "~",
		"000000",
		"000000",
		"011000",
		"100101",
		"000010",
		"000000" }, { ";",
		"000000",
		"001000",
		"000000",
		"000000",
		"001000",
		"010000" }, { "<",
		"000000",
		"000010",
		"000100",
		"001000",
		"000100",
		"000010" }, { ">",
		"010000",
		"001000",
		"0001000",
		"001000",
		"010000",
		"100000" }, { "\\",
		"100000",
		"01000",
		"001000",
		"000100",
		"000010",
		"000001" } };
	void drawCursor(int x, int y, unsigned int pixelWidth, unsigned int pixelHeight, PixelSetter& pixelSetter) const;
public:
	TextDrawer();
	unsigned int draw(std::string text, int x, int y, PixelSetter &pixelSetter, unsigned int pxWidth, unsigned int pxHeight);
	unsigned int drawWrapped(std::string text, int x, int y,
			PixelSetter & pixelSetter, unsigned int pixelWidth, unsigned int pixelHeight, unsigned int maxWidth);
	void drawLetter(char letter, int x, int y, unsigned int pixelW, unsigned int pixelH, PixelSetter &pixelSetter);
	void setCursorLocation(int location);
};
