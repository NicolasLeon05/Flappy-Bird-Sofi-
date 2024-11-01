#include "objects/player.h"

#include "utils/screen_info.h"
#include "utils/texture_manager.h"

namespace Player
{
	static void MovePlayer(Player& player)
	{
		const float gravity = 1000.0f;

		if (IsKeyPressed(KEY_SPACE) && (player.colisionShape.y > 0))
		{
			player.speed.y = -gravity / 2;
		}

		player.speed.y += gravity * GetFrameTime();
		player.colisionShape.y += player.speed.y * GetFrameTime();

		/*if (IsKeyDown(KEY_UP))
		{
			if (player.colisionShape.y > 0)
				player.colisionShape.y -= player.speed.y * GetFrameTime();
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			if (player.colisionShape.y + player.colisionShape.height < screenHeight)
				player.colisionShape.y += player.speed.y * GetFrameTime();
		}*/

	}

	void ResetPlayer(Player& player)
	{
		player.colisionShape.x = static_cast<float>(screenWidth) * 1 / 3;
		player.colisionShape.y = static_cast<float>(screenHeight) / 2.0f;
		player.speed.y = 0;
	}

	Player GetPlayer()
	{
		Player player;

		player.scale = 2;
		player.speed = { 0.0f, 0.0f };
		player.colisionShape.x = static_cast<float>(screenWidth) * 1 / 3;
		player.colisionShape.y = static_cast<float>(screenHeight) / 2.0f;
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