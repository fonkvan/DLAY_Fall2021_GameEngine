#include "Game.h"
#include "SDL.h"
#include "Scene.h"
#include "..\..\Games\SpaceGame\Source\SpaceGame.h"
#include "..\..\Games\SpaceGame\Source\Ship.h"
#include "Sprite.h"
#include "Vec2D.h"

int main(int argc, char* args[])
{
	Scene Main = Scene();
	SpaceGame SG = SpaceGame(&Main);
	SG.InitGame("SG");
	return(0);
}