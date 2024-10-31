#include "scenes/gameplay_scene.h"

#include "objects/player.h"

namespace GameplayScene
{
	Player::Player player;

	void Init()
	{
		player = Player::GetPlayer();
	}

	void Update()
	{
		Player::Update(player);
	}

	void Draw()
	{
		Player::Draw(player);
	}
}


