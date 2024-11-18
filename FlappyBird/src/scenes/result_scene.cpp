#include "result_scene.h"

#include <iostream>
#include <string>

#include "objects/button.h"
#include "objects/text.h"
#include "utils/scene_manager.h"
#include "utils/screen_info.h"

using namespace std;

namespace ResultScene
{
	static int savedScore;
	static Button::Button backToMenuButton;
	static Button::Button playAgainButton;
	static Text::Text resultText;
	static Text::Text scoreText;

	void SaveScore(int score)
	{
		savedScore = score;
	}

	void Init()
	{
		resultText = Text::GetText(screenWidth / 2,
			screenHeight / 2 - static_cast<int>(Text::Padding::big),
			Text::Fonts::Title2, static_cast<int>(Text::FontSize::big),
			"YOU LOST", RED, YELLOW);
		Text::CenterTextX(resultText);

		scoreText = Text::GetText(screenWidth / 2,
			resultText.location.y + Text::GetTextHeight(resultText) + static_cast<int>(Text::Padding::tiny),
			resultText.fontSize / 2,
			"SCORE: ", YELLOW);

		playAgainButton = Button::GetButton(resultText.location.x,
			resultText.location.y + Text::GetTextHeight(resultText) + static_cast<int>(Text::Padding::medium),
			static_cast <float>(Text::GetTextWidth(resultText)),
			static_cast <float>(Text::GetTextHeight(resultText) / 2),
			"REPLAY", BLACK, MAGENTA, WHITE);

		backToMenuButton = Button::GetButton(resultText.location.x,
			playAgainButton.shape.y + playAgainButton.shape.height + static_cast<int>(Text::Padding::tiny),
			static_cast <float>(Text::GetTextWidth(resultText)),
			static_cast <float>(Text::GetTextHeight(resultText) / 2),
			"MENU", BLACK, SKYBLUE, WHITE);
	}

	void Update()
	{
		if (Button::IsButtonPrssed(backToMenuButton))
		{
			SceneManager::SetCurrentScene(SceneManager::Menu);
		}

		if (Button::IsButtonPrssed(playAgainButton))
		{
			SceneManager::SetCurrentScene(SceneManager::Gameplay);
		}

		if (scoreText.content != "SCORE: " + to_string(savedScore))
		{
			scoreText.content += to_string(savedScore);
			Text::CenterTextX(scoreText);
		}

	}

	void Draw()
	{
		Button::DrawButton(playAgainButton);
		Button::DrawButton(backToMenuButton);

		Text::DrawText(resultText);
		Text::DrawText(scoreText);
	}
}