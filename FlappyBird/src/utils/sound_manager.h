#pragma once
#include "raylib.h"

namespace SoundManager
{
	extern bool isMusicMuted;
	extern bool isSfxMuted;

	extern Music currentBgm;

	extern Music menuBgm;
	extern Music gameplayBgm;

	extern Sound jumpSfx;
	extern Sound collideSfx;
	extern Sound scoreUpSfx;
	extern Sound gameOverSfx;
	extern Sound clickButtonSfx;

	void Load();
	void Unload();
	void MuteMusic();
	void MuteSounds();

}