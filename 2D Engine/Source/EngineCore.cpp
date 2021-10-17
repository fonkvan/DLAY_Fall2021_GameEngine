#include <string>
#include <vector>
#include "SDL.h"
#include "Scene.h"
#include "Ship.h"
#include "Sprite.h"
#include "Vec2D.h"

int main(int argc, char* args[])
{
	Scene Main = Scene();
	Ship ship = Ship();
	ship.SetSpeed(300);
	ship.SetPlayerStatus(true);
	std::vector<Vec2D> InitPositions;
	InitPositions.push_back(Vec2D{300, 300});
	std::string shipPath = "SpaceShipB.PNG";
	std::vector<Sprite*> Sprites;
	std::vector<std::string> ImagePaths;
	Sprites.push_back(&ship);
	ImagePaths.push_back(shipPath);
	Main.Start(Sprites, ImagePaths, InitPositions);
	
	return(0);
}