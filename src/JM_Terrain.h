#pragma once

class JM_Terrain
{
private:
	SDL_Texture* textureSprite;
	SDL_Surface* surface;
public:
	JM_Terrain();
	JM_Terrain(float x, float y, float height, float width);
	void Init(const char *filename, SDL_Renderer* render);
	void Render(SDL_Renderer* render);
	~JM_Terrain();

	SDL_Rect Rect;
	float X, Y, Width, Height;
	double rotation;
};

