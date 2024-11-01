#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"

namespace GameplayScene
{
	Player::Player player;
	Obstacle::Obstacle obstacle;

	static void ResetGameplay()
	{
		Player::ResetPlayer(player);
		Obstacle::ResetObstacle(obstacle);
	}

	static void CheckObstacleColision()
	{
		if (player.colisionShape.x + player.colisionShape.width >= obstacle.colisionShape.x &&
			player.colisionShape.x <= obstacle.colisionShape.x + obstacle.colisionShape.width &&
			player.colisionShape.y + player.colisionShape.height >= obstacle.colisionShape.y &&
			player.colisionShape.y <= obstacle.colisionShape.y + obstacle.colisionShape.height) 
		{
			ResetGameplay();

		}
		else if (player.colisionShape.y + player.colisionShape.height >= GetScreenHeight())
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


