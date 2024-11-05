#include "game.h"

#include "raylib.h"

#include "scenes/gameplay_scene.h"
#include "scenes/credits_scene.h"
#include "scenes/menu_scene.h"
#include "utils/screen_info.h"
#include "utils/scene_manager.h"

namespace FlappyBird
{
	static void Load()
	{
		GameplayScene::Load();
	}

	static void Unload()
	{
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
			GameplayScene::Update();
			break;

		case SceneManager::Menu:
			MenuScene::Update();
			break;

		case SceneManager::Credits:
			CreditsScene::Update();
			break;
		
		case SceneManager::Result:
			break;
		
		case SceneManager::HowToPlay:
			break;
		
		default:
			break;
		}
	}

	static void Draw()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
			GameplayScene::Draw();
			break;

		case SceneManager::Menu:
			MenuScene::Draw();
			break;

		case SceneManager::Credits:
			CreditsScene::Draw();
			break;

		case SceneManager::Result:
			break;

		case SceneManager::HowToPlay:
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

		while (!ShouldWindowClose())
		{
			/*if ((previousScene == SceneManager::Result || (previousScene == SceneManager::Gameplay) &&
				SceneManager::GetCurrentScene() != SceneManager::Result) &&
				SceneManager::GetCurrentScene() != SceneManager::Gameplay)
			{
				restart = true;
				previousScene = SceneManager::None;
			}*/

			//if (restart)
			//{

			//Init();

			/*	restart = false;
			}*/

			Update();
			Draw();
		}

		Close();
	}
}


