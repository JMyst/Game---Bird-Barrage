#pragma once

#include "JM_Square.h"
#include "JM_Enemy.h"
#include "SDL_mixer.h""
#include "JM_Menu.h"


class JM_Pickup
{
private:
	SDL_Texture* textureSprite;
	SDL_Surface* surface;
	Mix_Chunk *SOUND_pickup = NULL;
	Mix_Chunk *SOUND_spawnIn = NULL;

public:
	JM_Pickup();
	JM_Pickup(float x, float y, float height, float width, bool rotate, bool armour, int spawningRate);
	~JM_Pickup();
	void Render(SDL_Renderer* aRenderer);
	void Init(const char *filename, const char *soundname, const char *soundSpawn, SDL_Renderer* render);
	void Input(SDL_Event &event);
	void Update(SDL_Renderer* render, JM_Square &player, JM_Enemy &enemy, JM_Enemy &enemy2, JM_Enemy &enemy3, JM_Enemy &enemy4, JM_Enemy &enemy5, JM_Enemy &enemy6, JM_Enemy &robot, JM_Score &score, JM_Menu &menu);
	void spawnIn(JM_Menu &menu);
	void spawnOut();

	SDL_Rect Rect;
	float X, Y, Width, Height, spawnRate;
	int maxPickup_X, maxPickup_Y, minPickup_X, minPickup_Y;
	Uint32 	timeout, randX, randY;
	double rotation;
	bool isInstantiated = false, enableRotation, Armour = false;
};