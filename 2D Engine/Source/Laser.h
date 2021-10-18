#pragma once
#include "Sprite.h"

class Laser : public Sprite
{
	public:
		Laser();
		virtual void Update(SDL_Renderer* renderer) override;
		virtual void PlayerInput(SDL_Event Event, SDL_Renderer* renderer) override;
		virtual void DefaultBehavior() override;
};