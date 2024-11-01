#include "game.h"

#include "raylib.h"

#include "scenes/gameplay_scene.h"
#include "utils/screen_info.h"

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
	}

	static void Update()
	{
		GameplayScene::Update();

	}

	static void Draw()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		GameplayScene::Draw();

		EndDrawing();
	}

	static void Close()
	{
		Unload();
	}

	static bool ShouldWindowClose()
	{
		return WindowShouldClose(); //|| SceneManager::GetCurrentScene() == SceneManager::None;
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


