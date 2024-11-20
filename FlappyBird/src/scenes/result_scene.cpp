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

	static float opacity = 0.5f;
	static Color semiTransparentBlack = { 0, 0, 0, static_cast <unsigned char>(opacity * 255) };

	void SaveScore(int score)
	{
		savedScore = score;

		if (savedScore > bestScore)
			bestScore = savedScore;
	}

	void Init()
	{
		resultText = Text::GetText
		(screenWidth / 2,
			screenHeight / 3 - static_cast<int>(Text::FontSize::giant),
			Text::Fonts::Default,
			static_cast<int>(Text::FontSize::big),
			"YOU LOST",
			RED);
		Text::CenterTextX(resultText);

		currentScoreText = Text::GetText
		(resultText.location.x,
			resultText.location.y + resultText.fontSize + static_cast<float>(Text::Padding::medium),
			Text::Fonts::Default,
			resultText.fontSize / 2,
			"SCORE: ",
			YELLOW);

		bestScoreText = Text::GetText
		(resultText.location.x,
			currentScoreText.location.y + currentScoreText.fontSize + static_cast<float>(Text::Padding::small),
			Text::Fonts::Default,
			resultText.fontSize / 2,
			"BEST SCORE: ",
			YELLOW);

		playAgainButton = Button::GetButton
		(resultText.location.x,
			bestScoreText.location.y + bestScoreText.fontSize + static_cast<float>(Text::Padding::medium),
			static_cast <float>(Text::GetTextWidth(resultText)),
			static_cast <float>(resultText.fontSize / 2),
			"REPLAY",
			BLACK, SKYBLUE, WHITE,
			Text::Fonts::Default);

		backToMenuButton = Button::GetButton
		(resultText.location.x,
			playAgainButton.shape.y + static_cast<float>(Text::Padding::medium),
			static_cast <float>(Text::GetTextWidth(resultText)),
			static_cast <float>(resultText.fontSize / 2),
			"MENU",
			BLACK, MAGENTA, WHITE,
			Text::Fonts::Default);
	}

	void Update()
	{
		if (IsMusicStreamPlaying(SoundManager::currentBgm))
		{
			StopMusicStream(SoundManager::currentBgm);
		}

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
		DrawRectangle(0, 0, screenWidth, screenHeight, semiTransparentBlack);
		Button::DrawButton(playAgainButton);
		Button::DrawButton(backToMenuButton);

		Text::DrawText(resultText);
		Text::DrawText(currentScoreText);
		Text::DrawText(bestScoreText);
	}
}