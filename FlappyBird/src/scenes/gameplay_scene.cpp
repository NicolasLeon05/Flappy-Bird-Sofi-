#include "scenes/gameplay_scene.h"

#include "objects/player.h"
#include "objects/obstacle.h"
#include "objects/button.h"
#include "objects/parallax_handler.h"
#include "utils/screen_info.h"

namespace GameplayScene
{
	static Player::Player player;
	static Obstacle::Obstacle obstacle;
	static Texture2D demonTexture;
	static Button::Button backButton;
	static Parallax::Parallax parallax;

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

	void Load()
	{
		demonTexture = LoadTexture(SpritesManager::demonSprite.c_str());

		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0004_bg.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0003_far buildings.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0002_3.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0001_buildings.png");
		Parallax::PushBackLayer(parallax, "res/sprites/parallax_bg/industrial-hell_0000_foreground.png");

		Parallax::Load(parallax);
	}

	void Unload()
	{
		UnloadTexture(demonTexture);
		Parallax::Unload(parallax);
	}

	void Init()
	{
		player = Player::GetPlayer();
		obstacle = Obstacle::GetObstacle();
		Player::SaveTexture(demonTexture, player);
		backButton = Button::GetButton(0, screenHeight - static_cast<float>(Text::FontSize::medium), static_cast<float>(Text::Padding::medium), static_cast<float>(Text::FontSize::medium), "BACK", BLACK, RED, WHITE);
	}

	void Update()
	{
		CheckObstacleColision();
		Player::Update(player);
		Obstacle::Update(obstacle);
		Button::CheckSceneChange(backButton, SceneManager::Menu);
		Parallax::Update(parallax);
	}

	void Draw()
	{
		ClearBackground(RAYWHITE);
		Parallax::Draw(parallax);
		Player::Draw(player);
		Obstacle::Draw(obstacle);
		Button::DrawButton(backButton);
	}
}


