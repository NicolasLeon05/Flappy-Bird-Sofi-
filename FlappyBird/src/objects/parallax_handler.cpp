#include "objects/parallax_handler.h"

#include "utils/screen_info.h"


namespace Parallax
{
	static float speedMin = 20.0f;
	static float speedMax = 50.0f;

	static void DuplicateSprite(Layer& layer)
	{
		layer.spriteClone = layer.sprite;
		layer.spriteClone.dest.x += layer.sprite.dest.width;
	}

	Parallax parallax;

	//the first one to enter is the background layer.
	void PushBackLayer(string textureDir)
	{
		Layer layer{};

		layer.sprite.textureDir = textureDir;
		SpritesManager::InitSprite(layer.sprite);
		layer.sprite.rotation = 0.0f;
		layer.speed = static_cast<float>(GetRandomValue(static_cast<int>(speedMin), static_cast<int>(speedMax)));
		layer.sprite.scale = 1;

		parallax.parallaxLayers.push_back(layer);
	}

	void Load()
	{
		for (list<Layer>::iterator it = parallax.parallaxLayers.begin(); it != parallax.parallaxLayers.end(); it++)
		{
			(*it).sprite.texture = LoadTexture((*it).sprite.textureDir.c_str());
			SpritesManager::SaveBGTexture((*it).sprite.texture, (*it).sprite, screenWidth, screenHeight);
			(*it).sprite.dest.y = 0.0f;
			(*it).sprite.dest.x = 0.0f;
			DuplicateSprite(*it);
		}
	}

	void Unload()
	{
		for (list<Layer>::iterator it = parallax.parallaxLayers.begin(); it != parallax.parallaxLayers.end(); it++)
			UnloadTexture((*it).sprite.texture);

		parallax.parallaxLayers.clear();
	}

	void Update()
	{
		for (list<Layer>::iterator it = parallax.parallaxLayers.begin(); it != parallax.parallaxLayers.end(); it++)
		{
			(*it).sprite.dest.x -= (*it).speed * GetFrameTime();
			(*it).spriteClone.dest.x -= (*it).speed * GetFrameTime();

			if ((*it).sprite.dest.x <= 0.0f)
				(*it).spriteClone.dest.x = (*it).sprite.dest.x + (*it).sprite.dest.width;

			if ((*it).spriteClone.dest.x <= 0.0f)
				(*it).sprite.dest.x = (*it).spriteClone.dest.x + (*it).spriteClone.dest.width;

		}
	}

	void Draw()
	{
		for (list<Layer>::iterator it = parallax.parallaxLayers.begin(); it != parallax.parallaxLayers.end(); it++)
		{
			SpritesManager::DrawSprite((*it).sprite);
			SpritesManager::DrawSprite((*it).spriteClone);

		}
	}
}
