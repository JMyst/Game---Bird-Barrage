#ifndef aSquareFILE
#define aSquareFILE

#include <iostream>
#include "JM_Vector2D.h"

class JM_Square
{
private:
	

public:
	JM_Square();
	JM_Square(float x, float y, float height, float width);
	~JM_Square();
	void Render(SDL_Renderer* aRenderer);
	void Init(const char *filename, SDL_Renderer* render);
	void Input(SDL_Event &event);
	void Update();

	SDL_Surface* surface;
	SDL_Texture* textureSprite;
	SDL_Rect Rect, spriteRect;
	JM_Vector2D velocity;
	float X, Y, Width, Height, playerHeight;
	unsigned int calcX = 0, changeTimeMS = 200, numberOfFrames = 2, frameIndex, ticks;
	int maxPlayer_X, maxPlayer_Y, minPlayer_X, minPlayer_Y;
	double rotation;
	bool KEY_LEFT = false, KEY_RIGHT = false, KEY_UP = false, isFlipped = false, isGrounded = false, isStationary = true, Armour = false, exceedRightX = false, exceedLeftX = false;
};

#endif

