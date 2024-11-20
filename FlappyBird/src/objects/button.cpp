#include "Objects/button.h"

#include "utils/sound_manager.h"

namespace Button
{
	float buttonWidth = 320;

	bool IsMouseOnButton(Button& button)
	{
		return GetMouseX() > button.shape.x &&
			GetMouseY() > button.shape.y &&
			GetMouseX() < (button.shape.x + button.shape.width) &&
			GetMouseY() < (button.shape.y + button.shape.height);
	}

	bool IsButtonPrssed(Button& button)
	{
		if (IsMouseOnButton(button))
		{
			button.currentColor = button.highlightColor;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				PlaySound(SoundManager::clickButtonSfx);
				return true;
			}
		}
		else
			button.currentColor = button.defaultColor;

		return false;
	}


	static void DrawButtonText(Button button)
	{
		Font font = Text::GetFont(button.textShown.font);

		Vector2 textSize = MeasureTextEx(
			font,
			button.textShown.content.c_str(),
			static_cast<float>(button.textShown.fontSize),
			Text::textSpacing
		);

		float textX = button.shape.x + button.shape.width / 2 - textSize.x / 2;
		float textY = button.shape.y + button.shape.height / 2 - textSize.y / 2;

		DrawTextEx
		(font,
			button.textShown.content.c_str(),
			Vector2{ textX, textY },
			static_cast<float>(button.textShown.fontSize),
			Text::textSpacing,
			button.textShown.currentColor);
	}

	static void DrawButtonRect(Button button)
	{
		DrawRectangle(static_cast<int>(button.shape.x), static_cast<int>(button.shape.y), static_cast<int>(button.shape.width), static_cast<int>(button.shape.height), button.currentColor);
		DrawRectangleLines(static_cast<int>(button.shape.x), static_cast<int>(button.shape.y), static_cast<int>(button.shape.width), static_cast<int>(button.shape.height), button.highlightColor);
	}

	void DrawButton(Button button)
	{
		DrawButtonRect(button);
		DrawButtonText(button);
	}

	Button GetButton(float x, float y, float width, float height, string content, Color mainColor, Color highlightColor, Color textColor, Text::Fonts font)
	{
		Button myButton;

		myButton.defaultColor = mainColor;
		myButton.currentColor = myButton.defaultColor;
		myButton.highlightColor = highlightColor;

		myButton.shape.width = width;
		myButton.shape.height = height;
		myButton.shape.x = x;
		myButton.shape.y = y;

		myButton.textShown.content = content;
		myButton.textShown.fontSize = static_cast<int>(height) / 2;
		myButton.textShown.currentColor = textColor;
		myButton.textShown.location.x = x + width / 2.0f - static_cast<float>(MeasureText(myButton.textShown.content.c_str(), myButton.textShown.fontSize), myButton.textShown.fontSize);
		myButton.textShown.font = font;

		return myButton;
	}

};