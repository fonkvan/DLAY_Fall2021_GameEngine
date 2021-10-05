#include "Scene.h"
#include "Sprite.h"
#include <iostream>

Scene::Scene()
{
	Size.x = 700;
	Size.y = 700;
	//Position.x = 0;
	//Position.y = 0;
	Framerate = 60;
	Keyboard = 0;
	MouseButton = 0;
}

void Scene::Start()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow("Engine Window (Default)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Size.x, Size.y, SDL_WINDOW_RESIZABLE);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	HideCursor();
	bool bPlay = true;
	bool bPaused = false;
	while (bPlay)
	{
		float Tick = 1.f/Framerate;
		float TickMS = Tick/1000.f;
		SDL_Delay(TickMS);
		Keyboard = SDL_GetKeyboardState(NULL);
		SDL_Event Event;
		while (SDL_PollEvent(&Event))
		{
			if (!bPaused)
			{
				for (Sprite* s : Sprites)
				{
					s->Update();
				}
			}
			if (Keyboard[SDL_SCANCODE_P])
			{
				bPaused = true;
				std::cout << "P pressed. Pausing..." << std::endl;
				Pause();
				bPaused = false;
				std::cout << "Unpaused" << std::endl;
			}
			if (Keyboard[SDL_SCANCODE_Q])
			{
				bPlay = false;
				std::cout << "Q Pressed. Quitting game." << std::endl;
			}
			if (Keyboard[SDL_SCANCODE_T])
			{
				std::cout << "T pressed. Changing mouse visibility" << std::endl;
				int MouseVisibility = SDL_ShowCursor(SDL_QUERY);
				if (MouseVisibility)
				{
					HideCursor();
					SDL_Delay(2000);
				}
				else
				{
					ShowCursor();
					SDL_Delay(2000);
				}
			}
		}
		SDL_RenderPresent(Renderer);
	}
	End();
}

void Scene::End()
{
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void Scene::Pause()
{
	SDL_Delay(1000);
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
	MouseButton = SDL_GetMouseState(&x, &y);
	MousePos.x = x;
	MousePos.y = y;
	return MousePos;
}

void Scene::Hide()
{

}

void Scene::Show()
{

}