#include <iostream>
#include <functional>
#include <thread>
#include "Scene.h"
#include "Sprite.h"

//macro OUT does nothing but explicitly states that something marked as OUT is an out parameter
//ie. it could be changed in the function it's being passed to
#define OUT

Scene::Scene()
{
	Window = nullptr;
	Renderer = nullptr;
	Size.x = 700;
	Size.y = 700;
	Framerate = 60;
	MouseButton = 0;
	CurrentTime = std::chrono::system_clock::now();
	LastTime = CurrentTime;
	DeltaTime = CurrentTime - LastTime;
	MousePos.x = 0;
	MousePos.y = 0;
	RefreshSeconds = 1.00 / Framerate;
}

void Scene::Start(std::vector<Sprite*> Sprites, std::vector<std::string> ImagePaths, std::vector<Vec2D> InitialPositions)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow("Engine Window (Default)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)Size.x, (int)Size.y, SDL_WINDOW_RESIZABLE);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	HideCursor();
	if (Window == nullptr)
	{
		std::cout << "There was an error initializing the Window. " << SDL_GetError() << std::endl;
		End();
	}
	if (Renderer == nullptr)
	{
		std::cout << "There was an error initializing the Renderer. " << SDL_GetError() << std::endl;
		End();
	}
	this->Sprites = Sprites;
	InitSprites(ImagePaths, InitialPositions);
	if (PCount == 0)
	{
		std::cout << "No Sprite is instantiated to be a player. Call Sprite::SetPlayerStatus(bool IsPlayer) and pass true on Sprite you want to control." << std::endl;
		End();
	}
	if (PCount > 1)
	{
		std::cout << "You instantiated too many Sprites to be the player. Multiplayer is currently not implemented." << std::endl;
		End();
	}
	Tick();
	End();
}

void Scene::End()
{
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void Scene::Tick()
{
	bool bWindowVisible = true;
	SDL_Event Event;
	while (bPlay)
	{
		CurrentTime = std::chrono::system_clock::now();
		DeltaTime = CurrentTime - LastTime;
		if (DeltaTime.count() < RefreshSeconds)
		{
			continue; //only used here to clean up code and help alleviate several layers of nesting
		}
		LastTime = CurrentTime;
		if (!bPaused)
		{
			//for (int i = 0; i < Sprites.size(); ++i)
			//{
			//	Sprites[i]->Update();
			//	/*if (Sprites[i]->CollidesWith(Sprites[i+1]))
			//	{
			//		std::cout << "Two things collided!" << std::endl;
			//	}
			//	else
			//	{
			//		std::cout << "No collision" << std::endl;
			//	}*/
			//}
			//SDL_PollEvent(&Event);
			//EventHandler(Event, OUT bPlay, OUT bPaused);
			SDL_PollEvent(&Event);
			std::thread ST = std::thread(&Scene::SceneThread, this, Event);
			std::thread GT = std::thread(&Scene::GameThread, this);
			ST.join();
			GT.join();
		}
		else
		{
			PausedEventHandler(OUT bPlay, OUT bPaused); // this function was also created to help alleviate 
		}
	}
	return;
}

void Scene::Pause()
{
	//Will maybe do something?
}

void Scene::Clear()
{
	SDL_RenderClear(Renderer);
}

void Scene::HideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void Scene::ShowCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

Vec2D Scene::GetMousePos()
{
	int x, y; // Out parameters
	MouseButton = SDL_GetMouseState(OUT &x, OUT &y);
	MousePos.x = x;
	MousePos.y = y;
	return MousePos;
}

void Scene::Hide()
{
	SDL_HideWindow(Window);
}

void Scene::Show()
{
	SDL_ShowWindow(Window);
}

void Scene::EventHandler(SDL_Event Event, bool& bPlay, bool& bPaused)
{
	bool bWindowVisible = true;
	if (Event.type == SDL_KEYDOWN)
	{
		if (Event.key.keysym.sym == SDLK_p)
		{
			bPaused = true;
			std::cout << "P pressed. Pausing..." << std::endl;
			Pause();
		}
		if (Event.key.keysym.sym == SDLK_c)
		{
			std::cout << "Clearing renderer" << std::endl;
			Clear();
		}
		if (Event.key.keysym.sym == SDLK_q || Event.key.keysym.sym == SDLK_ESCAPE)
		{
			bPlay = false;
			std::cout << "Quit button pressed. Quitting engine." << std::endl;
		}
		if (Event.key.keysym.sym == SDLK_t)
		{
			std::cout << "T pressed. Changing mouse visibility" << std::endl;
			int MouseVisibility = SDL_ShowCursor(SDL_QUERY);
			if (MouseVisibility)
			{
				HideCursor();
			}
			else
			{
				ShowCursor();
			}
		}
		if (Event.key.keysym.sym == SDLK_h)
		{
			std::cout << "Changing window visibility" << std::endl;
			if (bWindowVisible)
			{
				bWindowVisible = false;
				Hide();
			}
			else
			{
				bWindowVisible = true;
				Show();
			}
		}
	}
}

void Scene::PausedEventHandler(bool& bPlay, bool& bPaused)
{
	SDL_Event Event;
	SDL_PollEvent(&Event);
	if (Event.type == SDL_KEYDOWN)
	{
		if (Event.key.keysym.sym == SDLK_p)
		{
			bPaused = false;
			std::cout << "P pressed. Unpausing..." << std::endl;
		}
		if (Event.key.keysym.sym == SDLK_q || Event.key.keysym.sym == SDLK_ESCAPE)
		{
			bPlay = false;
			std::cout << "Quit button pressed. Quitting engine." << std::endl;
		}
	}
}

void Scene::InitSprites(std::vector<std::string> ImagePaths, std::vector<Vec2D> InitialPositions)
{
	for (int i = 0; i < Sprites.size(); ++i)
	{
		Sprites[i]->Scene = this;
		Sprites[i]->SetImage(Renderer, ImagePaths[i], InitialPositions[i]);
		Sprites[i]->Draw(Renderer);
		if (Sprites[i]->bPlayer)
		{
			++PCount;
		}
	}
}

void Scene::SceneThread(SDL_Event Event)
{
	std::cout << "Scene Thread running" << std::endl;
	//SDL_Event Event;
	SDL_PollEvent(&Event);
	//EventHandler(Event, OUT bPlay, OUT bPaused); // this function was also created to help alleviate 
	while (SDL_PollEvent(&Event))
	{
		EventHandler(Event, OUT bPlay, OUT bPaused); // this function was also created to help alleviate 
	}
	SDL_RenderPresent(Renderer);
}

void Scene::GameThread()
{
	std::cout << "Game Thread running" << std::endl;
	for (int i = 0; i < Sprites.size(); ++i)
	{
		Sprites[i]->Update();
		/*if (Sprites[i]->CollidesWith(Sprites[i+1]))
		{
			std::cout << "Two things collided!" << std::endl;
		}
		else
		{
			std::cout << "No collision" << std::endl;
		}*/
	}
}