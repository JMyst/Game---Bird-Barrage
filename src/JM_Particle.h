#pragma once
#include "JM_Vector2D.h"

class JM_Particle
{
public:
	JM_Particle();
	JM_Particle(float x, float y, float height, float width);
	~JM_Particle();
	void Update();
	void Render(SDL_Renderer* aRenderer);

	SDL_Rect Rect;
	JM_Vector2D velocity;
	Uint32 timeout;
	float X, Y, Width, Height;
	bool instantiated = false;

	int maxParticle_X, minParticle_X, maxParticle_Y, minParticle_Y;
};

