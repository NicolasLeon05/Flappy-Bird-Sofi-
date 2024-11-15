#pragma once

#include "raylib.h"

namespace Obstacle
{
	struct Obstacle
	{
		Vector2 speed;
		Rectangle lowerColisionShape;
		Rectangle higherColisionShape;
		bool scoreGiven;
	};

	void ResetObstacle(Obstacle& obstacle);
	Obstacle GetObstacle();
	void Update(Obstacle& obstacle);
	void Draw(Obstacle& obstacle);
}