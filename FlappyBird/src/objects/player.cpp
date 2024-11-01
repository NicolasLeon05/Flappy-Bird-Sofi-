#include "objects/player.h"

namespace Player
{
	static void MovePlayer(Player& player)
	{
		if (IsKeyDown(KEY_UP))
		{
			if (player.colisionShape.y > 0)
				player.colisionShape.y -= player.speed.y * GetFrameTime();
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			if (player.colisionShape.y + player.colisionShape.height < GetScreenHeight())
				player.colisionShape.y += player.speed.y * GetFrameTime();
		}

	}

	void ResetPlayer(Player& player)
	{
		player = GetPlayer();
	}

	Player GetPlayer()
	{
		Player player;

		player.speed = { 500.0f, 500.0f };
		player.colisionShape.x = static_cast<float>(GetScreenWidth()) * 1 / 3;
		player.colisionShape.y = static_cast<float>(GetScreenHeight()) / 2.0f;
		player.colisionShape.width = playerSize;
		player.colisionShape.height = player.colisionShape.width;

		return player;
	}

	void Update(Player& player)
	{
		MovePlayer(player);
	}

	void Draw(Player player)
	{
		DrawRectangle(static_cast<int>(player.colisionShape.x), static_cast<int>(player.colisionShape.y), static_cast<int>(player.colisionShape.width), static_cast<int>(player.colisionShape.height), YELLOW);
	}

}