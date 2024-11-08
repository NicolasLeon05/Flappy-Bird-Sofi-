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

	void PushBackLayer(Parallax& parallax, string textureDir);

	void Load(Parallax& parallax);

	void Unload(Parallax& parallax);

	void Update(Parallax& parallax);

	void Draw(Parallax parallax);

}