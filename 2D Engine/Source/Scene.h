#pragma once
#include <chrono>
#include <string>
#include <vector>
#include "SDL.h"
#include "Vec2D.h"

class Sprite;
class Scene
{
	private:
		bool bPlay = true;
		bool bPaused = false;
		SDL_Window* Window;
		SDL_Renderer* Renderer = nullptr;
		Vec2D Size;
		std::vector<Sprite*> Sprites;
		int Framerate;
		Uint32 MouseButton;
		Vec2D MousePos;
		std::chrono::system_clock::time_point CurrentTime;
		std::chrono::system_clock::time_point LastTime;
		std::chrono::duration<double> DeltaTime;
		double RefreshSeconds;
		int PCount = 0;
	public:
		Scene();
		void Start(std::vector<Sprite*> Sprites, std::vector<std::string> ImagePaths, std::vector<Vec2D> InitialPositions);
		void End();
		void Tick();
		void Pause();
		void Clear();
		void HideCursor();
		void ShowCursor();
		Vec2D GetMousePos();
		void Hide();
		void Show();
		void SceneThread(SDL_Event Event);
		void GameThread();
		void EventHandler(SDL_Event Event, bool& bPlay, bool& bPaused);
		void PausedEventHandler(bool& bPlay, bool& bPaused);
		void InitSprites(std::vector<std::string> ImagePaths, std::vector<Vec2D> InitialPositions);
};