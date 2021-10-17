#pragma once
#include "Sprite.h"
class Ship : public Sprite
{
	private:

	public:
	Ship();
	virtual void Update() override;
	virtual void PlayerInput(SDL_Event Event) override;
	virtual void DefaultBehavior() override;
	void Fire();
};

