#pragma once

namespace GameplayScene
{
	extern bool isSinglePlayer;
	extern int score;

	void LoadTextures();
	void Unload();
	void Init();
	void Update();
	void Draw();
}
