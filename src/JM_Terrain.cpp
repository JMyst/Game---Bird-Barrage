#include "SDL.h"
#include "JM_Terrain.h"
#include "SDL_image.h"


JM_Terrain::JM_Terrain()
{
}

JM_Terrain::JM_Terrain(float x, float y, float height, float width)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
}

void JM_Terrain::Init(const char *filename, SDL_Renderer* render)
{
	surface = IMG_Load(filename);
	textureSprite = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	rotation = 0;
}

void JM_Terrain::Render(SDL_Renderer* render)
{
	Rect.x = X;
	Rect.y = Y;
	Rect.w = Width;
	Rect.h = Height;
	SDL_SetRenderDrawColor(render, 10, 10, 15, 255);
	//SDL_RenderFillRect(render, &Rect);
	SDL_RenderCopyEx(render, textureSprite, NULL, &Rect, rotation, NULL, SDL_FLIP_NONE);
}

JM_Terrain::~JM_Terrain()
{
	SDL_DestroyTexture(textureSprite);
}