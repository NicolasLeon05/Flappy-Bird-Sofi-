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

		player.sprite.dest.y = player.colisionShape.y + player.colisionShape.height / 2;
		player.sprite.dest.x = player.colisionShape.x + player.colisionShape.width;
	}

	void ResetPlayer(Player& player)
	{
		player.colisionShape.x = static_cast<float>(screenWidth) * 1 / 3;
		player.colisionShape.y = static_cast<float>(screenHeight) / 2.0f;
		player.speed.y = 0;
	}

	void SaveTexture(Texture2D texture, Player& player)
	{
		player.sprite.texture = texture;

		player.sprite.source.width = static_cast<float>(player.sprite.texture.width / 2);
		player.sprite.source.height = static_cast<float>(player.sprite.texture.height);

		player.sprite.dest.width = player.sprite.source.width * player.scale;
		player.sprite.dest.height = player.sprite.source.height * player.scale;

		player.sprite.origin = { static_cast<float>(player.sprite.texture.width),static_cast<float>(player.sprite.texture.height) };
	}

	void InitSprite(TextureManager::Sprite& sprite)
	{
		Rectangle sourceRect{};

		sourceRect.x = 0;
		sourceRect.y = 0;

		sprite.source = sourceRect;

		Rectangle destRect{};

		destRect.x = 0;
		destRect.y = 0;

		sprite.dest = destRect;

		Vector2 origin{};

		sprite.origin = origin;

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

		player.sprite.textureDir = TextureManager::demonSprite;
		player.angle = 0.0f;

		return player;
	}

	void Update(Player& player)
	{
		MovePlayer(player);
	}

	void Draw(Player player)
	{
		DrawRectangle(static_cast<int>(player.colisionShape.x), static_cast<int>(player.colisionShape.y), static_cast<int>(player.colisionShape.width), static_cast<int>(player.colisionShape.height), YELLOW);
		DrawTexturePro(player.sprite.texture, player.sprite.source, player.sprite.dest, player.sprite.origin, player.angle, WHITE);

	}

}