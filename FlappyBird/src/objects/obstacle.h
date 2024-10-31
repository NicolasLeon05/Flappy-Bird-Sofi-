#pragma once

#include "raylib.h"

namespace Obstacle
{
	struct Obstacle
	{
		Vector2 speed;
		Rectangle colisionShape;
	};

	Obstacle GetObstacle();
	void Update(Obstacle& obstacle);
	void Draw(Obstacle& obstacle);
}