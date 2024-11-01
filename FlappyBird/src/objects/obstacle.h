#pragma once

#include "raylib.h"

namespace Obstacle
{
	struct Obstacle
	{
		Vector2 speed;
		Rectangle lowerColisionShape;
		Rectangle higherColisionShape;
	};

	void ResetObstacle(Obstacle& obstacle);
	Obstacle GetObstacle();
	void Update(Obstacle& obstacle);
	void Draw(Obstacle& obstacle);
}