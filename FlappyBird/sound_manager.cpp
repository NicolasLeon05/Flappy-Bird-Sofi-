#include "sound_manager.h"

namespace SoundManager
{
	Music menuMusic;
	Music gameplayMusic;

	Sound jumpSound;
	Sound collideSound;
	Sound scoreUpSound;
	Sound gameOverSound;
	Sound clickButtonSound;

	void Load()
	{
		InitAudioDevice();
		menuMusic = LoadMusicStream("res/bgm/gameplay_bgm.mp3");
		gameplayMusic = LoadMusicStream("res/bgm/menu_bgm.mp3");

		jumpSound = LoadSound("res/sfx/jump.wav");
		SetSoundVolume(jumpSound, 0.3f);

		collideSound = LoadSound("res/sfx/collide.wav");
		SetSoundVolume(collideSound, 0.3f);

		scoreUpSound = LoadSound("res/sfx/score_up.wav");
		SetSoundVolume(scoreUpSound, 0.3f);

		gameOverSound = LoadSound("res/sfx/game_over.wav");
		SetSoundVolume(gameOverSound, 1.0f);

		clickButtonSound = LoadSound("res/sfx/click_button.wav");
		SetSoundVolume(clickButtonSound, 1.5f);
	}

	void Unload()
	{
		UnloadMusicStream(menuMusic);
		UnloadMusicStream(gameplayMusic);

		UnloadSound(jumpSound);
		UnloadSound(collideSound);
		UnloadSound(scoreUpSound);
		UnloadSound(gameOverSound);
		UnloadSound(clickButtonSound);

		CloseAudioDevice();
	}
}