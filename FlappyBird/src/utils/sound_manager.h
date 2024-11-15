#pragma once
#include "raylib.h"

namespace SoundManager
{
	extern Music menuMusic;
	extern Music gameplayMusic;

	extern Sound jumpSound;
	extern Sound collideSound;
	extern Sound scoreUpSound;
	extern Sound gameOverSound;
	extern Sound clickButtonSound;

	void Load();
	void Unload();

}