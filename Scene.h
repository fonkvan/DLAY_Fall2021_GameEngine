#pragma once
#include <vector>
#include "SDL.h"
#include "Vec2D.h"

class Sprite;
class Scene
{
	private:
		SDL_Window* Window;
		SDL_Renderer* Renderer;
		Vec2D Size;
		//Vec2D Position;
		std::vector<Sprite*> Sprites;
		int Framerate;
		const Uint8* Keyboard;
		Uint32 MouseButton;
		Vec2D MousePos;
	public:
		Scene();
		void Start();
		void End();
		void Pause();
		void Clear();
		void HideCursor();
		void ShowCursor();
		Vec2D GetMousePos();
		void Hide();
		void Show();
};

