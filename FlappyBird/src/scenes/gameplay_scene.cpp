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
	static const int obstacleSpeedUp = 10;

	static float obstaclesDistance = screenWidth / 2;

	static Player::Player player1;
	static Player::Player player2;

	static Obstacle::Obstacle obstacle1;
	static Obstacle::Obstacle obstacle2;

	static Texture2D demon1Texture;
	static Texture2D demon2Texture;

	static Texture2D obstacleTexture;

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

	static bool CheckScoreUp()
	{
		if (player1.colisionShape.x > obstacle1.higherColisionShape.x + obstacle1.higherColisionShape.width &&
			obstacle1.scoreGiven == false)
		{
			obstacle1.scoreGiven = true;
			return true;
		}

		if (player1.colisionShape.x > obstacle2.higherColisionShape.x + obstacle2.higherColisionShape.width &&
			obstacle2.scoreGiven == false)
		{
			obstacle2.scoreGiven = true;
			return true;
		}
		return false;
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

		obstacleTexture = LoadTexture(SpritesManager::obstacleSprite.c_str());
	}

	void Unload()
	{
		Parallax::Unload();

		UnloadTexture(obstacleTexture);

		UnloadTexture(demon1Texture);
		if (!isSinglePlayer)
			UnloadTexture(demon2Texture);
	}

	void Init()
	{
		score = 0;

		player1 = Player::GetPlayer();
		Player::SaveTexture(demon1Texture, player1);

		SpritesManager::SaveTexture(obstacleTexture, obstacle1.higherSprite);
		SpritesManager::SaveTexture(obstacleTexture, obstacle1.lowerSprite);

		SpritesManager::SaveTexture(obstacleTexture, obstacle2.higherSprite);
		SpritesManager::SaveTexture(obstacleTexture, obstacle2.lowerSprite);

		if (!isSinglePlayer)
		{
			player2 = Player::GetPlayer();
			Player::SaveTexture(demon2Texture, player2);
		}

		obstacle1 = Obstacle::GetObstacle(obstacle1.lowerSprite);

		obstacle2 = Obstacle::GetObstacle(obstacle2.lowerSprite);
		obstacle2.higherColisionShape.x += obstaclesDistance;
		obstacle2.lowerColisionShape.x += obstaclesDistance;
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

		if (CheckScoreUp())
		{
			score++;
			if (score >= upDifficultyScore)
			{
				difficultyUp = true;
			}

			if (difficultyUp)
			{
				obstacle1.speed.x += obstacleSpeedUp;
				obstacle2.speed.x += obstacleSpeedUp;
			}
			
		}

		//Obstacle
		Obstacle::Update(obstacle1, difficultyUp);
		Obstacle::Update(obstacle2, difficultyUp);

		//Back
		if (IsKeyReleased(KEY_ESCAPE))
		{
			SceneManager::SetCurrentScene(SceneManager::Pause);
		}

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
		score = 0;
		difficultyUp = false;

		Player::ResetPlayer(player1);
		if (!isSinglePlayer)
			Player::ResetPlayer(player2);

		Obstacle::ResetObstacle(obstacle1);
		Obstacle::ResetObstacleSpeed(obstacle1);

		Obstacle::ResetObstacle(obstacle2);
		Obstacle::ResetObstacleSpeed(obstacle2);

		obstacle2.higherColisionShape.x += obstaclesDistance;
		obstacle2.lowerColisionShape.x += obstaclesDistance;
	}

}


