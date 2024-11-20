#include "objects/text.h"
#include "utils/screen_info.h"

namespace Text
{
	static Font titleFont1;
	static Font titleFont2;
	static Font generalText;




	void CenterTextX(Text& text)
	{
		text.location.x = screenWidth/2 - GetTextWidth(text) / 2;
	}

	float GetTextWidth(Text text)
	{
		return MeasureTextEx(GetFont(text.font), text.content.c_str(), static_cast<float> (text.fontSize), 10).x;
	}

	Font GetFont(Fonts font)
	{
		switch (font)
		{
		case Fonts::Title1:
			return titleFont1;
			break;
		case Fonts::Title2:
			return titleFont2;
			break;
		case Fonts::Default:
			return generalText;
			break;
		default:
			return generalText;
			break;
		}
	}

	void LoadFonts()
	{
		titleFont1 = LoadFont("res/fonts/Swamp Witch.ttf");
		titleFont2 = LoadFont("res/fonts/NECK ROMANCER Regular.ttf");
		generalText = LoadFont("res/fonts/joystix monospace.otf");
	}

	void UnloadFonts()
	{
		UnloadFont(GetFont(Fonts::Default));
		UnloadFont(GetFont(Fonts::Title1));
		UnloadFont(GetFont(Fonts::Title2));
	}

	void DrawText(Text myText)
	{
		SetTextureFilter(GetFont(myText.font).texture, TEXTURE_FILTER_BILINEAR);
		DrawTextEx(GetFont(myText.font), myText.content.c_str(), myText.location, static_cast<float>(myText.fontSize), textSpacing, myText.currentColor);
	}

	void DrawText(Text myText, int number)
	{
		SetTextureFilter(GetFont(myText.font).texture, TEXTURE_FILTER_BILINEAR);
		DrawTextEx(GetFont(myText.font), TextFormat(myText.content.c_str(), number), myText.location, static_cast<float>(myText.fontSize), textSpacing, myText.currentColor);
	}


	Text GetText(float x, float y, Fonts font, int fontSize, string content, Color color)
	{
		Text myText;

		myText.currentColor = color;
		myText.content = content;
		myText.fontSize = fontSize;
		myText.location.x = x;
		myText.location.y = y;
		myText.font = font;

		return myText;
	}
};