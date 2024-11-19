#include "scenes/how2play_scene.h"

#include "objects/text.h"
#include "objects/button.h"
#include "utils/screen_info.h"

namespace HowToPlayScene
{
	static Text::Text controlsTitle;
	static Text::Text spaceControl;
	static Text::Text leftClickControl;
	static Text::Text objectiveTitle;
	static Text::Text objectiveText;
	static Text::Text specialObstacleText;
	static Button::Button backToMenuButton;

	void Init()
	{

		controlsTitle = Text::GetText
		(screenWidth / 2,
			static_cast<int>(Text::Padding::medium),
			static_cast<int>(Text::FontSize::medium),
			"CONTROLS",
			WHITE);
		Text::CenterTextX(controlsTitle);

		spaceControl = Text::GetText
		(screenWidth / 2,
			controlsTitle.location.y + static_cast<int>(Text::Padding::medium),
			static_cast<int>(Text::FontSize::small),
			"- Space to jump as player 1 or singleplayer!",
			WHITE);
		Text::CenterTextX(spaceControl);

		leftClickControl = Text::GetText
		(screenWidth / 2,
			spaceControl.location.y + static_cast<int>(Text::Padding::medium),
			static_cast<int>(Text::FontSize::small),
			"- Space to jump as player 2!",
			WHITE);
		Text::CenterTextX(leftClickControl);

		objectiveTitle = Text::GetText
		(screenWidth / 2,
			leftClickControl.location.y + static_cast<int>(Text::Padding::big),
			static_cast<int>(Text::FontSize::medium),
			"OBJECTIVES",
			WHITE);
		Text::CenterTextX(objectiveTitle);

		objectiveText = Text::GetText
		(screenWidth / 2,
			objectiveTitle.location.y + static_cast<int>(Text::Padding::medium),
			static_cast<int>(Text::FontSize::small),
			"- Get as far as you can!",
			WHITE);
		Text::CenterTextX(objectiveText);

		specialObstacleText = Text::GetText
		(screenWidth / 2,
			objectiveText.location.y + static_cast<int>(Text::Padding::medium),
			objectiveText.fontSize,
			"- Once you reach a certain score the obstacles will move up and down!",
			WHITE);
		Text::CenterTextX(specialObstacleText);

		backToMenuButton = Button::GetButton
		(static_cast<float>(Text::Padding::small),
			screenHeight,
			80, 40,
			"BACK",
			BLACK, YELLOW, WHITE);
		backToMenuButton.shape.y -= backToMenuButton.shape.height + static_cast<float>(Text::Padding::small);

	}

	void Update()
	{
		if (Button::IsButtonPrssed(backToMenuButton))
		{
			SceneManager::SetCurrentScene(SceneManager::Menu);
		}
	}

	void Draw()
	{
		Text::DrawText(controlsTitle);
		Text::DrawText(spaceControl);
		Text::DrawText(leftClickControl);
		Text::DrawText(objectiveTitle);
		Text::DrawText(objectiveText);
		Text::DrawText(specialObstacleText);
		Button::DrawButton(backToMenuButton);
	}
}
