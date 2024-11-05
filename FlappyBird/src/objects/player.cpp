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

	void SaveTexture(Texture2D texture, Player& player)
	{
		player.sprite.atlas.texture = texture;

		player.sprite.atlas.source.x = 0;
		player.sprite.atlas.source.y = 0;

		player.sprite.atlas.source.width = static_cast<float>(player.sprite.atlas.texture.width / 3);
		player.sprite.atlas.source.height = static_cast<float>(player.sprite.atlas.texture.height);

		player.sprite.atlas.dest.width = player.sprite.atlas.source.width * player.scale;
		player.sprite.atlas.dest.height = player.sprite.atlas.source.height * player.scale;

		player.sprite.atlas.origin = { static_cast<float>(player.sprite.atlas.texture.width),
										static_cast<float>(player.sprite.atlas.texture.height) };

		player.sprite = TextureManager::GetAnimatedSprite(player.sprite.atlas, 3, 30, static_cast<int>(player.sprite.atlas.source.width));
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

		//TextureManager::InitSprite(player.sprite.atlas);

		player.sprite.atlas.textureDir = TextureManager::demonSprite;
		player.angle = 0.0f;


		return player;
	}

	void Update(Player& player)
	{
		MovePlayer(player);
	}

	void Draw(Player& player)
	{
		DrawRectangle(static_cast<int>(player.colisionShape.x), static_cast<int>(player.colisionShape.y), static_cast<int>(player.colisionShape.width), static_cast<int>(player.colisionShape.height), YELLOW);
		//DrawTexturePro(player.sprite.atlas.texture, player.sprite.atlas.source, player.sprite.atlas.dest, player.sprite.atlas.origin, player.angle, WHITE);
		TextureManager::AnimateSprite(player.sprite, player.angle);
	}

}