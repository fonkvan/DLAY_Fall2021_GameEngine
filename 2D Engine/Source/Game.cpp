#include "Game.h"
#include "Scene.h"

Game::Game()
{
	GameName = "";
	GameScene = nullptr;
}
Game::Game(Scene* GameScene)
{
	GameName = "";
	this->GameScene = GameScene;
}

void Game::InitGame(const char* GameName)
{
	this->GameName = GameName;
}

void Game::RunGame()
{
	GameScene->Start(GameName, Sprites, ImagePaths, InitialPositions);
}