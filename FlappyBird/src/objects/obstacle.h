#pragma once

#include "raylib.h"

#include <utils/texture_manager.h>

namespace Obstacle
{
	struct Obstacle
	{
		SpritesManager::Sprite lowerSprite;
		SpritesManager::Sprite higherSprite;

		Vector2 speed;

		Rectangle lowerColisionShape;
		Rectangle higherColisionShape;
		bool scoreGiven;
	};

	void ResetObstacle(Obstacle& obstacle);
	Obstacle GetObstacle(SpritesManager::Sprite sprite);

	void Update(Obstacle& obstacle, bool difficultyUp);
	void Draw(Obstacle& obstacle);
}