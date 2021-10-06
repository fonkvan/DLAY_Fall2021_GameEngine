#include "Sprite.h"

Sprite::Sprite()
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
}

void Sprite::VectorProjection(double Speed)
{
	Velocity.x = Speed * cos(MoveAngle) + Acceleration.x;
	Velocity.y = Speed * sin(MoveAngle) + Acceleration.y;
	this->Speed = sqrt((Velocity.x * Velocity.x) + (Velocity.y * Velocity.y));
	MoveAngle = atan2(Velocity.y, Velocity.x);
}

void Sprite::SetImage(std::string ImageName)
{

}

void Sprite::Draw()
{

}

void Sprite::Update()
{

}

void Sprite::Hide()
{

}

void Sprite::Show()
{

}

void Sprite::SetSpeed(double Speed)
{
	VectorProjection(Speed);
}

void Sprite::SetImageAngle(double Degrees)
{
	ImageAngle = ConvertToRadians(Degrees);
}

void Sprite::SetMoveAngle(double Degrees)
{
	MoveAngle = ConvertToRadians(Degrees);
}

void Sprite::AddForce(double Force)
{

}

void Sprite::SetBoundAction()
{

}

void Sprite::CheckBounds()
{

}

bool Sprite::CollidesWith(Sprite* OtherSprite)
{
	return false;
}

double Sprite::DistanceTo(Sprite* OtherSprite)
{
	double DeltaX = (this->Position.x - OtherSprite->Position.x) * (this->Position.x - OtherSprite->Position.x);
	double DeltaY = (this->Position.y - OtherSprite->Position.y) * (this->Position.y - OtherSprite->Position.y);
	return sqrt(DeltaX + DeltaY);
}

double Sprite::AngleTo(Sprite* OtherSprite)
{
	return 0.0;
}

double Sprite::ConvertToRadians(double Degrees)
{
	return Degrees * M_PI / 180.00;
}