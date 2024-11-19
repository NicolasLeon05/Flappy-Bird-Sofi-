#pragma once
#include <iostream>

#include "raylib.h"

using namespace std;

namespace SpritesManager
{
	struct Sprite
	{
		string textureDir;
		Rectangle source;
		Rectangle dest;
		Vector2 origin;
		Texture2D texture;
		float rotation;
		float scale;
	};

	struct AnimatedSprite
	{
		Sprite atlas;
		int frames;
		int fps;		// GetFrameTime() * (frames/fps) = frames
		int xOffSet;
		int frameWidth;
		int currentFrame;
		double updateTime;
		double timer;
		float start;
	};

	const string demon1Sprite = "res/sprites/demon.png";
	const string demon2Sprite = "res/sprites/demon2.png";
	const string obstacleSprite = "res/sprites/pipe.png";

	void AnimateSprite(AnimatedSprite& sprite);

	void DrawAnimatedSprite(AnimatedSprite sprite);

	void DrawSprite(Sprite sprite);

	AnimatedSprite GetAnimatedSprite(Sprite sprite, int framesAmount, int framesPerSecond, int framesSize);

	void InitSprite(SpritesManager::Sprite& sprite);
	void SaveTexture(Texture2D texture, AnimatedSprite& sprite, int framesAmount, int fps);
	void SaveTexture(Texture2D texture, Sprite& sprite);
	void SaveBGTexture(Texture2D texture, Sprite& sprite, float width, float height);
}

