#include "sound_manager.h"

namespace SoundManager
{
	static bool isMute;

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
		isMute = false;

		InitAudioDevice();
		menuBgm = LoadMusicStream("res/bgm/menu_bgm.mp3");
		SetMusicVolume(menuBgm, 0.6f);

		gameplayBgm = LoadMusicStream("res/bgm/gameplay_bgm.mp3");
		SetMusicVolume(gameplayBgm, 0.6f);


		jumpSfx = LoadSound("res/sfx/jump.wav");
		SetSoundVolume(jumpSfx, 0.2f);

		collideSfx = LoadSound("res/sfx/collide.wav");
		SetSoundVolume(collideSfx, 0.3f);

		scoreUpSfx = LoadSound("res/sfx/score_up.wav");
		SetSoundVolume(scoreUpSfx, 0.3f);

		gameOverSfx = LoadSound("res/sfx/game_over.wav");
		SetSoundVolume(gameOverSfx, 0.5f);

		clickButtonSfx = LoadSound("res/sfx/click_button.wav");
		SetSoundVolume(clickButtonSfx, 0.7f);
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

	void Mute()
	{
		SetMusicVolume(menuBgm, 0.0f);
		SetMusicVolume(gameplayBgm, 0.0f);
		SetSoundVolume(jumpSfx, 0.0f);
		SetSoundVolume(collideSfx, 0.0f);
		SetSoundVolume(scoreUpSfx, 0.0f);
		SetSoundVolume(gameOverSfx, 0.0f);
		SetSoundVolume(clickButtonSfx, 0.0f);
	}

	void Unmute()
	{
		SetMusicVolume(menuBgm, 0.6f);
		SetMusicVolume(gameplayBgm, 0.6f);
		SetSoundVolume(jumpSfx, 0.2f);
		SetSoundVolume(collideSfx, 0.3f);
		SetSoundVolume(scoreUpSfx, 0.3f);
		SetSoundVolume(gameOverSfx, 0.5f);
		SetSoundVolume(clickButtonSfx, 0.7f);
	}
}