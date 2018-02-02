#pragma once
#include <vector>
#include <time.h>
#include "SDL.h"
#include "JM_EnemyParticle.h"

class ParticleEffects
{
private:
	std::vector<JM_EnemyParticle*> particles;
	std::vector<float> lifetime;
public:
	ParticleEffects();
	ParticleEffects(float x, float y, float height, float width);
	~ParticleEffects();

	void Update();
	void Render(SDL_Renderer* aRenderer);
	void Emit(float scale, float lifetimes);

	float X, Y, Width, Height;
	bool emitting = false;
	Uint32 decayTime;
};

