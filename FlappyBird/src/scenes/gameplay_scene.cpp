#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"
#include "objects/button.h"
#include "objects/parallax_handler.h"
#include "utils/screen_info.h"

namespace GameplayScene
{
	bool isSinglePlayer;

	static Player::Player player1;
	static Player::Player player2;

	static Obstacle::Obstacle obstacle;

	static Texture2D demon1Texture;
	static Texture2D demon2Texture;

	static Button::Button backButton;

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

	static void CheckObstacleColision(Player::Player player)
	{
		if (CheckObstacleColision(obstacle.higherColisionShape, player) || CheckObstacleColision(obstacle.lowerColisionShape, player))
		{
			ResetGameplay();
		}
		else if (player.colisionShape.y + player.colisionShape.height >= screenHeight)
			ResetGameplay();
	}

	static void JumpPlayer1()
	{
		if (IsKeyPressed(KEY_SPACE) && (player1.colisionShape.y > 0))
		{
			Player::Jump(player1);
		}
	}

	static void JumpPlayer2()
	{
		if (IsMouseButtonPressed(0) && (player2.colisionShape.y > 0))
		{
			Player::Jump(player2);
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

	void Load()
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
		player1 = Player::GetPlayer();
		Player::SaveTexture(demon1Texture, player1);

		if (!isSinglePlayer)
		{
			player2 = Player::GetPlayer();
			Player::SaveTexture(demon2Texture, player2);
		}

		obstacle = Obstacle::GetObstacle();
		backButton = Button::GetButton(0, screenHeight - static_cast<float>(Text::FontSize::medium), static_cast<float>(Text::Padding::medium), static_cast<float>(Text::FontSize::medium), "BACK", BLACK, RED, WHITE);
	}

	void Update()
	{
		//Player 1
		Player::Update(player1);
		JumpPlayer1();
		CheckObstacleColision(player1);
		CheckTopCollision(player1);

		
		//Player 2
		if (!isSinglePlayer)
		{
			Player::Update(player2);
			JumpPlayer2();
			CheckObstacleColision(player2);
			CheckTopCollision(player2);
		}

		//Obstacle
		Obstacle::Update(obstacle);

		//Back button
		if (Button::IsButtonPrssed(backButton) ||
			IsKeyReleased(KEY_ESCAPE))
		{
			Button::ChangeScene(SceneManager::Menu);
		}

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

		Button::DrawButton(backButton);
	}
}


