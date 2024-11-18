#include "scenes/how2play_scene.h"

#include "objects/text.h"
#include "objects/button.h"
#include "utils/screen_info.h"

namespace HowToPlayScene
{
	static Text::Text howToPlayTitle;
	static Text::Text controlsTitle;
	static Text::Text spaceControl;
	static Text::Text leftClickControl;
	static Text::Text objectiveTitle;
	static Text::Text objectiveText;
	static Text::Text specialObstacleText;
	static Button::Button backToMenuButton;

	void Init()
	{
		howToPlayTitle = Text::GetText(screenWidth / 2, 
			static_cast<int>(Text::Padding::medium),
			static_cast<int>(Text::FontSize::big), 
			"HOW TO PLAY",
			SKYBLUE);
		Text::CenterTextX(howToPlayTitle);

		controlsTitle = Text::GetText(screenWidth / 2,
			howToPlayTitle.location.y + Text::GetTextHeight(howToPlayTitle) + static_cast<int>(Text::Padding::medium),
			 static_cast<int>(Text::FontSize::big),
			"CONTROLS",
			WHITE);
		Text::CenterTextX(controlsTitle);

		spaceControl = Text::GetText(screenWidth / 2,
			controlsTitle.location.y + Text::GetTextHeight(controlsTitle) + static_cast<int>(Text::Padding::small),
			 static_cast<int>(Text::FontSize::small),
			"- Space to jump as player 1 or singleplayer!",
			WHITE);
		Text::CenterTextX(spaceControl);

		leftClickControl = Text::GetText(screenWidth / 2,
			spaceControl.location.y + Text::GetTextHeight(spaceControl) + static_cast<int>(Text::Padding::tiny), static_cast<int>(Text::FontSize::small),
			"- Space to jump as player 2!",
			WHITE);
		Text::CenterTextX(leftClickControl);

		objectiveTitle = Text::GetText(screenWidth / 2,
			leftClickControl.location.y + Text::GetTextHeight(leftClickControl) + static_cast<int>(Text::Padding::small), static_cast<int>(Text::FontSize::big),
			"OBJECTIVES",
			WHITE);
		Text::CenterTextX(objectiveTitle);

		objectiveText = Text::GetText(screenWidth / 2,
			objectiveTitle.location.y + Text::GetTextHeight(objectiveTitle) + static_cast<int>(Text::Padding::small),
			static_cast<int>(Text::FontSize::small),
			"- Get as far as you can!",
			WHITE);
		Text::CenterTextX(objectiveText);

		specialObstacleText = Text::GetText(screenWidth / 2,
			objectiveText.location.y + Text::GetTextHeight(objectiveText) + static_cast<int>(Text::Padding::small),
			objectiveText.fontSize,
			"- Once you reach a certain score the obstacles will move up and down!",
			WHITE);
		Text::CenterTextX(specialObstacleText);

		backToMenuButton = Button::GetButton(static_cast<float>(Text::Padding::tiny),
			screenHeight, 80, 40, "BACK", BLACK, YELLOW, WHITE);
		backToMenuButton.shape.y -= backToMenuButton.shape.height + static_cast<float>(Text::Padding::tiny);
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
		Text::DrawText(howToPlayTitle);
		Text::DrawText(controlsTitle);
		Text::DrawText(spaceControl);
		Text::DrawText(leftClickControl);
		Text::DrawText(objectiveTitle);
		Text::DrawText(objectiveText);
		Text::DrawText(specialObstacleText);
		Button::DrawButton(backToMenuButton);
	}
}
