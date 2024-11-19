#include "menu_scene.h"

#include "raylib.h"

#include "utils/scene_manager.h"
#include "utils/sound_manager.h"
#include "scenes/gameplay_scene.h"
#include "utils/screen_info.h"
#include "objects/button.h"
//NOTE: All of the above are used

using namespace std;

enum Options
{
	Play,
	Exit
};

static Button::Button singlePlayerButton;
static Button::Button twoPlayersButton;
static Button::Button exitButton;
static Button::Button creditsButton;
static Button::Button howToPlayButton;

static Button::Button muteBgm;
static Button::Button muteSfx;

static Text::Text titlePart1;
static Text::Text titlePart2;
static Text::Text versionText;

void MenuScene::Init()
{
#pragma region TITLE_TEXTS

	titlePart1 = Text::GetText
	(screenWidth / 2,
		titlePart1.location.y = static_cast<float>(Text::Padding::medium),
		static_cast<int>(Text::FontSize::big),
		"PLACE",
		MAGENTA);

	Text::CenterTextX(titlePart1);

	titlePart2 = Text::GetText
	(screenWidth / 2,
		titlePart1.location.y + titlePart1.fontSize,
		static_cast<int>(Text::FontSize::big),
		"HOLDER",
		YELLOW);

	Text::CenterTextX(titlePart2);

#pragma endregion

	singlePlayerButton = Button::GetButton
	(static_cast<float>(GetScreenWidth()) / 2.0f - static_cast<float>(Text::GetTextWidth(titlePart2)) / 2.0f,
		static_cast<float>(GetScreenHeight()) / 1.8f - titlePart2.fontSize,
		static_cast<float>(Text::GetTextWidth(titlePart2)),
		static_cast<float>(titlePart2.fontSize) / 2.0f,
		"SINGLE PLAYER",
		BLACK, MAGENTA, WHITE);

	twoPlayersButton = Button::GetButton
	(singlePlayerButton.shape.x,
		singlePlayerButton.shape.y + singlePlayerButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width, singlePlayerButton.shape.height,
		"TWO PLAYERS",
		BLACK, MAGENTA, WHITE);

	creditsButton = Button::GetButton
	(singlePlayerButton.shape.x,
		twoPlayersButton.shape.y + twoPlayersButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width, singlePlayerButton.shape.height,
		"CREDITS",
		BLACK, SKYBLUE, WHITE);

	howToPlayButton = Button::GetButton
	(creditsButton.shape.x,
		creditsButton.shape.y + creditsButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width,
		singlePlayerButton.shape.height,
		"HOW TO PLAY",
		BLACK, YELLOW, WHITE);

	exitButton = Button::GetButton
	(singlePlayerButton.shape.x,
		howToPlayButton.shape.y + howToPlayButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width,
		singlePlayerButton.shape.height,
		"EXIT",
		BLACK, RED, WHITE);

	muteBgm = Button::GetButton
	(titlePart1.location.x + GetTextWidth(titlePart1) + static_cast<int>(Text::Padding::big),
		static_cast<int>(Text::Padding::small),
		singlePlayerButton.shape.width / 3,
		singlePlayerButton.shape.height,
		"Music",
		BLACK, RED, WHITE);

	muteSfx = Button::GetButton
	(muteBgm.shape.x,
		muteBgm.shape.y + muteBgm.shape.height + static_cast<int>(Text::Padding::minimum),
		singlePlayerButton.shape.width / 3,
		singlePlayerButton.shape.height,
		"Sounds",
		BLACK, RED, WHITE);

	//Version
	versionText = Text::GetText
	(static_cast<float>(Text::Padding::tiny),
		static_cast<float>(Text::Padding::tiny),
		static_cast<int>(Text::FontSize::medium),
		"v0.4",
		GRAY);
}


void MenuScene::Update()
{
	if (Button::IsButtonPrssed(muteBgm))
	{
		SoundManager::MuteMusic();
	}

	if (Button::IsButtonPrssed(muteSfx))
	{
		SoundManager::MuteSounds();
	}

	if (Button::IsButtonPrssed(singlePlayerButton))
	{
		GameplayScene::isSinglePlayer = true;
		SceneManager::SetCurrentScene(SceneManager::Gameplay);
	}

	if (Button::IsButtonPrssed(twoPlayersButton))
	{
		GameplayScene::isSinglePlayer = false;
		SceneManager::SetCurrentScene(SceneManager::Gameplay);
	}

	if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
	{
		StopMusicStream(SoundManager::currentBgm);
		SoundManager::currentBgm = SoundManager::gameplayBgm;
		PlayMusicStream(SoundManager::currentBgm);
	}

	if (Button::IsButtonPrssed(creditsButton))
	{
		SceneManager::SetCurrentScene(SceneManager::Credits);
	}

	if (Button::IsButtonPrssed(howToPlayButton))
	{
		SceneManager::SetCurrentScene(SceneManager::HowToPlay);
	}

	if (Button::IsButtonPrssed(exitButton))
	{
		SceneManager::SetCurrentScene(SceneManager::None);
	}


}

void MenuScene::Draw()
{
	DrawText(titlePart1);
	DrawText(titlePart2);

	Button::DrawButton(muteBgm);
	Button::DrawButton(muteSfx);

	Button::DrawButton(singlePlayerButton);
	Button::DrawButton(twoPlayersButton);
	Button::DrawButton(creditsButton);
	Button::DrawButton(howToPlayButton);
	Button::DrawButton(exitButton);
	Text::DrawText(versionText);
}
