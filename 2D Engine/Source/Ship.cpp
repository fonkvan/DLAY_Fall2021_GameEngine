#include <iostream>
#include "Ship.h"

#define OUT
Ship::Ship()
{
	Image = nullptr;
	Size.x = 0;
	Size.y = 0;
	Position.x = 0;
	Position.y = 0;
	ImageAngle = 0.0;
	MoveAngle = 0.0;
	Speed = 0.0;
	Velocity.x = 0;
	Velocity.y = 0;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Scene = nullptr;
	BoundAction = 0;
	bCollisionEnabled = true;
}

void Ship::Update()
{
	SDL_Event Event;
	if (bPlayer)
	{
		SDL_PollEvent(&Event);
		PlayerInput(Event);
	}
	else
	{
		DefaultBehavior();
	}
	return;
}

void Ship::PlayerInput(SDL_Event Event)
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
		if (Event.key.keysym.sym == SDLK_a)
		{
			IA = ConvertToDegrees(ImageAngle);
			MA = ConvertToDegrees(MoveAngle);
			SetImageAngle(IA - 1);
			SetMoveAngle(MA - 1);
			std::cout << "Rotating counter clockwise" << std::endl;
		}
		if (Event.key.keysym.sym == SDLK_d)
		{
			IA = ConvertToDegrees(ImageAngle);
			MA = ConvertToDegrees(MoveAngle);
			SetImageAngle(IA + 1);
			SetMoveAngle(MA + 1);
			std::cout << "Rotating clockwise" << std::endl;
		}
	}
}

void Ship::DefaultBehavior()
{

}

void Ship::Fire()
{

}