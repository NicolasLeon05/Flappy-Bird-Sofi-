#include "obstacle.h"

#include "utils/screen_info.h"
#include "objects/player.h"

namespace Obstacle
{
	static float obstacleSpace = Player::playerSize * 4.0f;

	enum class Size
	{
		small,
		medium,
		big
	};

	enum class SizeValues
	{
		big = screenHeight * 1 / 4,
		medium = screenHeight * 2 / 4,
		small = screenHeight * 3 / 4
	};

	static void RandomizeHeight(Obstacle& obstacle)
	{
		Size size = static_cast<Size>(GetRandomValue(0, static_cast<int>(Size::big)));

		switch (size)
		{
		case Size::small:
			obstacle.lowerColisionShape.y = static_cast<int>(SizeValues::small);
			break;

		case Size::medium:
			obstacle.lowerColisionShape.y = static_cast<int>(SizeValues::medium);
			break;

		case Size::big:
			obstacle.lowerColisionShape.y = static_cast<int>(SizeValues::big);
			break;

		default:
			break;
		}

		obstacle.lowerColisionShape.height = screenHeight - obstacle.lowerColisionShape.y;

		obstacle.higherColisionShape.x = obstacle.lowerColisionShape.x;
		obstacle.higherColisionShape.y = 0;
		obstacle.higherColisionShape.height = screenHeight - obstacle.lowerColisionShape.height - obstacleSpace;

	}

	static void MoveObstacle(Obstacle& obstacle)
	{
		if (obstacle.lowerColisionShape.x + obstacle.lowerColisionShape.width > 0)
		{
			obstacle.lowerColisionShape.x -= obstacle.speed.x * GetFrameTime();
			obstacle.higherColisionShape.x = obstacle.lowerColisionShape.x;
		}
		else
		{
			ResetObstacle(obstacle);
		}

		obstacle.lowerSprite.dest.x = obstacle.lowerColisionShape.x;
		obstacle.lowerSprite.dest.y = obstacle.lowerColisionShape.y;
		obstacle.lowerSprite.dest.width = obstacle.lowerColisionShape.width;
		obstacle.lowerSprite.dest.height = obstacle.lowerColisionShape.height;

		obstacle.higherSprite = obstacle.lowerSprite;

		obstacle.higherSprite.dest.x = obstacle.higherColisionShape.x;
		obstacle.higherSprite.dest.y = obstacle.higherColisionShape.y;
		obstacle.higherSprite.dest.width = obstacle.higherColisionShape.width;
		obstacle.higherSprite.dest.height = obstacle.higherColisionShape.height;
	}

	void ResetObstacle(Obstacle& obstacle)
	{
		obstacle.lowerColisionShape.x = screenWidth;
		obstacle.lowerColisionShape.width = 25.0f;

		obstacle.higherColisionShape.width = obstacle.lowerColisionShape.width;
		RandomizeHeight(obstacle);
		obstacle.scoreGiven = false;
	}

	Obstacle GetObstacle(SpritesManager::Sprite sprite)
	{
		Obstacle obstacle;

		obstacle.lowerSprite.texture = sprite.texture;
		obstacle.higherSprite.texture = sprite.texture;

		obstacle.lowerColisionShape.x = screenWidth;
		obstacle.lowerColisionShape.width = 25.0f;

		obstacle.higherColisionShape.width = obstacle.lowerColisionShape.width;
		RandomizeHeight(obstacle);

		obstacle.lowerSprite.rotation = 0;
		obstacle.higherSprite.rotation = 0;

		obstacle.lowerSprite.dest.x = obstacle.lowerColisionShape.x;
		obstacle.lowerSprite.dest.y = obstacle.lowerColisionShape.y;
		obstacle.lowerSprite.dest.width = obstacle.lowerColisionShape.width;
		obstacle.lowerSprite.dest.height = obstacle.lowerColisionShape.height;


		obstacle.higherSprite.rotation = 180;

		obstacle.higherSprite.dest.x = obstacle.higherColisionShape.x;
		obstacle.higherSprite.dest.y = obstacle.higherColisionShape.y;
		obstacle.higherSprite.dest.width = obstacle.higherColisionShape.width;
		obstacle.higherSprite.dest.height = obstacle.higherColisionShape.height;

		obstacle.speed = { 400.0f, 400.0f };
		obstacle.scoreGiven = false;

		obstacle.lowerSprite.source.width = static_cast<float>(obstacle.lowerSprite.texture.width);
		obstacle.lowerSprite.source.height = static_cast<float>(obstacle.lowerSprite.texture.height);

		return obstacle;
	}

	void Update(Obstacle& obstacle)
	{
		MoveObstacle(obstacle);
	}

	void Draw(Obstacle& obstacle)
	{
		/*DrawRectangle
		(static_cast<int>(obstacle.higherColisionShape.x),
			static_cast<int>(obstacle.higherColisionShape.y),
			static_cast<int>(obstacle.higherColisionShape.width),
			static_cast<int>(obstacle.higherColisionShape.height),
			RED);
			*/

		//std::cout << "Dibujando obstáculo superior: "
		//	<< " X: " << obstacle.higherSprite.dest.x
		//	<< " Y: " << obstacle.higherSprite.dest.y << std::endl;

		//std::cout << "Dibujando obstáculo inferior: "
		//	<< " X: " << obstacle.lowerSprite.dest.x
		//	<< " Y: " << obstacle.lowerSprite.dest.y << std::endl;
		
		SpritesManager::DrawSprite(obstacle.lowerSprite);
		SpritesManager::DrawSprite(obstacle.higherSprite);
	}
}