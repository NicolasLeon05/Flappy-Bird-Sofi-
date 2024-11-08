#pragma once
#include "raylib.h"

#include "utils/texture_manager.h"

namespace Player
{
	struct Player
	{
		Vector2 speed;
		Rectangle colisionShape;
		SpritesManager::AnimatedSprite sprite;
	};

	const float playerSize = 32.0f;

	void ResetPlayer(Player& player);

	void SaveTexture(Texture2D texture, Player& player);

	Player GetPlayer();

	void Update(Player& player);

	void Draw(Player& player);


}


