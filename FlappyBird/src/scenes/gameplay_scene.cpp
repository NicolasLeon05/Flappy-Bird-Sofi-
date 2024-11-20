#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"
#include "objects/Parallax_handler.h"
#include "scenes/result_scene.h"
#include "utils/screen_info.h"
#include "utils/sound_manager.h"
#include "utils/scene_manager.h"

#include <iostream>
#include <string>

namespace GameplayScene
{
	bool isSinglePlayer;
	int score;

	static const int upDifficultyScore = 15;
	static bool difficultyUp;

	static float obstaclesDistance = 400.0f;

	static Player::Player player1;
	static Player::Player player2;

	static Obstacle::Obstacle obstacle1;
	static Obstacle::Obstacle obstacle2;

	static Texture2D demon1Texture;
	static Texture2D demon2Texture;

	static Texture2D higherObstacleTexture;
	static Texture2D lowerObstacleTexture;

	static void Lose()
	{
		PlaySound(SoundManager::gameOverSfx);
		ResultScene::SaveScore(score);
		ResetGameplay();
		SceneManager::SetCurrentScene(SceneManager::Result);
	}

	static bool CheckObstacleColision(Rectangle colisionShape, Player::Player player)
	{
		return player.colisionShape.x + player.colisionShape.width >= colisionShape.x &&
			player.colisionShape.x <= colisionShape.x + colisionShape.width &&
			player.colisionShape.y + player.colisionShape.height >= colisionShape.y &&
			player.colisionShape.y <= colisionShape.y + colisionShape.height;
	}

	static void IsCollidingWithObstacle(Player::Player player, Obstacle::Obstacle obstacle)
	{
		if (CheckObstacleColision(obstacle.higherColisionShape, player) || CheckObstacleColision(obstacle.lowerColisionShape, player))
		{
			PlaySound(SoundManager::collideSfx);
			Lose();

		}
		else if (player.colisionShape.y + player.colisionShape.height >= screenHeight)
		{
			Lose();
		}
	}

	static void CheckScoreUp(Obstacle::Obstacle& obstacle)
	{
		if (player1.colisionShape.x > obstacle.higherColisionShape.x + obstacle.higherColisionShape.width &&
			obstacle.scoreGiven == false)
		{
			score++;
			obstacle.scoreGiven = true;

			if (score >= upDifficultyScore)
				difficultyUp = true;
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

		lowerObstacleTexture = LoadTexture(SpritesManager::obstacleSprite.c_str());
		higherObstacleTexture = LoadTexture(SpritesManager::obstacleSprite.c_str());
	}

	void Unload()
	{
		Parallax::Unload();

		UnloadTexture(higherObstacleTexture);
		UnloadTexture(lowerObstacleTexture);

		UnloadTexture(demon1Texture);
		if (!isSinglePlayer)
			UnloadTexture(demon2Texture);
	}

	void Init()
	{
		score = 0;

		player1 = Player::GetPlayer();
		Player::SaveTexture(demon1Texture, player1);

		SpritesManager::SaveTexture(lowerObstacleTexture, obstacle1.higherSprite);
		SpritesManager::SaveTexture(lowerObstacleTexture, obstacle1.lowerSprite);

		if (!isSinglePlayer)
		{
			player2 = Player::GetPlayer();
			Player::SaveTexture(demon2Texture, player2);
		}

		obstacle1 = Obstacle::GetObstacle(obstacle1.lowerSprite);
		obstacle2 = Obstacle::GetObstacle(obstacle2.lowerSprite);
	}

	void Update()
	{
		//Player 1
		Player::Update(player1);
		JumpPlayer1();
		IsCollidingWithObstacle(player1, obstacle1);
		IsCollidingWithObstacle(player1, obstacle2);
		CheckTopCollision(player1);

		
		//Player 2
		if (!isSinglePlayer)
		{
			Player::Update(player2);
			JumpPlayer2();
			IsCollidingWithObstacle(player2, obstacle1);
			IsCollidingWithObstacle(player2, obstacle2);
			CheckTopCollision(player2);
		}

		//Obstacle
		Obstacle::Update(obstacle1, difficultyUp);
		if (obstacle2.lowerColisionShape.x - obstacle1.lowerColisionShape.x > obstaclesDistance ||
			obstacle1.lowerColisionShape.x - obstacle2.lowerColisionShape.x > obstaclesDistance)
		{
			Obstacle::Update(obstacle2, difficultyUp);
		}

		//Back button
		if (IsKeyReleased(KEY_ESCAPE))
		{
			SceneManager::SetCurrentScene(SceneManager::Pause);
		}

		CheckScoreUp(obstacle1);
		CheckScoreUp(obstacle2);

		Parallax::Update();
	}

	void Draw()
	{
		ClearBackground(RAYWHITE);
		Parallax::Draw();

		Obstacle::Draw(obstacle1);
		Obstacle::Draw(obstacle2);

		Player::Draw(player1);
		if (!isSinglePlayer)
			Player::Draw(player2);


		DrawText((to_string(score)).c_str(),
			30,
			30,
			30,
			RED);
	}

	void ResetGameplay()
	{
		Player::ResetPlayer(player1);
		score = 0;

		if (!isSinglePlayer)
			Player::ResetPlayer(player2);

		Obstacle::ResetObstacle(obstacle1);
		Obstacle::ResetObstacle(obstacle2);
	}

}


