#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"

namespace GameplayScene
{
	static Player::Player player;
	static Obstacle::Obstacle obstacle;
	static Texture2D demonTexture;

	static void ResetGameplay()
	{
		Player::ResetPlayer(player);
		Obstacle::ResetObstacle(obstacle);
	}

	static bool CheckObstacleColision(Rectangle colisionShape)
	{
		return player.colisionShape.x + player.colisionShape.width >= colisionShape.x &&
			player.colisionShape.x <= colisionShape.x + colisionShape.width &&
			player.colisionShape.y + player.colisionShape.height >= colisionShape.y &&
			player.colisionShape.y <= colisionShape.y + colisionShape.height;
	}

	static void CheckObstacleColision()
	{
		if (CheckObstacleColision(obstacle.higherColisionShape) || CheckObstacleColision(obstacle.lowerColisionShape))
		{
			ResetGameplay();
		}
		else if (player.colisionShape.y + player.colisionShape.height >= screenHeight)
			ResetGameplay();
	}

	void Init()
	{
		player = Player::GetPlayer();
		obstacle = Obstacle::GetObstacle();

	}

	void Update()
	{
		CheckObstacleColision();
		Player::Update(player);
		Obstacle::Update(obstacle);
	}

	void Draw()
	{
		Player::Draw(player);
		Obstacle::Draw(obstacle);
		DrawText("v0.1", 10, 0, 40, GRAY);
	}
}


