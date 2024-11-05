#include "utils/texture_manager.h"

namespace TextureManager
{
	enum class Frames
	{
		first,
		middle,
		last
	};

	void AnimateSprite(AnimatedSprite& sprite, float rotation)
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

		rotation = 45.0f;

		DrawTexturePro(sprite.atlas.texture, sprite.atlas.source, sprite.atlas.dest, sprite.atlas.origin, rotation, WHITE);

	}

	AnimatedSprite GetAnimatedSprite(Sprite sprite, int framesAmount, int framesPerSecond, int framesSize)
	{
		AnimatedSprite animatedSprite{};

		animatedSprite.atlas = sprite;
		animatedSprite.frames = framesAmount;
		animatedSprite.fps = framesPerSecond;		// GetTime() * (frames/fps) = frames
		animatedSprite.frameWidth = framesSize;
		animatedSprite.start = static_cast<float>(GetTime());
		animatedSprite.xOffSet = 0;
		animatedSprite.updateTime = 1.0f / animatedSprite.fps;
		animatedSprite.timer = 0;
		animatedSprite.currentFrame = 0;

		return animatedSprite;
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
}

