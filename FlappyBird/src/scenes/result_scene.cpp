#include "result_scene.h"

#include <iostream>
#include <string>

#include "objects/button.h"
#include "objects/text.h"
#include "utils/scene_manager.h"
#include "utils/screen_info.h"
#include "utils/sound_manager.h"

using namespace std;

namespace ResultScene
{
	static int savedScore;
	static int bestScore;
	static Button::Button backToMenuButton;
	static Button::Button playAgainButton;
	static Text::Text resultText;
	static Text::Text currentScoreText;
	static Text::Text bestScoreText;

	void SaveScore(int score)
	{
		savedScore = score;

		if (savedScore > bestScore)
			bestScore = savedScore;
	}

	void Init()
	{
		StopMusicStream(SoundManager::currentBgm);

		resultText = Text::GetText
		(screenWidth / 2,
			screenHeight / 3 - static_cast<int>(Text::FontSize::giant),
			static_cast<int>(Text::FontSize::big),
			"YOU LOST",
			RED);
		Text::CenterTextX(resultText);

		currentScoreText = Text::GetText
		(resultText.location.x,
			resultText.location.y + resultText.fontSize + static_cast<float>(Text::Padding::medium),
			resultText.fontSize / 2,
			"SCORE: ",
			YELLOW);

		bestScoreText = Text::GetText
		(resultText.location.x,
			currentScoreText.location.y + currentScoreText.fontSize + static_cast<float>(Text::Padding::small),
			resultText.fontSize / 2,
			"BEST SCORE: ",
			YELLOW);

		playAgainButton = Button::GetButton
		(resultText.location.x,
			bestScoreText.location.y + bestScoreText.fontSize + static_cast<float>(Text::Padding::medium),
			static_cast <float>(Text::GetTextWidth(resultText)),
			static_cast <float>(resultText.fontSize / 2),
			"REPLAY",
			BLACK, SKYBLUE, WHITE);

		backToMenuButton = Button::GetButton
		(resultText.location.x,
			playAgainButton.shape.y + static_cast<float>(Text::Padding::medium),
			static_cast <float>(Text::GetTextWidth(resultText)),
			static_cast <float>(resultText.fontSize / 2),
			"MENU",
			BLACK, MAGENTA, WHITE);
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


		currentScoreText.content = "SCORE: " + to_string(savedScore);
		bestScoreText.content = "BEST SCORE: " + to_string(bestScore);

	}

	void Draw()
	{
		Button::DrawButton(playAgainButton);
		Button::DrawButton(backToMenuButton);

		Text::DrawText(resultText);
		Text::DrawText(currentScoreText);
		Text::DrawText(bestScoreText);
	}
}