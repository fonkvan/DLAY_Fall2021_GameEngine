#include <iostream>
#include "Scene.h"
#include "Sprite.h"

//macro OUT does nothing but explicitly states that something marked as OUT is an out parameter, ie. it could be changed in the function it's being passed to
#define OUT

Scene::Scene()
{
	Window = nullptr;
	Renderer = nullptr;
	Size.x = 700;
	Size.y = 700;
	//Position.x = 0;
	//Position.y = 0;
	Framerate = 60;
	Keyboard = 0;
	MouseButton = 0;
	CurrentTime = std::chrono::system_clock::now();
	LastTime = CurrentTime;
	DeltaTime = CurrentTime - LastTime;
	MousePos.x = 0;
	MousePos.y = 0;
	RefreshSeconds = 1.00 / Framerate;
}

void Scene::Start()
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
	bool bPlay = true;
	bool bPaused = false;
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
			for (Sprite* s : Sprites)
			{
				s->Update();
			}
			Keyboard = SDL_GetKeyboardState(NULL);

			while (SDL_PollEvent(&Event))
			{
				EventHandler(Event, OUT bPlay, OUT bPaused); // this function was also created to help alleviate 
			}
			SDL_RenderPresent(Renderer);
		}
		else
		{
			PausedEventHandler(Event, OUT bPlay, OUT bPaused); // this function was also created to help alleviate 
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

void Scene::PausedEventHandler(SDL_Event Event, bool& bPlay, bool& bPaused)
{
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