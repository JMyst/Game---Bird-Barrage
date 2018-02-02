/**
 * @file   main.cpp
 * @author your_name (your_email)
 * @brief  The main entry point for our simple game.
*/

//C++ Headers
#include <iostream> // functions for printing things out
#include <string>   // functions for strings
#include <ctime>

#define STB_TRUETYPE_IMPLEMENTATION

//Include SDL into our program so we have access to SDL functions
#include "SDL.h"
#include "SDL_mixer.h"
#include "JM_Square.h"
#include "SDL_image.h"
#include "ScreenText.h"
#include "ParticleSystem.h"
#include "ParticleEffects.h"
#include "JM_Vector2D.h"
#include "JM_Particle.h"
#include "JM_Terrain.h"
#include "JM_Pickup.h"
#include "JM_Enemy.h"
#include "JM_Score.h"
#include "JM_Menu.h"

//Window width and window height
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

//Alias -- we don't want to type out std:: all the time!
using namespace std;


char* getTime(void)
{
	time_t currentTime = std::time(0);

	struct tm* info = localtime(&currentTime);

	char* returnString = new char[32]();

	strftime(returnString, 32, "%d/%m/%y %T", info);

	return returnString;
}

int main(int argc, char *argv[])
{
	SDL_Log("Game running");

	//Firstly initialise SDL.. log an error if we can't open it
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//Log an error
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "An error occurred when initialising SDL.. closing..");

		//Return.. exit the program
		return -1;
	}
	IMG_Init(SDL_INIT_EVERYTHING);

	//Create a simple window
	SDL_Window* infoWindow = SDL_CreateWindow("Information", 200, 200, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Window* window = SDL_CreateWindow("Bird Barrage", 200, 200, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* infoRender = SDL_CreateRenderer(infoWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Mix_Music *SOUND_aBckMusic = NULL;
	Mix_Music *SOUND_aBckMusicFast = NULL;

	bool appOpen = true, outerApp = true;
	bool menuRunning = true, running = true;
	bool musicFast = false, useController = false;

	SDL_Joystick* aGamePadController = NULL;
	JM_Vector2D aJoystick;

	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could access Joystick! SDL Error: %s\n", SDL_GetError());
	}
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No GameControllers connected!\n");
	}
	else
	{
		aGamePadController = SDL_JoystickOpen(0);
		printf("GameController connected! \n");
		useController = true;
		if (aGamePadController == NULL)
		{
			printf("Error - %s \n", SDL_GetError());
		}
	}

	while(outerApp)
	{
		JM_Menu menu;
		JM_Square player(370, 400, 50, 70);
		JM_Pickup cherry(200, 200, 25, 25, false, false, 800);
		JM_Pickup hourglass(250, 200, 25, 25, true, false, 3000);
		JM_Pickup armour(250, 200, 25, 25, false, true, 1000);
		JM_Terrain ground(0, 550, 80, 800);
		JM_Terrain background(0, 0, 700, 800);
		JM_Terrain scoreBoard(155, 0, 80, 450);
		JM_Terrain robotBackground(430, 50, 500, 400);
		ParticleSystem pSystem(30, 30, 1.f, 1.f);
		ParticleEffects pEffects(300, 300, 1, 1);
		JM_Enemy enemy(400, 500, 60, 115, 1, 100);
		JM_Enemy enemy2(400, 500, 60, 115, 1, 100);
		JM_Enemy enemy3(400, 500, 60, 115, 1, 100);
		JM_Enemy enemy4(400, 500, 60, 115, 1, 100);
		JM_Enemy enemy5(400, 500, 60, 115, 1, 100);
		JM_Enemy enemy6(400, 500, 60, 115, 1, 100);
		JM_Enemy robot(400, 500, 60, 115, 2, 200);
		JM_Score score(window, "content/advanced_pixel-7.ttf");

		player.Init("content/PlayerSprite.png", render);
		enemy.Init("content/EnemySpriteSheet.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		enemy2.Init("content/EnemySpriteSheet.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		enemy3.Init("content/EnemySpriteSheet.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		enemy4.Init("content/EnemySpriteSheet.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		enemy5.Init("content/EnemySpriteSheet.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		enemy6.Init("content/EnemySpriteSheet.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		robot.Init("content/EnemySpriteSheet2.png", "./content/ArmourRemove.wav", "./content/EnemyDestroy.wav", render);
		cherry.Init("content/Cherry.png", "./content/Cherry.wav", "./content/SpawnIn.wav", render);
		hourglass.Init("content/Hourglass2.png", "./content/Hourglass.wav", "./content/SpawnIn.wav", render);
		armour.Init("content/Armour.png", "./content/Armour.wav", "./content/SpawnIn.wav", render);
		ground.Init("content/Ground.png", render);
		background.Init("content/Background.png", render);
		scoreBoard.Init("content/ScoreBoard.png", render);
		pSystem.Init();

		int frameCount = 0;
		unsigned int currentTime = 0;
		unsigned int lastTime;

		SDL_SetRenderDrawColor(infoRender, 10, 10, 15, 255);
		SDL_RenderClear(infoRender);
		score.infoPanel(infoWindow, "content/advanced_pixel-7.ttf");
		SDL_RenderPresent(infoRender);

		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		menu.Init(window, "content/advanced_pixel-7.ttf");
		robotBackground.Init("content/RobotFace.png", render);

		appOpen = true;
		menuRunning = true;
		running = true;

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			printf("Warning: Audio has not been found! \n");
		}
		else
		{
			SOUND_aBckMusic = Mix_LoadMUS("./content/Music2.wav");
			SOUND_aBckMusicFast = Mix_LoadMUS("./content/MusicFast.wav");
			score.deserialiseAudio("../content/audio.json", menu);
			if (menu.audioMuted)
			{
			Mix_VolumeMusic(0); //The volume for the music (0-255)
			}
			else
			{
			Mix_VolumeMusic(32); //The volume for the music (0-255)
			}
		}

		Mix_PlayMusic(SOUND_aBckMusic, -1);

		while (appOpen)
		{
			while (menuRunning)
			{
				SDL_Event event;

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						running = false;
						menuRunning = false;
						appOpen = false;
						outerApp = false;
					}
					if (event.key.repeat == NULL)
					{
						if (event.type == SDL_KEYDOWN)
						{
							if(menu.menuIndex == 1)
							{ 
								switch (menu.audioIndex)
								{
								case 0:
									if (event.key.keysym.sym == SDLK_SPACE && menu.audioIndex == 0)
									{
										menu.menuItems[1]->setText("Audio: Medium", 100, 200, 70);
										menu.menuItems[3]->setText("MUTE AUDIO", 100, 300, 70);
										printf("\nVolume Medium");
										Mix_VolumeMusic(50);
										menu.audioMuted = false;
										menu.audioIndex = 1;
									}
									break;
								case 1:
									if (event.key.keysym.sym == SDLK_SPACE && menu.audioIndex == 1)
									{
										menu.menuItems[1]->setText("Audio: High", 100, 200, 70);
										menu.menuItems[3]->setText("MUTE AUDIO", 100, 300, 70);
										printf("\nVolume High");
										Mix_VolumeMusic(100);
										menu.audioMuted = false;
										menu.audioIndex = 2;
									}
									break;
								case 2:
									if (event.key.keysym.sym == SDLK_SPACE && menu.audioIndex == 2)
									{
										menu.menuItems[1]->setText("Audio: Low", 100, 200, 70);
										menu.menuItems[3]->setText("MUTE AUDIO", 100, 300, 70);
										printf("\nVolume Low");
										Mix_VolumeMusic(16);
										menu.audioMuted = false;
										menu.audioIndex = 0;
									}
									break;
								}
							}
							if (event.key.keysym.sym == SDLK_SPACE && menu.menuIndex == 0)
							{
								printf("\nSPACEKEY PRESSED");
								menuRunning = false;
								running = true;
							}
							if (event.key.keysym.sym == SDLK_SPACE && menu.menuIndex == 2)
							{
								printf("\nSPACEKEY PRESSED");
								menuRunning = false;
								running = false;
								appOpen = false;
								outerApp = false;
							}
							if (event.key.keysym.sym == SDLK_s)
							{
								score.serialise("../content/score.json");
							}
							if (event.key.keysym.sym == SDLK_d)
							{
								score.deserialise("../content/score.json");
							}
							if (event.key.keysym.sym == SDLK_SPACE && menu.menuIndex == 3 && menu.audioMuted == false)
							{
								printf("\nSPACEKEY PRESSED");
								menu.audioMuted = true;
								Mix_VolumeMusic(0);
								menu.menuItems[3]->setText("UNMUTE AUDIO", 100, 300, 70);
							}
							else
							{
								if (event.key.keysym.sym == SDLK_SPACE && menu.menuIndex == 3 && menu.audioMuted == true)
								{
									printf("\nSPACEKEY PRESSED");
									menu.audioMuted = false;
									if (menu.audioIndex == 0)
									{
										Mix_VolumeMusic(10);
									}
									if (menu.audioIndex == 1)
									{
										Mix_VolumeMusic(50);
									}
									if (menu.audioIndex == 2)
									{
										Mix_VolumeMusic(100);
									}
									menu.menuItems[3]->setText("MUTE AUDIO", 100, 300, 70);
								}
							}
							menu.Input(event);
						}
					}
				}
				aJoystick.X = SDL_JoystickGetAxis(aGamePadController, 0) / 3276.70;
				aJoystick.Y = SDL_JoystickGetAxis(aGamePadController, 1) / 3276.70;
				printf("Joystick X: %f -- Y: %f \n", aJoystick.X, aJoystick.Y);
				menu.Update(robotBackground);
				SDL_RenderClear(render);
				robotBackground.Render(render);
				menu.Render(render);
				SDL_RenderPresent(render);
			}

			while (running)
			{
				//int frameCap = SDL_GetTicks() + 3;

				SDL_Event event;
				if (useController == true)
				{
					aJoystick.X = SDL_JoystickGetAxis(aGamePadController, 0) / 3276.70;
					aJoystick.Y = SDL_JoystickGetAxis(aGamePadController, 1) / 3276.70;

					if (aJoystick.X > 5)
					{
						player.KEY_RIGHT = true;
					}
					if (aJoystick.X < -5)
					{
						player.KEY_LEFT = true;
					}
					if (aJoystick.X < 1 && aJoystick.X > -1)
					{
						player.velocity.X = 0;
						player.KEY_LEFT = false;
						player.KEY_RIGHT = false;
					}
				}

				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_JOYBUTTONDOWN: // Handle Joystick Button Presses
						if (event.jbutton.button == 0)
						{
							printf("A button - Pressed \n");
							player.KEY_UP = true;
						}
						if (event.jbutton.button == 1)
						{
							printf("B button - Pressed \n");
							if (pSystem.particles[0]->instantiated == false)
							{
								if (!player.isFlipped)
								{
									pSystem.particles[0]->velocity.X = 2;
								}
								if (player.isFlipped)
								{
									pSystem.particles[0]->velocity.X = -2;
								}
								pSystem.particles[0]->X = player.X + (player.Width / 2);
								pSystem.particles[0]->Y = player.Y + (player.Height / 2);
								pSystem.particles[0]->timeout = SDL_GetTicks() + 2500;
								pSystem.particles[0]->instantiated = true;
							}
							else
							{
								if (pSystem.particles[1]->instantiated == false)
								{
									if (!player.isFlipped)
									{
										pSystem.particles[1]->velocity.X = 2;
									}
									if (player.isFlipped)
									{
										pSystem.particles[1]->velocity.X = -2;
									}
									pSystem.particles[1]->X = player.X + (player.Width / 2);
									pSystem.particles[1]->Y = player.Y + (player.Height / 2);
									pSystem.particles[1]->timeout = SDL_GetTicks() + 2500;
									pSystem.particles[1]->instantiated = true;
								}
							}
						}
						break;
					case SDL_JOYBUTTONUP:
						if (event.jbutton.button == 0)
						{
							printf("A button - Up \n");
							player.KEY_UP = false;
						}
						if (event.jbutton.button == 1)
						{
							printf("B button - Up \n");
						}
						break;
					}
					if (enemy.gameLoss == true || enemy2.gameLoss == true || enemy3.gameLoss == true || enemy4.gameLoss == true || enemy5.gameLoss == true || enemy6.gameLoss == true || robot.gameLoss == true)
					{
						running = false;
						menuRunning = false;
						appOpen = false;
						menu.gameOver(window, "content/advanced_pixel-7.ttf", render, score.scoreCount);
					}
					if (event.type == SDL_QUIT)
					{
						running = false;
						menuRunning = false;
						appOpen = false;
						outerApp = false;
					}
					if (event.key.repeat == NULL)
					{
						if (event.key.keysym.sym == SDLK_ESCAPE)
						{
							running = false;
							menuRunning = true;
							menu.menuItems[0]->setText("UNPAUSE", 100, 150, 70);
							printf("ESCAPEKEY PRESSED");
						}
						pSystem.Input(event, player);
						player.Input(event);
					}
				}
				//Check if any changes have been made to the obects, and if so, update these changes
				enemy.spawnIn();
				enemy2.spawnIn();
				enemy3.spawnIn();
				enemy4.spawnIn();
				enemy5.spawnIn();
				enemy6.spawnIn();
				robot.spawnIn();
				cherry.spawnIn(menu);
				hourglass.spawnIn(menu);
				armour.spawnIn(menu);

				player.Update();
				enemy.Update(player, pSystem.particles, score, render, pEffects, menu);
				enemy2.Update(player, pSystem.particles, score, render, pEffects, menu);
				enemy3.Update(player, pSystem.particles, score, render, pEffects, menu);
				enemy4.Update(player, pSystem.particles, score, render, pEffects, menu);
				enemy5.Update(player, pSystem.particles, score, render, pEffects, menu);
				enemy6.Update(player, pSystem.particles, score, render, pEffects, menu);
				robot.Update(player, pSystem.particles, score, render, pEffects, menu);
				cherry.Update(render, player, enemy, enemy2, enemy3, enemy4, enemy5, enemy6, robot, score, menu);
				hourglass.Update(render, player, enemy, enemy2, enemy3, enemy4, enemy5, enemy6, robot, score, menu);
				armour.Update(render, player, enemy, enemy2, enemy3, enemy4, enemy5, enemy6, robot, score, menu);
				pSystem.Update(player);
				pEffects.Update();

				SDL_SetRenderDrawColor(render, 80, 100, 100, 255);

				//while(!SDL_TICKS_PASSED(SDL_GetTicks(), frameCap)){}

				//Render all of our sprites
				SDL_RenderClear(render);
				background.Render(render);
				ground.Render(render);
				scoreBoard.Render(render);
				cherry.Render(render);
				hourglass.Render(render);
				armour.Render(render);
				score.Render(render);
				pSystem.Render(render);
				pEffects.Render(render);
				enemy.Render(render);
				enemy2.Render(render);
				enemy3.Render(render);
				enemy4.Render(render);
				enemy5.Render(render);
				enemy6.Render(render);
				robot.Render(render);
				player.Render(render);

				pEffects.Emit(4.f, 0.05f);

				SDL_RenderPresent(render);

				frameCount++;
				lastTime = currentTime;
				currentTime = SDL_GetTicks();
				unsigned int frameTime = currentTime - lastTime;
				SDL_Log("[%s]", getTime());
				printf("\rFramecount: %i Tickcount: %i", frameTime, currentTime);
				printf(" Player Y velocity: %f", player.velocity.Y);
				printf(" Player X velcity: %f", player.velocity.X);

				if (enemy.velocityIncrement > 0.8 && musicFast == false)
				{
					Mix_PlayMusic(SOUND_aBckMusicFast, -1);
					musicFast = true;
				}
				if (enemy.velocityIncrement < 0.8 && musicFast == true)
				{
					Mix_PlayMusic(SOUND_aBckMusic, -1);
					musicFast = false;
				}
			}
		}
		score.serialiseAudio("../content/audio.json", menu);
	}
	//Destroy our windows -- free up memory that has been allocated to this window
	//SDL_DestroyRenderer(render);
	//SDL_DestroyRenderer(infoRender);
	SDL_JoystickClose(aGamePadController);
	aGamePadController = NULL;
	Mix_FreeMusic(SOUND_aBckMusic);
	Mix_FreeMusic(SOUND_aBckMusicFast);
	SDL_DestroyWindow(window);
	SDL_DestroyWindow(infoWindow);

	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();

	SDL_Log("Game closing");

	//Finally, exit
	return 0;
}