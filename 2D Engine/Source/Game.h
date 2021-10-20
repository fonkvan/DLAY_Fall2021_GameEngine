//This is an abstract class and should not be instantiated on it's own.
#pragma once
#include <string>
#include <vector>
#include "Vec2D.h"

class Scene;
class Sprite;
class Game
{
	protected:
		const char* GameName;
		Scene* GameScene;
		std::vector<Sprite*> Sprites;
		std::vector<std::string> ImagePaths;
		std::vector<Vec2D> InitialPositions;
	public:
		Game();
		Game(Scene* GameScene);
		virtual void InitGame(const char* GameName);
		void RunGame();
};

