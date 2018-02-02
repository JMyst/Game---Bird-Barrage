#pragma once
#include <vector>
#include "ScreenText.h"
#include "JM_Terrain.h"

#define STB_TRUETYPE_IMPLEMENTATION
class JM_Menu
{
private:
public:
	JM_Menu();
	void Input(SDL_Event &event);
	void Init(SDL_Window* window, const char* _text);
	void Render(SDL_Renderer* renderer);
	void Update(JM_Terrain &robot);
	void gameOver(SDL_Window *window, const char *_text, SDL_Renderer *render, int score);
	~JM_Menu();

	std::vector<ScreenText*> menuItems;
	ScreenText* gOver;
	ScreenText* yourScore;
	ScreenText* yourScoreValue;
	ScreenText* _continue;
	ScreenText* title;
	std::string s;
	int menuIndex = 0, audioIndex = 1;
	bool audioMuted = false;
};

