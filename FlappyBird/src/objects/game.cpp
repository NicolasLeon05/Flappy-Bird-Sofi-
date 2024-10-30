#include "game.h"

#include "raylib.h"

namespace FlappyBird
{
	static void Load()
	{

	}

	static void Unload()
	{

	}

	static void Init()
	{

	}

	static void Update()
	{

	}

	static void Draw()
	{

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
		InitWindow(1024, 768, "Flappy Game");
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

			Init();

			/*	restart = false;
			}*/

			Update();
			Draw();
		}

		Close();
	}
}


