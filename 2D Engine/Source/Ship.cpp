#include <iostream>
#include <vector>
#include "Laser.h"
#include "Ship.h"
#include "Scene.h"

#define OUT
Ship::Ship()
{
	Image = nullptr;
	Size.x = 0;
	Size.y = 0;
	Position.x = 0;
	Position.y = 0;
	ImageAngle = 0.0;
	MoveAngle = -M_PI/2;
	Speed = 0.0;
	Velocity.x = 0;
	Velocity.y = 0;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Scene = nullptr;
	BoundAction = 0;
	bCollisionEnabled = true;
}

void Ship::Update(SDL_Renderer* renderer)
{
	if(!bPlayer)
	{
		DefaultBehavior();
	}
	//Update location, rotation, etc
	return;
}

void Ship::PlayerInput(SDL_Event Event, SDL_Renderer* renderer)
{
	double IA;
	double MA;
	if(Event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (Event.button.button == SDL_BUTTON_LEFT)
		{
			Fire();
		}
	}
	if (Event.type == SDL_KEYDOWN)
	{
		if (Event.key.keysym.sym == SDLK_w)
		{
			MoveAngle = -M_PI/2;
			SetSpeed(12.00);
			MoveSprite();
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		if (Event.key.keysym.sym == SDLK_a)
		{
			MoveAngle = M_PI;
			SetSpeed(12.00);
			MoveSprite();
		/*	IA = ConvertToDegrees(ImageAngle);
			MA = ConvertToDegrees(MoveAngle);
			SetImageAngle(IA - 1);
			SetMoveAngle(MA - 1);*/
			UpdateVertices();
		}
		if (Event.key.keysym.sym == SDLK_d)
		{
			MoveAngle = 0;
			SetSpeed(12.00);
			MoveSprite();
			/*IA = ConvertToDegrees(ImageAngle);
			MA = ConvertToDegrees(MoveAngle);
			SetImageAngle(IA + 1);
			SetMoveAngle(MA + 1);*/
			UpdateVertices();
		}
	}
	if (Event.type == SDL_KEYUP)
	{
		SetSpeed(0.00);
	}
}

void Ship::DefaultBehavior()
{
	Sprite* Player = Scene->GetPlayerSprite();
	Vec2D PCenter = Player->GetPosition();
	if (PCenter.x > Center.x)
	{
		MoveAngle = 0;
		SetSpeed(1.00);
		MoveSprite();
	}
	else if (PCenter.x < Center.x)
	{
		MoveAngle = M_PI;
		SetSpeed(1.00);
		MoveSprite();
	}
}

void Ship::Fire()
{
	Laser l = Laser();
	Vec2D SpawnLoc{Center.x, Center.y - 50};
	Scene->SpawnSpriteAtLocation(&l, "Laser.png", SpawnLoc, 1.0);
}