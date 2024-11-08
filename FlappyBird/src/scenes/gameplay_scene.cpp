#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"
#include "objects/button.h"
#include "objects/parallax_handler.h"
#include "utils/screen_info.h"

namespace GameplayScene
{
	static const float gravity = 1000.0f;
	static const float jump = -gravity / 2.5f;

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

	static void MovePlayer(Player::Player& player)
	{
		if (player.colisionShape.y - player.colisionShape.height / 2 <= 0)
		{
			player.colisionShape.y = player.colisionShape.height / 2;
			player.speed.y = 0;
		}	

		player.speed.y += gravity * GetFrameTime();
		player.colisionShape.y += player.speed.y * GetFrameTime();

		player.sprite.atlas.dest.y = player.colisionShape.y + player.colisionShape.height / 2;
		player.sprite.atlas.dest.x = player.colisionShape.x + player.colisionShape.width * 2;
	}

	static void JumpPlayer1()
	{
		if (IsKeyPressed(KEY_SPACE) && (player1.colisionShape.y > 0))
		{
			player1.speed.y = jump;
		}
	}

	static void JumpPlayer2()
	{
		if (IsMouseButtonPressed(0) && (player2.colisionShape.y > 0))
		{
			player2.speed.y = jump;
		}
	}

	void Load()
	{
		demon1Texture = LoadTexture(SpritesManager::demon1Sprite.c_str());
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
		UnloadTexture(demon1Texture);
		Parallax::Unload(parallax);
	}

	void Init()
	{
		player1 = Player::GetPlayer();
		Player::SaveTexture(demon1Texture, player1);

		player2 = Player::GetPlayer();
		Player::SaveTexture(demon2Texture, player2);

		obstacle = Obstacle::GetObstacle();
		backButton = Button::GetButton(0, screenHeight - static_cast<float>(Text::FontSize::medium), static_cast<float>(Text::Padding::medium), static_cast<float>(Text::FontSize::medium), "BACK", BLACK, RED, WHITE);
	}

	void Update()
	{
		CheckObstacleColision(player1);
		CheckObstacleColision(player2);

		MovePlayer(player1);
		MovePlayer(player2);

		Player::Update(player1);
		Player::Update(player2);

		JumpPlayer1();
		JumpPlayer2();

		Obstacle::Update(obstacle);

		Button::CheckSceneChange(backButton, SceneManager::Menu);
		Parallax::Update(parallax);
	}

	void Draw()
	{
		ClearBackground(RAYWHITE);
		Parallax::Draw(parallax);

		Player::Draw(player1);
		Player::Draw(player2);

		Obstacle::Draw(obstacle);

		Button::DrawButton(backButton);
	}
}


