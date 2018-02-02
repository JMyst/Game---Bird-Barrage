#include <stdlib.h>
#include <time.h>

#include "JM_Enemy.h"
#include "SDL_image.h"
#include "SDL.h"

JM_Enemy::JM_Enemy()
{
}

JM_Enemy::JM_Enemy(float x, float y, float height, float width, int health, int spawningRate)
{
	X = x;
	Y = y;
	Height = height;
	Width = width;
	rotation = 0;
	maxHealth = health;
	Health = health;
	spawnRate = spawningRate;
}

void JM_Enemy::Init(const char *filename, const char *removeArmourSound, const char *destroySound, SDL_Renderer* render)
{
	velocity.X = 0;
	velocity.Y = 0;

	surface = IMG_Load(filename);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Warning: Audio has not been found! \n");
	}
	else
	{
		SOUND_destroyed = Mix_LoadWAV(destroySound);
		SOUND_removeArmour = Mix_LoadWAV(removeArmourSound);
		Mix_VolumeChunk(SOUND_destroyed, 60);
		Mix_VolumeChunk(SOUND_removeArmour, 128);
	}

	textureSprite = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
	timeout = SDL_GetTicks() + ((rand() % 100) * spawnRate);
	randY = (rand() % 400) + 100;
	flipY = (rand() % 2);
}

void JM_Enemy::spawnIn()
{
	if (!isInstantiated)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
		{

			if (flipY == 0)
			{
			X = 800;
			velocity.X = -0.5 - velocityIncrement;
			isFlipped = false;
			}
			if (flipY == 1)
			{
				X = -150;
				velocity.X = 0.5 + velocityIncrement;
				isFlipped = true;
			}
			isInstantiated = true;
			Y = randY;
			despawn = SDL_GetTicks() + 8000;
		}
	}
}

void JM_Enemy::Update(JM_Square &player, std::vector<JM_Particle*> particles, JM_Score& score, SDL_Renderer* render, ParticleEffects &parEffect, JM_Menu &menu)
{
	maxEnemy_X = X + Width;
	minEnemy_X = X;
	maxEnemy_Y = Y + Height;
	minEnemy_Y = Y;

	if (isInstantiated == true)
	{

		if (Health == 0 && isInstantiated)
		{
			parEffect.X = X + 45;
			parEffect.Y = Y + 25;
			parEffect.emitting = true;
			parEffect.decayTime = SDL_GetTicks() + 100;
			SDL_Log("\n\nCollision - Enemy Destroyed\n\n");
			spawnOut();
		}

		X = X + velocity.X;
		Y = Y + velocity.Y;

		if (SDL_TICKS_PASSED(SDL_GetTicks(), despawn))
		{
			spawnOut();
		}

		if (!(maxEnemy_X < player.minPlayer_X) && !(minEnemy_X > player.maxPlayer_X) && !(maxEnemy_Y < player.minPlayer_Y) && !(minEnemy_Y > player.maxPlayer_Y))
		{
			if (player.Armour == true)
			{
				printf("\n\nCollision - Armour dropped\n\n");
				if(!menu.audioMuted)
				Mix_PlayChannel(0, SOUND_removeArmour, 0);
				player.Armour = false;
				player.surface = IMG_Load("content/PlayerSprite.png");
				player.textureSprite = SDL_CreateTextureFromSurface(render, player.surface);
				spawnOut();
			}
			else
			{
				printf("\n\nCollision - GAME LOSS\n\n");
				player.X = 10000;
				//Call Collision function - Game loss
				gameLoss = true;
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (!(maxEnemy_X < particles[i]->minParticle_X) && !(minEnemy_X > particles[i]->maxParticle_X) && !(maxEnemy_Y < particles[i]->minParticle_Y) && !(minEnemy_Y > particles[i]->minParticle_Y) && particles[i]->instantiated)
			{
				if(!menu.audioMuted)
				Mix_PlayChannel(0, SOUND_destroyed, 0);
				particles[i]->instantiated = false;
				particles[i]->velocity.X = 0;
				particles[i]->X = 5;
				particles[i]->Y = 5;
				Health--;
				if(Health == 0 && maxHealth == 1)
				score.addScore(500);
				if (Health == 0 && maxHealth == 2)
				score.addScore(2000);
			}
		}
	}
}

void JM_Enemy::spawnOut()
{
	isInstantiated = false;
	velocity.X = 0;
	X = 200;
	Y = 200;
	Health = maxHealth;

	timeout = SDL_GetTicks() + ((rand() % 100) * spawnRate);
	randY = (rand() % 400) + 100;
	flipY = (rand() % 2);
	velocityIncrement = velocityIncrement + 0.05f;
}

void JM_Enemy::Input(SDL_Event &event)
{

}

void JM_Enemy::Render(SDL_Renderer* aRenderer)
{
	if (isInstantiated)
	{
		Rect.x = X;
		Rect.y = Y;
		Rect.w = Width;
		Rect.h = Height;

		ticks = SDL_GetTicks();
		frameIndex = (ticks / changeTimeMS) % numberOfFrames;
		calcX = (27 * frameIndex);

		spriteRect.x = calcX;
		spriteRect.y = 0;
		spriteRect.w = 27;
		spriteRect.h = 16;
		if(isFlipped)
		SDL_RenderCopyEx(aRenderer, textureSprite, &spriteRect, &Rect, rotation, NULL, SDL_FLIP_HORIZONTAL);
		if (!isFlipped)
		SDL_RenderCopyEx(aRenderer, textureSprite, &spriteRect, &Rect, rotation, NULL, SDL_FLIP_NONE);
	}
}

JM_Enemy::~JM_Enemy()
{
	SDL_DestroyTexture(textureSprite);
	Mix_FreeChunk(SOUND_destroyed);
	Mix_FreeChunk(SOUND_removeArmour);
	Mix_CloseAudio();
}
