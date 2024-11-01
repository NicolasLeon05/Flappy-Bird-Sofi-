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
			obstacle.lowerColisionShape.x = screenWidth;
			RandomizeHeight(obstacle);
		}

	}

	void ResetObstacle(Obstacle& obstacle)
	{
		obstacle = GetObstacle();
	}

	Obstacle GetObstacle()
	{
		Obstacle obstacle;

		obstacle.lowerColisionShape.x = screenWidth;
		obstacle.lowerColisionShape.width = 40.0f;
		obstacle.higherColisionShape.width = obstacle.lowerColisionShape.width;
		RandomizeHeight(obstacle);
		obstacle.speed = { 400.0f, 400.0f };

		return obstacle;
	}

	void Update(Obstacle& obstacle)
	{
		MoveObstacle(obstacle);
	}

	void Draw(Obstacle& obstacle)
	{
		DrawRectangle(static_cast<int>(obstacle.lowerColisionShape.x), static_cast<int>(obstacle.lowerColisionShape.y), static_cast<int>(obstacle.lowerColisionShape.width), static_cast<int>(obstacle.lowerColisionShape.height), RED);
		DrawRectangle(static_cast<int>(obstacle.higherColisionShape.x), static_cast<int>(obstacle.higherColisionShape.y), static_cast<int>(obstacle.higherColisionShape.width), static_cast<int>(obstacle.higherColisionShape.height), RED);
	}
}