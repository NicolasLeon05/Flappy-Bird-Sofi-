#pragma once

namespace GameplayScene
{
	extern bool isSinglePlayer;

	void LoadTextures();
	void Unload();
	void Init();
	void Update();
	void Draw();
	void ResetGameplay();
}
