#include "game.h"

#include "raylib.h"

#include "scenes/gameplay_scene.h"
#include "scenes/credits_scene.h"
#include "scenes/menu_scene.h"
#include "scenes/how2play_scene.h"
#include "scenes/result_scene.h"
#include "utils/screen_info.h"
#include "utils/scene_manager.h"
#include "utils/sound_manager.h"

namespace FlappyBird
{

	static void Load()
	{
		SoundManager::Load(); 
		GameplayScene::LoadTextures();
		SoundManager::currentBgm = SoundManager::menuBgm;
	}

	static void Unload()
	{
		SoundManager::Unload();
		GameplayScene::Unload();
	}

	static void Init()
	{
		GameplayScene::Init();
		MenuScene::Init();
		CreditsScene::Init();
	}

	static void Update()
	{
		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
		{
			GameplayScene::Update();
			break;
		}

		case SceneManager::Menu:
		{
			MenuScene::Update();
			break;
		}

		case SceneManager::Credits:
		{
			CreditsScene::Update();
			break;
		}
		
		case SceneManager::Result:
		{
			ResultScene::Update();
			break;
		}
		
		case SceneManager::HowToPlay:
		{
			HowToPlayScene::Update();
			break;
		}
		
		default:
			break;
		}

		UpdateMusicStream(SoundManager::currentBgm);
	}

	static void Draw()
	{
		BeginDrawing();
		
		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
			GameplayScene::Draw();
			break;

		case SceneManager::Menu:
			ClearBackground(BLACK);
			MenuScene::Draw();
			break;

		case SceneManager::Credits:
			ClearBackground(BLACK);
			CreditsScene::Draw();
			break;

		case SceneManager::Result:
			ClearBackground(BLACK);
			ResultScene::Draw();
			break;

		case SceneManager::HowToPlay:
			ClearBackground(BLACK);
			HowToPlayScene::Draw();
			break;

		default:
			break;
		}

		EndDrawing();
	}

	static void Close()
	{
		Unload();
	}

	static bool ShouldWindowClose()
	{
		return WindowShouldClose() || SceneManager::GetCurrentScene() == SceneManager::None;
	}

	void Play()
	{
		InitWindow(screenWidth, screenHeight, "Flappy Game");
		SetExitKey(KEY_NULL);

		Load();
		Init();
		PlayMusicStream(SoundManager::menuBgm);

		while (!ShouldWindowClose())
		{
			Update();
			Draw();
		}

		Close();
	}
}


