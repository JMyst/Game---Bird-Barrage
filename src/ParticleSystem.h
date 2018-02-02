#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "SDL.h"
#include "JM_Particle.h"
#include "JM_Square.h"
#include "JM_Enemy.h"


class ParticleSystem
{
private:
	SDL_Surface* surface;
public:
	std::vector<JM_Particle*> particles;
	SDL_Rect Rect;
	ParticleSystem();
	ParticleSystem(float x, float y, float height, float width);
	~ParticleSystem();
	void Init();
	void Update(JM_Square &player);
	//void Input();
	void add(int x, int y);
	void Render(SDL_Renderer* aRenderer);
	void Input(SDL_Event &event, JM_Square &player);
	float X, Y, Width, Height;
	double rotation;
	SDL_Renderer* render1;
};

