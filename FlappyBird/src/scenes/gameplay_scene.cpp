#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"
#include "objects/parallax_handler.h"
#include "utils/screen_info.h"
#include "utils/sound_manager.h"
#include "utils/scene_manager.h"

#include <iostream>
#include <string>

namespace GameplayScene
{
	bool isSinglePlayer;

	int score;

	static Player::Player player1;
	static Player::Player player2;

	static Obstacle::Obstacle obstacle;

	static Texture2D demon1Texture;
	static Texture2D demon2Texture;

	static Parallax::Parallax parallax;

	static void ResetGameplay()
	{
		Player::ResetPlayer(player1);

		if (!isSinglePlayer)
			Player::ResetPlayer(player2);

		Obstacle::ResetObstacle(obstacle);
	}

	static bool CheckObstacleColision(Rectangle colisionShape, Player::Player player)
	{
		return player.colisionShape.x + player.colisionShape.width >= colisionShape.x &&
			player.colisionShape.x <= colisionShape.x + colisionShape.width &&
			player.colisionShape.y + player.colisionShape.height >= colisionShape.y &&
			player.colisionShape.y <= colisionShape.y + colisionShape.height;
	}

	static void IsCollidingWithObstacle(Player::Player player)
	{
		if (CheckObstacleColision(obstacle.higherColisionShape, player) || CheckObstacleColision(obstacle.lowerColisionShape, player))
		{
			PlaySound(SoundManager::collideSfx);
			ResetGameplay();
		}
		else if (player.colisionShape.y + player.colisionShape.height >= screenHeight)
			ResetGameplay();
	}

	static void CheckScoreUp()
	{
		if (player1.colisionShape.x > obstacle.higherColisionShape.x + obstacle.higherColisionShape.width &&
			obstacle.scoreGiven == false)
		{
			score++;
			obstacle.scoreGiven = true;
		}
	}

	static void JumpPlayer1()
	{
		if (IsKeyPressed(KEY_SPACE) && (player1.colisionShape.y > 0))
		{
			Player::Jump(player1);
			PlaySound(SoundManager::jumpSfx);
		}
	}

	static void JumpPlayer2()
	{
		if (IsMouseButtonPressed(0) && (player2.colisionShape.y > 0))
		{
			Player::Jump(player2);
			PlaySound(SoundManager::jumpSfx);
		}
	}

	static void CheckTopCollision(Player::Player& player)
	{
		if (player.colisionShape.y - player.colisionShape.height / 2 <= 0)
		{
			player.colisionShape.y = player.colisionShape.height / 2;
			player.speed.y = 0;
		}
	}

	void LoadTextures()
	{
		demon1Texture = LoadTexture(SpritesManager::demon1Sprite.c_str());
		if (!isSinglePlayer)
			demon2Texture = LoadTexture(SpritesManager::demon2Sprite.c_str());

		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0004_bg.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0003_far buildings.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0002_3.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0001_buildings.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0000_foreground.png");

		Parallax::Load(parallax);
	}

	void Unload()
	{
		Parallax::Unload(parallax);

		UnloadTexture(demon1Texture);
		if (!isSinglePlayer)
			UnloadTexture(demon2Texture);
	}

	void Init()
	{
		score = 0;

		player1 = Player::GetPlayer();
		Player::SaveTexture(demon1Texture, player1);

		if (!isSinglePlayer)
		{
			player2 = Player::GetPlayer();
			Player::SaveTexture(demon2Texture, player2);
		}

		obstacle = Obstacle::GetObstacle();
	}

	void Update()
	{
		//Player 1
		Player::Update(player1);
		JumpPlayer1();
		IsCollidingWithObstacle(player1);
		CheckTopCollision(player1);

		
		//Player 2
		if (!isSinglePlayer)
		{
			Player::Update(player2);
			JumpPlayer2();
			IsCollidingWithObstacle(player2);
			CheckTopCollision(player2);
		}

		//Obstacle
		Obstacle::Update(obstacle);

		//Back button
		if (IsKeyReleased(KEY_ESCAPE))
		{
			SceneManager::SetCurrentScene(SceneManager::Menu);
		}

		CheckScoreUp();

		Parallax::Update(parallax);
	}

	void Draw()
	{
		ClearBackground(RAYWHITE);
		Parallax::Draw(parallax);

		Player::Draw(player1);
		if (!isSinglePlayer)
			Player::Draw(player2);

		Obstacle::Draw(obstacle);

		DrawText((to_string(score)).c_str(),
			30,
			30,
			30,
			RED);
	}
}


