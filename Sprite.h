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
		float ImageAngle;
		float MoveAngle; //MoveAngle and Speed used to calculate dx,dy
		float Speed;
		Vec2D Velocity; //dx, dy
		Vec2D Acceleration; //ddx, ddy
		Scene* Scene;
		Uint8* BoundAction;
		void VectorProjection();
	public:
		Sprite();
		void SetImage(std::string ImageName);
		void Draw();
		virtual void Update();
		void Hide();
		void Show();
		void SetSpeed(float Speed);
		void SetImageAngle(float Degrees);
		void SetMoveAngle(float Degrees);
		void AddForce();
		void SetBoundAction();
		void CheckBounds();
		bool CollidesWith(Sprite* Sprite);
		void DistanceTo(Sprite* Sprite);
		void AngleTo(Sprite* Sprite);
};

