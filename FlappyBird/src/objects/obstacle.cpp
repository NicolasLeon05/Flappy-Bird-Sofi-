#include "obstacle.h"

#include "utils/screen_info.h"

namespace Obstacle
{
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
			obstacle.colisionShape.y = static_cast<int>(SizeValues::small);
			break;

		case Size::medium:
			obstacle.colisionShape.y = static_cast<int>(SizeValues::medium);
			break;

		case Size::big:
			obstacle.colisionShape.y = static_cast<int>(SizeValues::big);
			break;

		default:
			break;
		}

		obstacle.colisionShape.height = screenHeight - obstacle.colisionShape.y;
	}

	static void MoveObstacle(Obstacle& obstacle)
	{
		if (obstacle.colisionShape.x + obstacle.colisionShape.width > 0)
		{
			obstacle.colisionShape.x -= obstacle.speed.x * GetFrameTime();
		}
		else
		{
			obstacle.colisionShape.x = screenWidth;
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

		obstacle.colisionShape.x = screenWidth;
		obstacle.colisionShape.width = 40.0f;
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
		DrawRectangle(static_cast<int>(obstacle.colisionShape.x), static_cast<int>(obstacle.colisionShape.y), static_cast<int>(obstacle.colisionShape.width), static_cast<int>(obstacle.colisionShape.height), GREEN);
	}
}