#pragma once
#include "..\..\..\2D Engine\Source\Sprite.h"

class Laser : public Sprite
{
	private:
		Sprite* Owner;
	public:
		Laser();
		virtual void Update(SDL_Renderer* renderer) override;
		virtual void PlayerInput(SDL_Event Event, SDL_Renderer* renderer) override;
		virtual void DefaultBehavior() override;
		virtual void CollisionBehavior(Sprite* OtherSprite) override;
		virtual void DealDamage(Sprite* OtherSprite, double Amount) override;
		friend class Ship;
		friend class SpaceGame;
};