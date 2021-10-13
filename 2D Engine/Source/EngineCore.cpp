#include <string>
#include <vector>
#include "SDL.h"
#include "Scene.h"
#include "Sprite.h"
#include "Vec2D.h"

int main(int argc, char* args[])
{
	Scene Main = Scene();
	Sprite ship = Sprite();
	Sprite oship = Sprite();
	std::vector<Vec2D> InitPositions;
	InitPositions.push_back(Vec2D{300, 550});
	InitPositions.push_back(Vec2D{135, 448});
	std::string shipPath = "SpaceShipA.jpg";
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