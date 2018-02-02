#include "JM_EnemyParticle.h"

JM_EnemyParticle::JM_EnemyParticle()
{
}

JM_EnemyParticle::JM_EnemyParticle(float x, float y, float height, float width)
{
	X = x;
	Y = y;
	Height = height;
	Width = width;
}

void JM_EnemyParticle::Render(SDL_Renderer* aRenderer)
{
	Rect.x = X;
	Rect.y = Y;
	Rect.w = Width;
	Rect.h = Height;
	SDL_SetRenderDrawColor(aRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(aRenderer, &Rect);
}

void JM_EnemyParticle::Update()
{
	X = X + velocity.X;
	Y = Y + velocity.Y;
}

JM_EnemyParticle::~JM_EnemyParticle()
{
}
