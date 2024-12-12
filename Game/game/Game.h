#pragma once

#include "engine/core/IGame.h"
//#include "CoinTile.h"

class Mario;
//class CointTile;
enum class GameInput;
enum class AnimationState;

class Game : public IGame
{
public:
	Game(NonOwnPtr<sf::RenderWindow> window);
	~Game() override = default;
	void update(float deltaTime) override;

	std::vector<std::vector<std::unique_ptr<Collider>>> mLevelColliderData;

	std::list<std::unique_ptr<RenderElement>> mRenderData;
	std::list<std::unique_ptr<Collider>> mColliderData;
	std::list<std::unique_ptr<GameObject>> mObjectData;

	std::unique_ptr<Mario> mario;
	NonOwnPtr<Camera> mMainCamera;

	sf::Sound mBackgroundSound;
	sf::Sound mEndSound;
	sf::Sound mMarioDieSound;
	std::unique_ptr<RenderElement> mGameEndText;

private:
	void _playerMoveLogic(const sf::Vector2f& playerPos, AnimationState state, bool flip);
	bool _isKeyPressed(GameInput in, GameInput isKey) const;
	void _init();
	void _initLevel();
	void _initSound();
	void _initPlayer();
	void _initEnemy();
	void _initFont();
	void _gameOver();
	void _gameWin();
	
	void _initGameEnd(std::string_view endText);

	const sf::Vector2f mEndScreenOffset{};

	float endTimer = 0.0f;
	const float maxEndTimer = 3000.0f;
};

