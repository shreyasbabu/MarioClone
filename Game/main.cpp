#include "Precompiled.h"

//#include "engine/core/IGame.h"
#include "engine/manager/InputHandler.h"
#include "engine/manager/AssetManager.h"
#include "engine/manager/CollisionSystem.h"
#include "engine/manager/RenderSystem.h"

#include "game/Game.h"

using FLoatDT = std::chrono::duration<float>;

int main()
{
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mario!", (sf::Style::Titlebar | sf::Style::Close));

	std::unique_ptr<InputHandler> inputHandler = std::make_unique<InputHandler>(window.get());
	std::unique_ptr<RenderSystem> renderSystem = std::make_unique<RenderSystem>(window.get());
	std::unique_ptr<CollisionSystem> collisionSystem = std::make_unique<CollisionSystem>(window.get());
	std::unique_ptr<AssetManager> assetManager = std::make_unique<AssetManager>();

	std::unique_ptr<IGame> game = std::make_unique<Game>(window.get());
	
	window->setFramerateLimit(60);

	auto lastTime = std::chrono::steady_clock::now();
	while (!inputHandler->shouldExitGame())
	{
		const auto currentTime =  std::chrono::steady_clock::now();
		const float deltaTime = std::chrono::duration<float>((std::chrono::steady_clock::now() - lastTime) * 1000.0f ).count();
		lastTime = currentTime;

		inputHandler->update(deltaTime);
		game->update(deltaTime);
		collisionSystem->update(deltaTime);
		renderSystem->update(deltaTime);
	}

	return 0;
}


/*
	TODO
	- Occlusion culling
	- Music Streaming
	- HUD (maybe menu and screen transsion)
	- JSON file thing
*/