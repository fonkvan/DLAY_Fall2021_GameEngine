#pragma once
#include "..\..\2D Engine\Source\Game.h"

class SpaceGame : public Game
{
	public:
		SpaceGame(Scene* GameScene);
		virtual void InitGame(const char* GameName) override;
};

