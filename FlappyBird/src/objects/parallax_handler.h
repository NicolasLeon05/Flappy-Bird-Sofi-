#pragma once

#include <list>

#include "raylib.h"

#include "utils/texture_manager.h"

namespace Parallax
{
	struct Layer
	{
		SpritesManager::Sprite sprite;
		SpritesManager::Sprite spriteClone;
		Vector2 pos;
		float speed;

	};

	struct Parallax
	{
		list<Layer> parallaxLayers;
	};

	extern Parallax parallax;

	void PushBackLayer(string textureDir);

	void Load();

	void Unload();

	void Update();

	void Draw();

}