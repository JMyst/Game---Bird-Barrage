#include "ParticleEffects.h"


ParticleEffects::ParticleEffects()
{
}

ParticleEffects::ParticleEffects(float x, float y, float height, float width)
{
	X = x;
	Y = y;
	particles = std::vector<JM_EnemyParticle*>();
	lifetime = std::vector<float>();
	srand(time(NULL));
}

void ParticleEffects::Update()
{
	for (int i = 0; i < particles.size(); i++)
	{
		lifetime[i] -= 0.001f;
		if (lifetime[i] < 0.0f)
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
			lifetime.erase(lifetime.begin() + i);
		}
		else
		{
			//particles[i]->velocity.Y += 0.01f;
			//particles[i]->velocity.X
			particles[i]->Update();
		}
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), decayTime))
	{
		emitting = false;
	}
}

void ParticleEffects::Render(SDL_Renderer* aRenderer)
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Render(aRenderer);
	}
}

void ParticleEffects::Emit(float scale, float lifetimes)
{
	if (emitting == true)
	{
		//float randomXVel = ((1.0f / (float)(rand() % 101)) - 0.3f) * 0.1f;
		//float randomYVel = ((1.0f / (float)(rand() % 101)) - 0.3f) * 0.1f;
		float randomXVel = (rand() % 201);
		randomXVel = (randomXVel - 100) / 100;
		float randomYVel = (rand() % 201);
		randomYVel = (randomYVel - 100) / 100;

		JM_EnemyParticle* particle = new JM_EnemyParticle(X, Y, scale, scale);
		particle->velocity.X = randomXVel;
		particle->velocity.Y = randomYVel;


		particles.push_back(particle);
		lifetime.push_back(lifetimes);
	}

}

ParticleEffects::~ParticleEffects()
{
}
