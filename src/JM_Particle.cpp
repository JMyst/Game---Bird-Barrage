#include "JM_Particle.h"


JM_Particle::JM_Particle()
{
}

JM_Particle::JM_Particle(float x, float y, float height, float width)
{
	X = x;
	Y = y;
	Height = height;
	Width = width;
}

void JM_Particle::Render(SDL_Renderer* aRenderer)
{
	Rect.x = X;
	Rect.y = Y;
	Rect.w = Width;
	Rect.h = Height;
	SDL_SetRenderDrawColor(aRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(aRenderer, &Rect);
}

void JM_Particle::Update()
{
	maxParticle_X = X + Width;
	minParticle_X = X;
	maxParticle_Y = Y + Height;
	minParticle_Y = Y;

	X = X + velocity.X;
	Y = Y + velocity.Y;
}

JM_Particle::~JM_Particle()
{
}
