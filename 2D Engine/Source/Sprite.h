#pragma once
#include <stack>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Vec2D.h"

class Scene;
class Sprite
{
	protected:
		SDL_Texture* Image;
		Vec2D Size;
		Vec2D Position;
		double LastAngle;
		double ImageAngle;
		double MoveAngle; //MoveAngle and Speed used to calculate dx,dy
		double Speed;
		double Scale;
		Vec2D D;
		Vec2D Center;
		Vec2D Velocity; //dx, dy
		Vec2D Acceleration; //ddx, ddy
		Scene* Scene;
		Uint8* BoundAction;
		SDL_Rect texture;
		std::vector<Vec2D> vertices;
		bool bCollisionEnabled;
		bool bPlayer = false;
		double ConvertToDegrees(double Radians);
	private:
		void VectorProjection(double Speed); //convert into individual Vector (Vec2D) components x and y
		double ConvertToRadians(double Degrees);
	public:
		Sprite();
		void SetScale(double s);
		SDL_Texture* SetImage(SDL_Renderer* renderer, std::string ImagePath, Vec2D InitPosition);
		void Draw(SDL_Renderer* renderer);
		virtual void Update(SDL_Renderer* renderer);
		virtual void PlayerInput(SDL_Event Event, SDL_Renderer* renderer); //If class not meant to ever be a player, just return
		virtual void DefaultBehavior(); //Standard behavior if not controlled by player, possibly AI behavior
		void Hide();
		void Show();
		void SetSpeed(double Speed);
		void SetImageAngle(double Degrees);
		void SetMoveAngle(double Degrees);
		void AddForce(Vec2D Force);
		void SetBoundAction();
		void CheckBounds();
		bool SeparateAxisTheorem(std::stack<Vec2D> Normals, Sprite* OtherSprite);
		bool CollidesWith(Sprite* OtherSprite); //use Separating Axis Theorem 
		double DistanceTo(Sprite* OtherSprite);
		double AngleTo(Sprite* OtherSprite);
		void SetVertices();
		void UpdateVertices();
		void SetCollisionEnabled(bool Set);
		void MoveSprite();
		std::stack<Vec2D> GetNormals();
		void SetPlayerStatus(bool IsPlayer);
		Vec2D GetPosition(); //returns Center position
		friend class Scene;
};