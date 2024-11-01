#pragma once
#include "raylib.h"

namespace Player
{
	struct Player
	{
		Vector2 speed;
		Rectangle colisionShape;
	};

	const float playerSize = 64.0f;

	void ResetPlayer(Player& player);

	Player GetPlayer();

	void Update(Player& player);

	void Draw(Player player);


}


