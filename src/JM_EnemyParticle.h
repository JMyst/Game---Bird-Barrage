#pragma once
#include "JM_Vector2D.h"

class JM_EnemyParticle
{
public:
	JM_EnemyParticle();
	JM_EnemyParticle::JM_EnemyParticle(float x, float y, float height, float width);
	~JM_EnemyParticle();

	void Update();
	void Render(SDL_Renderer* aRenderer);

	SDL_Rect Rect;
	JM_Vector2D velocity;
	float X, Y, Width, Height;
};

