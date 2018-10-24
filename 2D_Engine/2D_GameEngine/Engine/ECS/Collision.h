#pragma once
#include <SDL.h>

class Collision
{
public :
	// Access and allign bounding box
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
};