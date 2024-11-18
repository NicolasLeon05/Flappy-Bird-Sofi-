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

static Text::Text titlePart1;
static Text::Text titlePart2;
static Text::Text versionText;

void MenuScene::Init()
{
#pragma region TITLE_TEXTS

	titlePart1 = Text::GetText(screenWidth / 2, 0,/* Text::Fonts::Title1,*/ static_cast<int>(Text::FontSize::big), "PLACE", MAGENTA);
	Text::CenterTextX(titlePart1);
	titlePart1.location.y = static_cast<float>(Text::Padding::medium);
	titlePart2 = Text::GetText(screenWidth / 2, titlePart1.location.y + titlePart1.fontSize/**/, static_cast<int>(Text::FontSize::big), "HOLDER", YELLOW);
	Text::CenterTextX(titlePart2);

#pragma endregion

	singlePlayerButton = Button::GetButton
	(static_cast<float>(GetScreenWidth()) / 2.0f - static_cast<float>(Text::GetTextWidth(titlePart2)) / 2.0f,
		static_cast<float>(GetScreenHeight()) / 2.0f - titlePart2.fontSize,
		static_cast<float>(Text::GetTextWidth(titlePart2)),
		static_cast<float>(titlePart2.fontSize) / 2.0f,
		"SINGLE PLAYER",
		BLACK, MAGENTA, WHITE/**/);

	twoPlayersButton = Button::GetButton
	(singlePlayerButton.shape.x,
		singlePlayerButton.shape.y + singlePlayerButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width, singlePlayerButton.shape.height,
		"TWO PLAYERS",
		BLACK, MAGENTA, WHITE /*playButton.textShown.font*/);

	creditsButton = Button::GetButton
	(singlePlayerButton.shape.x,
		twoPlayersButton.shape.y + twoPlayersButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width, singlePlayerButton.shape.height,
		"CREDITS",
		BLACK, SKYBLUE, WHITE /*playButton.textShown.font*/);

	howToPlayButton = Button::GetButton(creditsButton.shape.x, creditsButton.shape.y + creditsButton.shape.height + static_cast<int>(Text::Padding::tiny), singlePlayerButton.shape.width, singlePlayerButton.shape.height, "HOW TO PLAY", BLACK, YELLOW, WHITE /*playButton.textShown.font*/);

	exitButton = Button::GetButton
	(singlePlayerButton.shape.x,
		howToPlayButton.shape.y + howToPlayButton.shape.height + static_cast<int>(Text::Padding::tiny),
		singlePlayerButton.shape.width, singlePlayerButton.shape.height,
		"EXIT",
		BLACK, RED, WHITE/*, playButton.textShown.font*/);


	//Version
	versionText = Text::GetText(static_cast<float>(Text::Padding::tiny),
		static_cast<float>(Text::Padding::tiny),
		static_cast<int>(Text::FontSize::medium),
		"v0.4",
		GRAY);
}


void MenuScene::Update()
{
	if (Button::IsButtonPrssed(singlePlayerButton))
	{		
		GameplayScene::isSinglePlayer = true;
		Button::ChangeScene(SceneManager::Gameplay);
	}

	if (Button::IsButtonPrssed(twoPlayersButton))
	{
		GameplayScene::isSinglePlayer = false;
		Button::ChangeScene(SceneManager::Gameplay);
	}

	if (SceneManager::GetCurrentScene() == SceneManager::Gameplay)
	{
		StopMusicStream(SoundManager::currentBgm);
		SoundManager::currentBgm = SoundManager::gameplayBgm;
		PlayMusicStream(SoundManager::currentBgm);
	}

	if (Button::IsButtonPrssed(creditsButton))
	{
		Button::ChangeScene(SceneManager::Credits);
	}

	if (Button::IsButtonPrssed(howToPlayButton))
	{
		Button::ChangeScene(SceneManager::HowToPlay);
	}

	if (Button::IsButtonPrssed(exitButton))
	{
		Button::ChangeScene(SceneManager::None);
	}


}

void MenuScene::Draw()
{
	DrawText(titlePart1);
	DrawText(titlePart2);

	Button::DrawButton(singlePlayerButton);
	Button::DrawButton(twoPlayersButton);
	Button::DrawButton(creditsButton);
	Button::DrawButton(howToPlayButton);
	Button::DrawButton(exitButton);
	Text::DrawText(versionText);
}
