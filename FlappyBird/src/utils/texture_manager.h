#pragma once
#include <iostream>

#include "raylib.h"

using namespace std;

namespace TextureManager
{
	struct Sprite
	{
		string textureDir;
		Rectangle source;
		Rectangle dest;
		Vector2 origin;
		Texture2D texture;
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

	const string demonSprite = "res/sprites/demon.png";
	void AnimateSprite(AnimatedSprite& sprite, float rotation);

	AnimatedSprite GetAnimatedSprite(Sprite sprite, int framesAmount, int framesPerSecond, int framesSize);

	void InitSprite(TextureManager::Sprite& sprite);
}

