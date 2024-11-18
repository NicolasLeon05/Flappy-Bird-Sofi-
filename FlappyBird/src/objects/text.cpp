#include "objects/text.h"

namespace Text
{
	static Font titlemusic1;
	static Font titlemusic2;
	static Font generalText;

	void CenterTextX(Text& text)
	{
		text.location.x -= GetTextWidth(text) / 2;
	}

	int GetTextWidth(Text text)
	{
		return MeasureText(text.content.c_str(), text.fontSize);
	}

	int GetTextHeight(Text text)
	{
		return MeasureText(text.content.c_str(), text.fontSize);
	}

	void DrawText(Text myText)
	{
		DrawText(myText.content.c_str(), static_cast<int>(myText.location.x), static_cast<int>(myText.location.y), myText.fontSize, myText.currentColor);
	}

	void DrawText(Text myText, int number)
	{
		DrawTextEx(GetFontDefault(), TextFormat(myText.content.c_str(), number), myText.location, static_cast<float>(myText.fontSize), textSpacing, myText.currentColor);
	}


	Text GetText(float x, float y, int fontSize, string content, Color color)
	{
		Text myText;

		myText.currentColor = color;
		myText.content = content;
		myText.fontSize = fontSize;
		myText.location.x = x;
		myText.location.y = y;

		return myText;
	}
};