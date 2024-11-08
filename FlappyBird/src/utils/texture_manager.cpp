#include "utils/texture_manager.h"

namespace SpritesManager
{
	void AnimateSprite(AnimatedSprite& sprite)
	{
		/*int currentFrame = ((static_cast<int>(GetTime()) - static_cast<int>(sprite.start)) * sprite.fps) % sprite.frameWidth;

		sprite.atlas.source = { static_cast<float>(sprite.frameWidth * currentFrame), 0 };*/

		sprite.timer += GetFrameTime();

		if (sprite.timer >= sprite.updateTime)
		{
			sprite.timer = 0.0f;
			sprite.xOffSet = sprite.currentFrame * sprite.frameWidth;

			sprite.currentFrame++;

			if (sprite.currentFrame > sprite.frames)
			{
				//back to the first frame
				sprite.currentFrame = 0;
			}
		}

		sprite.atlas.source.x = static_cast<float>(sprite.xOffSet);


	}

	void DrawAnimatedSprite(AnimatedSprite sprite)
	{
		DrawSprite(sprite.atlas);
	}

	void DrawSprite(Sprite sprite)
	{
		DrawTexturePro(sprite.texture, sprite.source, sprite.dest, sprite.origin, sprite.rotation, WHITE);
	}

	AnimatedSprite GetAnimatedSprite(Sprite sprite, int framesAmount, int framesPerSecond, int framesSize)
	{
		AnimatedSprite animatedSprite{};

		animatedSprite.atlas = sprite;
		animatedSprite.frames = framesAmount;
		animatedSprite.fps = framesPerSecond;
		animatedSprite.frameWidth = framesSize;
		animatedSprite.start = static_cast<float>(GetTime());
		animatedSprite.xOffSet = 0;
		animatedSprite.updateTime = 1.0f / animatedSprite.fps;
		animatedSprite.timer = 0;
		animatedSprite.currentFrame = 0;

		return animatedSprite;
	}

	void InitSprite(SpritesManager::Sprite& sprite)
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

	void SaveTexture(Texture2D texture, AnimatedSprite& sprite, int framesAmount, int fps)
	{
		SaveTexture(texture, sprite.atlas);

		//correction for the previous function (it overwrites)
		sprite.atlas.source.width = static_cast<float>(sprite.atlas.texture.width / framesAmount);
		sprite.atlas.source.height = static_cast<float>(sprite.atlas.texture.height);
		sprite.atlas.dest.width = sprite.atlas.source.width * sprite.atlas.scale;
		sprite.atlas.dest.height = sprite.atlas.source.height * sprite.atlas.scale;

		sprite = SpritesManager::GetAnimatedSprite(sprite.atlas, framesAmount, fps, static_cast<int>(sprite.atlas.source.width));
	}

	void SaveTexture(Texture2D texture, Sprite& sprite)
	{
		sprite.texture = texture;

		sprite.source.x = 0;
		sprite.source.y = 0;

		sprite.source.width = static_cast<float>(sprite.texture.width);
		sprite.source.height = static_cast<float>(sprite.texture.height);

		sprite.dest.width = sprite.source.width * sprite.scale;
		sprite.dest.height = sprite.source.height * sprite.scale;

		sprite.origin = { static_cast<float>(sprite.texture.width),
										static_cast<float>(sprite.texture.height) };

	}

	void SaveBGTexture(Texture2D texture, Sprite& sprite, float width, float height)
	{
		SaveTexture(texture, sprite);
		sprite.dest.width = width;
		sprite.dest.height = height;

		sprite.origin = { 0,0 };
	}
}

