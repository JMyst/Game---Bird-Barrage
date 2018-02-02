#include <iostream>
#include "SDL.h"
#include "JM_Pickup.h"
#include "SDL_image.h"

JM_Pickup::JM_Pickup()
{

}

JM_Pickup::JM_Pickup(float x, float y, float width, float height, bool rotate, bool armour, int spawningRate)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	rotation = 0;
	enableRotation = rotate;
	spawnRate = spawningRate;
	Armour = armour;
}

void JM_Pickup::Render(SDL_Renderer* aRenderer)
{
	if (isInstantiated)
	{
		Rect.x = X;
		Rect.y = Y;
		Rect.w = Width;
		Rect.h = Height;

		if (enableRotation)
		{
			rotation = rotation + 0.5;
		}

		SDL_RenderCopyEx(aRenderer, textureSprite, NULL, &Rect, rotation, NULL, SDL_FLIP_NONE);
	}
}

void JM_Pickup::Init(const char *filename, const char *soundname, const char *spawnSound, SDL_Renderer* render)
{
	surface = IMG_Load(filename);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Warning: Audio has not been found! \n");
	}
	else
	{
		SOUND_pickup = Mix_LoadWAV(soundname);
		Mix_VolumeChunk(SOUND_pickup, 128);
		SOUND_spawnIn = Mix_LoadWAV(spawnSound);
		Mix_VolumeChunk(SOUND_spawnIn, 60);
	}

	textureSprite = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	timeout = SDL_GetTicks() + ((rand() % 100) * spawnRate);
	randY = (rand() % 400) + 100;
	randX = (rand() % 790);
}

void JM_Pickup::Input(SDL_Event &event)
{

}

void JM_Pickup::spawnIn(JM_Menu &menu)
{
	if (!isInstantiated)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
		{
			if(!menu.audioMuted)
			Mix_PlayChannel(0, SOUND_spawnIn, 0);
			X = randX;
			Y = randY;
			isInstantiated = true;
		}
	}
}

void JM_Pickup::spawnOut()
{
	isInstantiated = false;
	X = 200;
	Y = 200;

	timeout = SDL_GetTicks() + ((rand() % 100) * spawnRate);
	randY = (rand() % 400) + 100;
	randX = (rand() % 800);
}

void JM_Pickup::Update(SDL_Renderer* render, JM_Square &player, JM_Enemy &enemy, JM_Enemy &enemy2, JM_Enemy &enemy3, JM_Enemy &enemy4, JM_Enemy &enemy5, JM_Enemy &enemy6, JM_Enemy &robot, JM_Score &score, JM_Menu &menu)
{
	maxPickup_X = X + Width;
	minPickup_X = X;
	maxPickup_Y = Y + Height;
	minPickup_Y = Y;

	if (isInstantiated)
	{
		if (!(maxPickup_X < player.minPlayer_X) && !(minPickup_X > player.maxPlayer_X) && !(maxPickup_Y < player.minPlayer_Y) && !(minPickup_Y > player.maxPlayer_Y))
		{  
			if(!menu.audioMuted)
			Mix_PlayChannel(0, SOUND_pickup, 0);
			printf("Pickup Obtained!");
			if (enableRotation)
			{
				enemy.velocityIncrement = 0;
				enemy2.velocityIncrement = 0;
				enemy3.velocityIncrement = 0;
				enemy4.velocityIncrement = 0;
				enemy5.velocityIncrement = 0;
				enemy6.velocityIncrement = 0;
				robot.velocityIncrement = 0;
			}
			if(Armour == false && enableRotation == false)
			{
				score.addScore(7500);
			}
			if (Armour == true)
			{
				player.surface = IMG_Load("content/PlayerSpriteA.png");
				player.textureSprite = SDL_CreateTextureFromSurface(render, player.surface);
				player.Armour = true;
			}
			spawnOut();
		}
	}
}

JM_Pickup::~JM_Pickup()
{
	SDL_DestroyTexture(textureSprite);
	Mix_FreeChunk(SOUND_pickup);
	Mix_FreeChunk(SOUND_spawnIn);
	Mix_CloseAudio();
}