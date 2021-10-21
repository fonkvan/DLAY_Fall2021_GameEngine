#include <iostream>
#include <vector>
#include "Laser.h"
#include "Ship.h"
#include "..\..\2D Engine\Source\Scene.h"

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
	Health = 3.00;
}

void Ship::Update(SDL_Renderer* renderer)
{
	if(!bPlayer)
	{
		DefaultBehavior();
	}
	if (bPlayer)
	{
		if (!bCanFire)
		{
			--CountTilFire;
		}
		if (CountTilFire <= 0)
		{
			bCanFire = true;
			CountTilFire = FireFrames;
		}
	}
	if (Health <= 0)
	{
		Die();
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
			if (bDraw && bCanFire)
			{
				Fire();
			}
		}
	}
	if (Event.type == SDL_KEYDOWN)
	{
		if (Event.key.keysym.sym == SDLK_w)
		{
			/*MoveAngle = -M_PI/2;
			SetSpeed(3.00);
			MoveSprite();*/
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		if (Event.key.keysym.sym == SDLK_a)
		{
			MoveAngle = M_PI;
			SetSpeed(3.00);
			MoveSprite();
			/*IA = ConvertToDegrees(ImageAngle);
			MA = ConvertToDegrees(MoveAngle);
			SetImageAngle(IA - 1);
			SetMoveAngle(MA - 1);
			UpdateVertices();*/
		}
		if (Event.key.keysym.sym == SDLK_d)
		{
			//Side-to-side movement
			MoveAngle = 0;
			SetSpeed(3.00);
			MoveSprite();
			//For rotation mechanics if wanted
			/*IA = ConvertToDegrees(ImageAngle);
			MA = ConvertToDegrees(MoveAngle);
			SetImageAngle(IA + 1);
			SetMoveAngle(MA + 1);
			UpdateVertices();*/
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

void Ship::CollisionBehavior(Sprite* OtherSprite)
{
	return;
}

void Ship::DealDamage(Sprite* OtherSprite, double Amount)
{
	return;
}

void Ship::Fire()
{
	bCanFire = false;
	Laser* l;
	++count;
	if (count >= Lasers.size())
	{
		count = 0;
	}
	l = Lasers[count];
	//l->MoveAngle = MoveAngle; // Use this for rotational mechanics, ie ship can rotate
	l->MoveAngle = -M_PI/2; //Use this for side-to-side movement only
	l->ImageAngle = ImageAngle;
	l->Center.x = Center.x;
	l->Center.y = Center.y;
	l->texture.x = Center.x - D.x;
	l->texture.y = Center.y - D.y;
	l->SetVertices();
	l->Speed = 20;
	l->Show();
}

void Ship::Die()
{
	Hide();
}