#pragma once
#include "JM_Vector2D.h"
#include "JM_Square.h"
#include "JM_Particle.h"
#include "ParticleSystem.h"
#include "ParticleEffects.h"
#include "JM_Score.h"
#include "JM_Menu.h"
#include "SDL_mixer.h""

class JM_Enemy
{
private:
	SDL_Texture* textureSprite;
	SDL_Surface* surface;
	Mix_Chunk *SOUND_destroyed = NULL;
	Mix_Chunk *SOUND_removeArmour = NULL;
public:
	JM_Enemy();
	JM_Enemy(float x, float y, float height, float width, int health, int spawnRate);
	~JM_Enemy();

	void spawnIn();
	void spawnOut();
	void Render(SDL_Renderer* aRenderer);
	void Init(const char *filename, const char *removeArmourSound, const char *destroySound, SDL_Renderer* render);
	void Input(SDL_Event &event);
	void Update(JM_Square &player, std::vector<JM_Particle*> particles, JM_Score& score, SDL_Renderer* render, ParticleEffects &parEffect, JM_Menu &menu);

	SDL_Rect Rect, spriteRect;
	JM_Vector2D velocity;
	float X, Y, Width, Height, playerHeight, maxHealth, Health, spawnRate, velocityIncrement = 0;
	unsigned int calcX = 0, changeTimeMS = 200, numberOfFrames = 2, frameIndex, ticks;
	int maxEnemy_X, maxEnemy_Y, minEnemy_X, minEnemy_Y;
	Uint32 timeout, randY, flipY, despawn;
	double rotation;
	bool isFlipped = false, isInstantiated = false, gameLoss = false;
};
