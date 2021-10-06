#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Vec2D.h"

class Scene;
class Sprite
{
	private:
		SDL_Surface* Image;
		Vec2D Size;
		Vec2D Position;
		double ImageAngle;
		double MoveAngle; //MoveAngle and Speed used to calculate dx,dy
		double Speed;
		Vec2D Velocity; //dx, dy
		Vec2D Acceleration; //ddx, ddy
		Scene* Scene;
		Uint8* BoundAction;
		void VectorProjection(double Speed);
		double ConvertToRadians(double Degrees);
	public:
		Sprite();
		void SetImage(std::string ImageName);
		void Draw();
		virtual void Update();
		void Hide();
		void Show();
		void SetSpeed(double Speed);
		void SetImageAngle(double Degrees);
		void SetMoveAngle(double Degrees);
		void AddForce(double Force);
		void SetBoundAction();
		void CheckBounds();
		bool CollidesWith(Sprite* OtherSprite);
		double DistanceTo(Sprite* OtherSprite);
		double AngleTo(Sprite* OtherSprite);
};

