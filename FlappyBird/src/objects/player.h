#pragma once
#include "raylib.h"

namespace Player
{
	struct Player
	{
		Vector2 speed;
		Rectangle colisionShape;
	};

	void ResetPlayer(Player& player);

	Player GetPlayer();

	void Update(Player& player);

	void Draw(Player player);


}


