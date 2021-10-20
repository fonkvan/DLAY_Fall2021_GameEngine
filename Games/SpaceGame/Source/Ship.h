#pragma once
#include "Sprite.h"
class Ship : public Sprite
{
	public:
		Ship();
		virtual void Update(SDL_Renderer* renderer) override;
		virtual void PlayerInput(SDL_Event Event, SDL_Renderer* renderer) override;
		virtual void DefaultBehavior() override;
		void Fire();
};

