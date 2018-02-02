#include <string>

#include "JM_Score.h"
#include "SDL.h"


JM_Score::JM_Score()
{
}

JM_Score::JM_Score(SDL_Window* window, const char* _text)
{
	s = std::to_string(scoreCount);
	text = new ScreenText(window, _text);
	text->setColor(255, 255, 255);
	text->setText(s, 340, -12, 80);
	scoreText = new ScreenText(window, _text);
	scoreText->setColor(255, 255, 255);
	scoreText->setText("SCORE:", 180, 15, 45);
}

void JM_Score::infoPanel(SDL_Window* window, const char* _text)
{
	name = new ScreenText(window, _text);
	module = new ScreenText(window, _text);
	number = new ScreenText(window, _text);
	gameName = new ScreenText(window, _text);
	name->setColor(0, 40, 255);
	module->setColor(255, 255, 255);
	number->setColor(255, 255, 255);
	gameName->setColor(255, 255, 255);
	name->setText("Jozef Mystkowski", 10, 10, 40);
	module->setText("Module: CGP2011M", 10, 40, 40);
	number->setText("Student number: 16604277", 10, 70, 40);
	gameName->setText("Game: Bird Barrage", 10, 100, 40);
	name->render();
	module->render();
	number->render();
	gameName->render();
}

void JM_Score::addScore(int score)
{
	scoreCount = scoreCount + score;
	s = std::to_string(scoreCount);
	text->setText(s, 340, -12, 80);
}

void JM_Score::Render(SDL_Renderer* aRenderer)
{
	scoreText->render();
	text->render();
}

void JM_Score::infoRender(SDL_Renderer* aRenderer)
{
	name->render();
	module->render();
	number->render();
	gameName->render();
}

void JM_Score::serialise(const std::string& path) const
{
	std::ofstream outStream;
	std::ifstream inStream;
	outStream.open(path, std::ios::out);
	json outObject;
	outObject["scorecount"] = this->scoreCount;
	outObject["stringcount"] = this->s;
	outStream << outObject.dump(2);
	printf("\n\nSERIALISING\n\n");
	outStream.close();
}

void JM_Score::serialiseAudio(const std::string& path, const JM_Menu &menu) const
{
	std::ofstream outStream;
	std::ifstream inStream;
	outStream.open(path, std::ios::out);
	json outObject;
	outObject["audiomuted"] = menu.audioMuted;
	outStream << outObject.dump(1);
	printf("\n\nSERIALISING AUDIO\n\n");
	outStream.close();
}

void JM_Score::deserialise(const std::string& path)
{
	std::ifstream inStream;
	inStream.open(path, std::ios::in);
	json j;
	inStream >> j;
	this->scoreCount = j["scorecount"].get<int>();
	this->s = j["stringcount"].get<std::string>();
	printf("\n\nDESERIALISING\n\n");
	text->setText(s, 340, -12, 80);
	text->render();
	inStream.close();
}

void JM_Score::deserialiseAudio(const std::string& path, JM_Menu &menu)
{
	std::ifstream inStream;
	inStream.open(path, std::ios::in);
	json j;
	inStream >> j;
	menu.audioMuted = j["audiomuted"].get<bool>();
	printf("\n\nDESERIALISING AUDIO\n\n");
	if(menu.audioMuted)
	menu.menuItems[3]->setText("UNMUTE AUDIO", 100, 300, 70);
	inStream.close();
}

JM_Score::~JM_Score()
{
	delete text;
	delete scoreText;
	delete name;
	delete module;
	delete number;
	delete gameName;
}