#include "sound_manager.h"

namespace SoundManager
{
	Music currentBgm;

	Music menuBgm;
	Music gameplayBgm;

	Sound jumpSfx;
	Sound collideSfx;
	Sound scoreUpSfx;
	Sound gameOverSfx;
	Sound clickButtonSfx;

	void Load()
	{
		InitAudioDevice();
		menuBgm = LoadMusicStream("res/bgm/menu_bgm.mp3");
		SetMusicVolume(menuBgm, 0.5f);

		gameplayBgm = LoadMusicStream("res/bgm/gameplay_bgm.mp3");
		SetMusicVolume(gameplayBgm, 0.5f);


		jumpSfx = LoadSound("res/sfx/jump.wav");
		SetSoundVolume(jumpSfx, 0.2f);

		collideSfx = LoadSound("res/sfx/collide.wav");
		SetSoundVolume(collideSfx, 0.3f);

		scoreUpSfx = LoadSound("res/sfx/score_up.wav");
		SetSoundVolume(scoreUpSfx, 0.3f);

		gameOverSfx = LoadSound("res/sfx/game_over.wav");
		SetSoundVolume(gameOverSfx, 1.0f);

		clickButtonSfx = LoadSound("res/sfx/click_button.wav");
		SetSoundVolume(clickButtonSfx, 1.0f);
	}
	void Unload()
	{
		UnloadMusicStream(menuBgm);
		UnloadMusicStream(gameplayBgm);

		UnloadSound(jumpSfx);
		UnloadSound(collideSfx);
		UnloadSound(scoreUpSfx);
		UnloadSound(gameOverSfx);
		UnloadSound(clickButtonSfx);

		CloseAudioDevice();
	}
}