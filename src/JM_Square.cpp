#include <iostream>
#include "SDL.h"
#include "JM_Square.h"
#include "SDL_image.h"

JM_Square::JM_Square()
{

}

JM_Square::JM_Square(float x, float y, float width, float height)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	rotation = 0;
	playerHeight = Y + Height;
}

void JM_Square::Init(const char *filename, SDL_Renderer* render)
{
	velocity.X = 0;
	velocity.Y = 0;

	surface = IMG_Load(filename);
	textureSprite = SDL_CreateTextureFromSurface(render, surface);
}

void JM_Square::Update()
{
	maxPlayer_X = X + Width;
	minPlayer_X = X;
	maxPlayer_Y = Y + Height;
	minPlayer_Y = Y;

	if (KEY_LEFT && !KEY_RIGHT && exceedLeftX == false)
	{
		velocity.X = -0.8;
		isFlipped = true;
		exceedRightX = false;
	}
	if (KEY_RIGHT && !KEY_LEFT && exceedRightX == false)
	{
		velocity.X = 0.8;
		isFlipped = false;
		exceedLeftX = false;
	}

	if (!KEY_LEFT && !KEY_RIGHT) 
	velocity.X = 0;
	if (velocity.Y > -0.8 && KEY_UP)
	velocity.Y = velocity.Y - 0.004;
	if (velocity.Y < 2 && !KEY_UP && isGrounded == false)
	velocity.Y = velocity.Y + 0.004;

	if (X >= 750 && !KEY_LEFT)
	{
		exceedRightX = true;
		velocity.X = 0;
	}
	if (X <= 0 && !KEY_RIGHT)
	{
		exceedLeftX = true;
		velocity.X = 0;
	}

	X = X + velocity.X;
	Y = Y + velocity.Y;
	playerHeight = Y + Height;

	if (Y <= 85)
	{
		velocity.Y = 0;
	}
	if (playerHeight >= 550)
	{
		velocity.Y = 0;
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}
	if (velocity.X == 0 && isGrounded)
	{
		isStationary = true;
	}
	else
	{
		isStationary = false;
	}
}

void JM_Square::Input(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			KEY_RIGHT = true;
			break;
		case SDLK_LEFT:
			KEY_LEFT = true;
			break;
		case SDLK_UP:
			KEY_UP = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			KEY_RIGHT = false;
			break;
		case SDLK_LEFT:
			KEY_LEFT = false;
			break;
		case SDLK_UP:
			KEY_UP = false;
			break;
		}
	}
}

void JM_Square::Render(SDL_Renderer* render)
{
	Rect.x = X;
	Rect.y = Y;
	Rect.w = Width;
	Rect.h = Height;

	ticks = SDL_GetTicks();
	frameIndex = (ticks / changeTimeMS) % numberOfFrames;
	calcX = (13 * frameIndex);

	if (!isStationary)
	{
		spriteRect.x = calcX;
		spriteRect.y = 0;
		spriteRect.w = 13;
		spriteRect.h = 18;
	}

	if (isStationary)
	{
		spriteRect.x = 0;
		spriteRect.y = 0;
		spriteRect.w = 13;
		spriteRect.h = 18;
	}
	if (!isGrounded)
	{
		spriteRect.x = 0;
		spriteRect.y = 18;
		spriteRect.w = 13;
		spriteRect.h = 18;
	}
	if(isFlipped)
	SDL_RenderCopyEx(render, textureSprite, &spriteRect, &Rect, rotation, NULL, SDL_FLIP_HORIZONTAL);
	if (!isFlipped)
	SDL_RenderCopyEx(render, textureSprite, &spriteRect, &Rect, rotation, NULL, SDL_FLIP_NONE);

}

JM_Square::~JM_Square()
{
	//This is commented because
	//Un-commenting this gives access errors!
	SDL_DestroyTexture(textureSprite);
	SDL_FreeSurface(surface);
}

