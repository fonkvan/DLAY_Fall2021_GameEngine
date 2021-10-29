#include "SpaceGame.h"
#include "Ship.h"
#include "Laser.h"
#include "..\..\..\2D Engine\Source\Scene.h"

SpaceGame::SpaceGame(Scene* GameScene)
{
	GameName = "Space Game";
	this->GameScene = GameScene;
}

void SpaceGame::InitGame(const char* GameName)
{
	Game::InitGame(GameName);
	//Ships
	Ship ship = Ship();
	Ship EnemyShip = Ship();
	ship.SetScale(0.2);
	EnemyShip.SetScale(0.2);
	ship.SetPlayerStatus(true);
	EnemyShip.SetImageAngle(180);
	std::string shipPath = "Games/SpaceGame/Assets/SpaceShipB.PNG";
	std::string EnemyShipPath = shipPath;
	//Lasers
	Laser L1 = Laser();
	Laser L2 = Laser();
	Laser L3 = Laser();
	L1.SetCollisionEnabled(false);
	L2.SetCollisionEnabled(false);
	L3.SetCollisionEnabled(false);
	std::string LaserPath = "Games/SpaceGame/Assets/Laser.png";
	//Place in vectors
	InitialPositions.push_back(Vec2D{ 300, 600 });
	InitialPositions.push_back(Vec2D{ 345, 300 });
	Vec2D offscreen{-100, 0};
	Vec2D off2{-200, 0};
	Vec2D off3{-300, 0};
	InitialPositions.push_back(offscreen);
	InitialPositions.push_back(off2);
	InitialPositions.push_back(off3);
	Sprites.push_back(&ship);
	Sprites.push_back(&EnemyShip);
	Sprites.push_back(&L1);
	Sprites.push_back(&L2);
	Sprites.push_back(&L3);
	ship.Lasers.push_back(&L1);
	ship.Lasers.push_back(&L2);
	ship.Lasers.push_back(&L3);
	for (int i = 0; i < ship.Lasers.size(); ++i)
	{
		ship.Lasers[i]->Owner = &ship;
	}
	ImagePaths.push_back(shipPath);
	ImagePaths.push_back(EnemyShipPath);
	ImagePaths.push_back(LaserPath);
	ImagePaths.push_back(LaserPath);
	ImagePaths.push_back(LaserPath);
	GameScene->Start(GameName, Sprites, ImagePaths, InitialPositions);
}