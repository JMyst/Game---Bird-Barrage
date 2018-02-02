#include <iostream>
#include <vector>
#include "SDL.h"
#include "ParticleSystem.h"




ParticleSystem::ParticleSystem()
{
	
}

ParticleSystem::ParticleSystem(float x, float y, float height, float width)
{
	X = x;
	Y = y;
	Width = width;
	Height - height;
	rotation = 0;
	srand(time(NULL));
}

void ParticleSystem::Input(SDL_Event &event, JM_Square &player)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (particles[0]->instantiated == false)
			{
				if (!player.isFlipped)
				{
					particles[0]->velocity.X = 2;
				}
				if (player.isFlipped)
				{
					particles[0]->velocity.X = -2;
				}
				particles[0]->X = player.X + (player.Width / 2);
				particles[0]->Y = player.Y + (player.Height / 2);
				particles[0]->timeout = SDL_GetTicks() + 2500;
				particles[0]->instantiated = true;
			}
			else
			{
				if (particles[1]->instantiated == false)
				{
					if (!player.isFlipped)
					{
						particles[1]->velocity.X = 2;
					}
					if (player.isFlipped)
					{
						particles[1]->velocity.X = -2;
					}
					particles[1]->X = player.X + (player.Width / 2);
					particles[1]->Y = player.Y + (player.Height / 2);
					particles[1]->timeout = SDL_GetTicks() + 2500;
					particles[1]->instantiated = true;
				}
			}
		}
	}
}
void ParticleSystem::Init()
{
	for (int i = 0; i < 2; i++)
	{
		float posX = X;
		float posY = Y;
		add(posX, posY);
	}
}

void ParticleSystem::add(int X, int Y)
{
	//float randomXVel = ((rand() % 201) - 100) / 500.0f;
	//float randomYVel = ((rand() % 201) - 100) / 500.0f;
	JM_Particle* aTmpGameItem = new JM_Particle(X, Y, 10, 10);
	//aTmpGameItem->velocity.X = randomXVel;
	//aTmpGameItem->velocity.Y = randomYVel;
	aTmpGameItem->velocity.X = 0;
	aTmpGameItem->velocity.Y = 0;

	this->particles.push_back(aTmpGameItem);
}
void ParticleSystem::Update(JM_Square &player)
{
	for (auto& element : particles)
	{
		if (element->instantiated == true)
		{
			//element->X = element->X + element->velocity.X;
			element->Update();
		}
		if(SDL_TICKS_PASSED(SDL_GetTicks(), element->timeout)) 
		{
			element->instantiated = false;
			element->velocity.X = 0;
			element->X = 5;
			element->Y = 5;
		}
	}
}

void ParticleSystem::Render(SDL_Renderer* aRenderer)
{
	for (auto& element : particles)
	{
		if(element->velocity.X != 0)
		element->Render(aRenderer);
	}
}

ParticleSystem::~ParticleSystem()
{
	for (auto &element : particles)
	{
		delete element;
	}
}
