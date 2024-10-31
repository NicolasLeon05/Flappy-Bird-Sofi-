#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"

namespace GameplayScene
{
	Player::Player player;
	Obstacle::Obstacle obstacle;

	void Init()
	{
		player = Player::GetPlayer();
		obstacle = Obstacle::GetObstacle();

	}

	void Update()
	{
		Player::Update(player);
		Obstacle::Update(obstacle);
	}

	void Draw()
	{
		Player::Draw(player);
		Obstacle::Draw(obstacle);
	}
}


