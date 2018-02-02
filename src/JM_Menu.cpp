#include "JM_Menu.h"

JM_Menu::JM_Menu()
{
}

void JM_Menu::Input(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			if ((menuIndex - 1) < 0)
			{
				printf("\nUPKEY PRESSED");
				menuIndex = menuItems.size() - 1;
				printf("\nMenu Index: %i", menuIndex);
			}
			else
			{
				printf("\nUPKEY PRESSED");
				menuIndex--;
				printf("\nMenu Index: %i", menuIndex);
			}
			break;
		case SDLK_DOWN:
			printf("\nDOWNKEY PRESSED");
			menuIndex = (menuIndex + 1) % menuItems.size();
			printf("\nMenu Index: %i", menuIndex);
			break;
		}
	}
}

void JM_Menu::Init(SDL_Window* window, const char* _text)
{
	ScreenText* startText = new ScreenText(window, _text);
	ScreenText* optionsText = new ScreenText(window, _text);
	ScreenText* quitText = new ScreenText(window, _text);
	ScreenText* audioText = new ScreenText(window, _text);
	title = new ScreenText(window, _text);
	startText->setText("START", 100, 150, 70); 
	optionsText->setText("Audio: Medium", 100, 200, 70);
	quitText->setText("QUIT", 100, 250, 70);
	audioText->setText("MUTE AUDIO", 100, 300, 70);
	title->setText("Bird Barrage", 100, 20, 100);
	startText->setColor(0, 40, 255);
	startText->setColor(0, 40, 255);
	optionsText->setColor(255, 255, 255);
	title->setColor(255, 255, 255);
	quitText->setColor(255, 255, 255);
	audioText->setColor(255, 255, 255);
	menuItems.push_back(startText);
	menuItems.push_back(optionsText);
	menuItems.push_back(quitText);
	menuItems.push_back(audioText);
}

void JM_Menu::Update(JM_Terrain &robot)
{
	menuItems[0]->setColor(255, 255, 255);
	menuItems[1]->setColor(255, 255, 255);
	menuItems[2]->setColor(255, 255, 255);
	menuItems[3]->setColor(255, 255, 255);
	menuItems[menuIndex]->setColor(0, 40, 255);
	robot.Y = (menuIndex * 50) - 120;
}

void JM_Menu::gameOver(SDL_Window *window, const char *_text, SDL_Renderer *render, int score)
{
	std::string s = std::to_string(score);
	bool running = true;
	gOver = new ScreenText(window, _text);
	yourScore = new ScreenText(window, _text);
	yourScoreValue = new ScreenText(window, _text);
	_continue = new ScreenText(window, _text);
	yourScore->setColor(255, 255, 255);
	yourScoreValue->setColor(255, 255, 255);
	_continue->setColor(0, 40, 255);
	gOver->setColor(255, 255, 255);
	yourScoreValue->setText(s, 360, 300, 50);
	yourScore->setText("Your Score:", 235, 200, 100);
	gOver->setText("GAMEOVER", 75, 10, 200);
	_continue->setText("Press space to continue", 225, 400, 50);
	while (running)
	{
		SDL_SetRenderDrawColor(render, 10, 10, 15, 255);
		SDL_RenderClear(render);
		gOver->render();
		yourScore->render();
		yourScoreValue->render();
		_continue->render();
		SDL_RenderPresent(render);

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				running = false;
				printf("\nSPACEKEY PRESSED");
			}
		}
	}
}

void JM_Menu::Render(SDL_Renderer* renderer)
{
	for (int i = 0; i < 4; i++)
	{
		menuItems[i]->render();
		title->render();
	}
}

JM_Menu::~JM_Menu()
{
	//delete _continue;
	//delete gOver;
	//delete yourScore;
	//delete yourScoreValue;
	//delete title;
}
