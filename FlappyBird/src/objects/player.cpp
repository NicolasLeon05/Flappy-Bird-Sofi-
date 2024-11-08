#include "objects/player.h"

#include "utils/screen_info.h"
#include "utils/texture_manager.h"

namespace Player
{
	static void MovePlayer(Player& player)
	{
		if (player.colisionShape.y - player.colisionShape.height / 2 <= 0)
		{
			player.colisionShape.y = player.colisionShape.height / 2;
		}

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

		player.sprite.atlas.dest.y = player.colisionShape.y + player.colisionShape.height / 2;
		player.sprite.atlas.dest.x = player.colisionShape.x + player.colisionShape.width * 2;
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

		player.sprite.atlas.scale = 2;
		player.speed = { 0.0f, 0.0f };
		player.colisionShape.x = static_cast<float>(screenWidth) * 1 / 3;
		player.colisionShape.y = static_cast<float>(screenHeight) / 2.0f;
		player.colisionShape.width = playerSize;
		player.colisionShape.height = player.colisionShape.width;

		//TextureManager::InitSprite(player.sprite.atlas);

		player.sprite.atlas.textureDir = SpritesManager::demonSprite;
		player.sprite.atlas.rotation = 0.0f;

		player.sprite.fps = 30;
		player.sprite.frames = 3;


		return player;
	}

	void SaveTexture(Texture2D texture, Player& player)
	{
		SpritesManager::SaveTexture(texture, player.sprite, player.sprite.frames, player.sprite.fps);
	}

	void Update(Player& player)
	{
		MovePlayer(player);
		SpritesManager::AnimateSprite(player.sprite);
	}

	void Draw(Player& player)
	{
		//DrawRectangle(static_cast<int>(player.colisionShape.x), static_cast<int>(player.colisionShape.y), static_cast<int>(player.colisionShape.width), static_cast<int>(player.colisionShape.height), YELLOW);
		//DrawTexturePro(player.sprite.atlas.texture, player.sprite.atlas.source, player.sprite.atlas.dest, player.sprite.atlas.origin, player.angle, WHITE);
		SpritesManager::DrawAnimatedSprite(player.sprite);
	}

}