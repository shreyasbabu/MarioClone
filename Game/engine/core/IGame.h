#pragma once
#include "engine/core/ISystem.h"
#include "engine/manager/GameObjectManager.h"
#include "engine/component/Camera.h"

class IGame : public ISystem
{
public:
	IGame(NonOwnPtr<sf::RenderWindow> window)
		:ISystem(window)
	{
	}
	virtual ~IGame() override = default;

	virtual void update(float deltaTime) override = 0;

protected:
	std::unique_ptr<GameObjectManager> mGameObjManager;
	//other managers
};

