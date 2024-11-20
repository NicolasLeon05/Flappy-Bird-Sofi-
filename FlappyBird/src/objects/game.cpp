#include "game.h"

#include "raylib.h"

#include "objects/parallax_handler.h"
#include "objects/text.h"
#include "scenes/gameplay_scene.h"
#include "scenes/credits_scene.h"
#include "scenes/menu_scene.h"
#include "scenes/how2play_scene.h"
#include "scenes/result_scene.h"
#include "scenes/pause_menu.h"
#include "utils/screen_info.h"
#include "utils/scene_manager.h"
#include "utils/sound_manager.h"


namespace HellEscape
{
	static void Load()
	{
		Text::LoadFonts();
		SoundManager::Load(); 
		GameplayScene::LoadTextures();
		SoundManager::currentBgm = SoundManager::menuBgm;

		Parallax::PushBackLayer("res/sprites/parallax_bg/industrial-hell_0004_bg.png");
		Parallax::PushBackLayer("res/sprites/parallax_bg/industrial-hell_0003_far-buildings.png");
		Parallax::PushBackLayer("res/sprites/parallax_bg/industrial-hell_0002_3.png");
		Parallax::PushBackLayer("res/sprites/parallax_bg/industrial-hell_0001_buildings.png");
		Parallax::PushBackLayer("res/sprites/parallax_bg/industrial-hell_0000_foreground.png");

		Parallax::Load();
	}

	static void Unload()
	{
		Parallax::Unload();
		SoundManager::Unload();
		GameplayScene::Unload();
		Text::UnloadFonts();
	}

	static void Init()
	{
		GameplayScene::Init();
		MenuScene::Init();
		CreditsScene::Init();
		HowToPlayScene::Init();
		ResultScene::Init();
		PauseScene::Init();
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
			if (!IsMusicStreamPlaying(SoundManager::currentBgm))
			{
				SoundManager::currentBgm = SoundManager::menuBgm;
				PlayMusicStream(SoundManager::currentBgm);
			}
			MenuScene::Update();
			Parallax::Update();
			break;
		}

		case SceneManager::Credits:
		{
			CreditsScene::Update();
			Parallax::Update();
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
			Parallax::Update();
			break;
		}

		case SceneManager::Pause:
		{
			PauseScene::Update();
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
			Parallax::Draw();
			MenuScene::Draw();
			break;

		case SceneManager::Credits:
			ClearBackground(BLACK);
			Parallax::Draw();
			CreditsScene::Draw();
			break;

		case SceneManager::Result:
			GameplayScene::Draw();
			ResultScene::Draw();
			break;

		case SceneManager::HowToPlay:
			ClearBackground(BLACK);
			Parallax::Draw();
			HowToPlayScene::Draw();
			break;

		case SceneManager::Pause:
			GameplayScene::Draw();
			PauseScene::Draw();
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
		InitWindow(screenWidth, screenHeight, "Hell Escape");
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


