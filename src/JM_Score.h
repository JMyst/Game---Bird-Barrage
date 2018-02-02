#pragma once

#include <fstream>
#include "JM_Menu.h"
#include "ScreenText.h"
#include "json.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
using json = nlohmann::json;

class JM_Score
{
private:
	ScreenText* text;
	ScreenText* scoreText;
	ScreenText* name;
	ScreenText* module;
	ScreenText* number;
	ScreenText* gameName;
public:
	JM_Score();
	JM_Score(SDL_Window* window, const char* _text);
	~JM_Score();

	void infoPanel(SDL_Window* window, const char* _text);
	void addScore(int score);
	void Render(SDL_Renderer* aRenderer);
	void infoRender(SDL_Renderer* aRenderer);
	void serialise(const std::string& path) const;
	void serialiseAudio(const std::string& path, const JM_Menu &menu) const;
	void JM_Score::deserialise(const std::string& path);
	void JM_Score::deserialiseAudio(const std::string& path, JM_Menu &menu);

	int scoreCount = 0;
	std::string s;
};

