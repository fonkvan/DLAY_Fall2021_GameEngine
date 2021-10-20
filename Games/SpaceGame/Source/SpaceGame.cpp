#include "SpaceGame.h"
#include "Ship.h"
#include "Laser.h"
#include "..\..\2D Engine\Source\Scene.h"

SpaceGame::SpaceGame(Scene* GameScene)
{
	GameName = "Space Game";
	this->GameScene = GameScene;
}

void SpaceGame::InitGame(const char* GameName)
{
	Game::InitGame(GameName);
	Ship ship = Ship();
	Ship oship = Ship();
	ship.SetScale(0.2);
	oship.SetScale(0.2);
	ship.SetPlayerStatus(true);
	InitialPositions.push_back(Vec2D{ 300, 600 });
	InitialPositions.push_back(Vec2D{ 345, 300 });
	oship.SetImageAngle(180);
	std::string shipPath = "Games/SpaceGame/Assets/SpaceShipB.PNG";
	std::string oshipPath = shipPath;
	Sprites.push_back(&ship);
	Sprites.push_back(&oship);
	ImagePaths.push_back(shipPath);
	ImagePaths.push_back(oshipPath);
}