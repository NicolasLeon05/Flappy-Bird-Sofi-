#pragma once

#include <iostream>
#include "raylib.h"

using namespace std;

namespace Text
{
	const float textSpacing = 10.0f;

	enum class Padding
	{
		minimum = 10,
		tiny = 20,
		small = 30,
		medium = 60,
		big = 90,
		giant = 120
	};

	enum class FontSize
	{
		tiny = 12,
		small = 20,
		medium = 40,
		big = 80,
		giant = 140
	};

	struct Text
	{
		string content = " ";
		int fontSize = 0;
		Vector2 location;
		Color currentColor;
		Color alt1Color;
		Color alt2Color;
	};


	//Prints a text
	void DrawText(Text myText);

	//Prints a text that needs a number to print
	void DrawText(Text myText, int score);

	void CenterTextX(Text& text);

	int GetTextWidth(Text text);

	int GetTextHeight(Text text);

	//Create texts
	Text GetText(float x, float y, int fontSize, string content, Color color);
};

