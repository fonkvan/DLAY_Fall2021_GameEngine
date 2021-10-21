#pragma once
#include <vector>
#include "Sprite.h"
class Laser;
class Ship : public Sprite
{
	private:
		std::vector<Laser*> Lasers;
		int count = 0;
		int FireFrames = 20;
		int CountTilFire = FireFrames;
		bool bCanFire = true;
	public:
		Ship();
		virtual void Update(SDL_Renderer* renderer) override;
		virtual void PlayerInput(SDL_Event Event, SDL_Renderer* renderer) override;
		virtual void DefaultBehavior() override;
		virtual void CollisionBehavior(Sprite* OtherSprite) override;
		virtual void DealDamage(Sprite* OtherSprite, double Amount) override;
		void Fire();
		void Die();
		friend class SpaceGame;
};

