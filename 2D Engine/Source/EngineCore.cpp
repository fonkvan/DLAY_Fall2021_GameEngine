#include <string>
#include <vector>
#include "SDL.h"
#include "Scene.h"
#include "..\..\Games\SpaceGame\Source\Ship.h"
#include "Sprite.h"
#include "Vec2D.h"

int main(int argc, char* args[])
{
	Scene Main = Scene();
	Ship ship = Ship();
	Ship oship = Ship();
	ship.SetScale(0.2);
	oship.SetScale(0.2);
	ship.SetPlayerStatus(true);
	std::vector<Vec2D> InitPositions;
	InitPositions.push_back(Vec2D{300, 600});
	InitPositions.push_back(Vec2D{345, 300});
	oship.SetImageAngle(180);
	std::string shipPath = "Games/SpaceGame/Assets/SpaceShipB.PNG";
	std::string oshipPath = shipPath;
	std::vector<Sprite*> Sprites;
	std::vector<std::string> ImagePaths;
	Sprites.push_back(&ship);
	Sprites.push_back(&oship);
	ImagePaths.push_back(shipPath);
	ImagePaths.push_back(oshipPath);
	Main.Start(Sprites, ImagePaths, InitPositions);
	
	return(0);
}