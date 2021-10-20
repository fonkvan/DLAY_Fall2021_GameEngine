#include "Laser.h"

Laser::Laser()
{
	Image = nullptr;
	Size.x = 0;
	Size.y = 0;
	Position.x = 0;
	Position.y = 0;
	ImageAngle = 0.0;
	MoveAngle = -M_PI / 2;
	Speed = 0.0;
	Velocity.x = 0;
	Velocity.y = 0;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Scene = nullptr;
	BoundAction = 0;
	bCollisionEnabled = true;
}

void Laser::Update(SDL_Renderer* renderer)
{
	DefaultBehavior();
}

void Laser::PlayerInput(SDL_Event Event, SDL_Renderer* renderer)
{
	return;
}

void Laser::DefaultBehavior()
{
	SetSpeed(50.00);
	MoveSprite();
}