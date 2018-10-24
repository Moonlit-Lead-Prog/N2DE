#pragma once

#include "Components.h"
#include "../Additions/Vector2.h"

class TransformComponent : public Component
{
public:

	Vector2 position;
	Vector2 velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 1;

	TransformComponent()
	{
		position.x = 32.0f;
		position.y = 32.0f;
	}

	TransformComponent(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int x, int y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		int x = position.x;
		int y = position.y;

		if (y % 32 == 0 && x % 32 == 0)
		{
			velocity.x = 0;
			velocity.y = 0;
		}
	}

};