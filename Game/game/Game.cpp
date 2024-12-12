#include "Precompiled.h"

#include "Game.h"
#include "Mario.h"
#include "Goomba.h"
#include "CoinTile.h"

#include "engine/manager/RenderSystem.h"
#include "engine/manager/AssetManager.h"
#include "engine/manager/InputHandler.h"
#include "engine/component/Animator.h"



Game::Game(NonOwnPtr<sf::RenderWindow> window)
	:IGame(window)
	, mEndScreenOffset(sf::Vector2f(-2000.0f, 2000.0f))
{
	mGameObjManager = std::make_unique<GameObjectManager>();
	mMainCamera = ServiceLocator::instance().getMainCamera();

	_init();

}
void Game::update(float deltaTime)
{
	mGameObjManager->update(deltaTime);
	if(ServiceLocator::instance().mIsWin == true)
	{
		_gameWin();
	}
	if(ServiceLocator::instance().mIsLoose == true)
	{
		mBackgroundSound.stop();
		endTimer += deltaTime;
		if (endTimer >= maxEndTimer)
		{
			_gameOver();
		}
	}

	if (!mario->isDead()) 
	{
		bool AnimStateChanged = false;
		const GameInput currentInputKeys = ServiceLocator::instance().getKeyInput();
		if (_isKeyPressed(currentInputKeys, GameInput::up))
		{
			_playerMoveLogic(sf::Vector2f(mario->getPos().x, mario->getPos().y - PLAYER_SPEED * deltaTime), AnimationState::STATE_ONE, false);
			AnimStateChanged = true;
		}
		if (_isKeyPressed(currentInputKeys, GameInput::down))
		{
			_playerMoveLogic(sf::Vector2f(mario->getPos().x, mario->getPos().y + PLAYER_SPEED * deltaTime), AnimationState::STATE_ONE, false);
			AnimStateChanged = true;
		}
		if (_isKeyPressed(currentInputKeys, GameInput::left))
		{
			_playerMoveLogic(sf::Vector2f(mario->getPos().x - PLAYER_SPEED * deltaTime, mario->getPos().y), AnimationState::STATE_ONE, true);
			AnimStateChanged = true;
		}
		if (_isKeyPressed(currentInputKeys, GameInput::right))
		{
			_playerMoveLogic(sf::Vector2f(mario->getPos().x + PLAYER_SPEED * deltaTime, mario->getPos().y), AnimationState::STATE_ONE, false);
			AnimStateChanged = true;
		}
		if (_isKeyPressed(currentInputKeys, GameInput::jump))
		{
			if (mario->isJumping() == false)
			{
				mario->Jump();
			}
		}
		if (!AnimStateChanged)
		{
			mario->getAnimator()->setAnimationState(AnimationState::STATE_ZERO, 0, 0);
		}

	}
}

void Game::_playerMoveLogic(const sf::Vector2f& playerPos, AnimationState state, bool flip)
{
	if (flip)
	{
		mario->getRenderElement()->getSprite()->setScale(-SCALE, SCALE);
	}
	else
	{
		mario->getRenderElement()->getSprite()->setScale(SCALE, SCALE);
	}
	mario->setPos(playerPos);
	mario->getAnimator()->setAnimationState(state, 1, 3);
}

bool Game::_isKeyPressed(GameInput in, GameInput isKey) const
{
	return static_cast<int>(in) & static_cast<int>(isKey);
}

void Game::_init()
{
	_initPlayer();
	_initEnemy();
	_initLevel();
	_initSound();
	_initFont();
	
	mMainCamera->setFollowTarget(mario->getRenderElement());

}

void Game::_initLevel()
{
	const sf::Vector2u origin(0, 0);
	const sf::Vector2u textureSize = ServiceLocator::instance().getSprite(Asset::Image::tile)->spriteSize;
	int count = 0;
	int index = 0;
	
	mColliderData.emplace_back(std::make_unique<Collider>(CollisionLayer::floor));
	mColliderData.back()->setRidgidbody(sf::FloatRect(origin.x , origin.x + (textureSize.y * 12 * SCALE), textureSize.x * LEVEL_WIDTH * SCALE, textureSize.y * 4 * SCALE));
	
	while(LevelData::levelOrder.size() > count)
	{
		for (int height = 0; height < LEVEL_HEIGHT; ++height)
		{
			for (int width = 0; width < LEVEL_WIDTH; ++width)
			{
				const char tile = LevelData::levelOrder[count][index++];
				const int layer = std::stoi(&tile);
				if (layer != 0)
				{
					mRenderData.emplace_back(std::make_unique<RenderElement>(RenderLayer::background, &ServiceLocator::instance().getSprite(Asset::Image::tile)->texture, textureSize));
					mRenderData.back()->setImageSize(textureSize);
					mRenderData.back()->setTexture(&ServiceLocator::instance().getSprite(Asset::Image::tile)->texture);
					mRenderData.back()->setPos(sf::Vector2f(origin.x + (textureSize.x * width * SCALE), origin.y + (textureSize.y * height * SCALE)));
					mRenderData.back()->getSprite()->setScale(4.0f, 4.0f);
				}
				switch (layer)
				{
				case 1: //background/sky
					mRenderData.back()->getSprite()->setTextureRect(sf::IntRect(textureSize.x * 3, textureSize.y * 21, textureSize.x, textureSize.y));
					break;
				case 2: //floor
					mRenderData.back()->getSprite()->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
					mRenderData.back()->setRenderLayer(RenderLayer::floor);
					break;
				case 3: //hills
					mRenderData.back()->getSprite()->setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
					mRenderData.back()->setRenderLayer(RenderLayer::hills);
					mColliderData.emplace_back(std::make_unique<Collider>(CollisionLayer::floor));
					mColliderData.back()->setRidgidbody(sf::FloatRect(origin.x + (textureSize.x * width * SCALE), origin.y + (textureSize.y * height * SCALE), textureSize.x * SCALE, textureSize.y * SCALE));
					break;
				case 4: //CointTile
					mRenderData.back()->getSprite()->setTextureRect(sf::IntRect(textureSize.x * 24, textureSize.y * 0, textureSize.x, textureSize.y));
					mRenderData.back()->setRenderLayer(RenderLayer::hills);
					mColliderData.emplace_back(std::make_unique<Collider>(CollisionLayer::object, "CoinTile"));
					mColliderData.back()->setRidgidbody(sf::FloatRect(origin.x + (textureSize.x * width * SCALE), origin.y + (textureSize.y * height * SCALE), textureSize.x * SCALE, textureSize.y * SCALE));
					mObjectData.emplace_back(std::make_unique<CoinTile>("CoinTile", std::make_unique<Animator>(Make_NonOwnPtr(mRenderData.back().get()), 24, 26, 0.35f), std::move(mRenderData.back()), std::move(mColliderData.back())));
					break;
				case 5: //BrickTile
					mRenderData.back()->getSprite()->setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 0, textureSize.x, textureSize.y));
					mRenderData.back()->setRenderLayer(RenderLayer::hills);
					mColliderData.emplace_back(std::make_unique<Collider>(CollisionLayer::floor));
					mColliderData.back()->setRidgidbody(sf::FloatRect(origin.x + (textureSize.x * width * SCALE), origin.y + (textureSize.y * height * SCALE), textureSize.x * SCALE, textureSize.y * SCALE));
					break;
				default:
					break;
				}
			}
		}
		count++;
		index = 0;
	}
}

void Game::_initSound()
{
	mBackgroundSound.setBuffer(ServiceLocator::instance().getSound(Asset::Sound::background)->mSoundBuffer);
	mBackgroundSound.setLoop(true);
	mBackgroundSound.play();

	mMarioDieSound.setBuffer(ServiceLocator::instance().getSound(Asset::Sound::die)->mSoundBuffer);
}

void Game::_initPlayer()
{
	sf::Vector2u mariotextureSize = ServiceLocator::instance().getSprite(Asset::Image::mario)->spriteSize;
	mario = std::make_unique<Mario>("Mario"
									, RenderLayer::object, &ServiceLocator::instance().getSprite(Asset::Image::mario)->texture
									, mariotextureSize);
	mario->getRenderElement()->getSprite()->setTextureRect(sf::IntRect(mariotextureSize.x * 0, mariotextureSize.y * 0, mariotextureSize.x, mariotextureSize.y));
	mario->getRenderElement()->getSprite()->setScale(SCALE, SCALE);
}

void Game::_initEnemy()
{
	sf::Vector2u goombatextureSize = ServiceLocator::instance().getSprite(Asset::Image::goomba)->spriteSize;

	mObjectData.emplace_back(std::make_unique<Goomba>("Goomba"
		, RenderLayer::object, &ServiceLocator::instance().getSprite(Asset::Image::goomba)->texture
		, goombatextureSize));
	mObjectData.back()->getRenderElement()->getSprite()->setTextureRect(sf::IntRect(goombatextureSize.x * 3, goombatextureSize.y * 0, goombatextureSize.x, goombatextureSize.y));
	mObjectData.back()->setPos(sf::Vector2f(3700.0f, 400.0f));
	mObjectData.back()->getRenderElement()->getSprite()->setScale(SCALE, SCALE);

	mObjectData.emplace_back(std::make_unique<Goomba>("Goomba"
		, RenderLayer::object, &ServiceLocator::instance().getSprite(Asset::Image::goomba)->texture
		, goombatextureSize));
	mObjectData.back()->getRenderElement()->getSprite()->setTextureRect(sf::IntRect(goombatextureSize.x * 3, goombatextureSize.y * 0, goombatextureSize.x, goombatextureSize.y));
	mObjectData.back()->setPos(sf::Vector2f(3500.0f, 400.0f));
	mObjectData.back()->getRenderElement()->getSprite()->setScale(SCALE, SCALE);
}

void Game::_initFont()
{
	mGameEndText = std::make_unique<RenderElement>(&ServiceLocator::instance().getFont(Asset::Font::HUD)->mFont);
	mGameEndText->getText()->setCharacterSize(32);
	mGameEndText->getText()->setFillColor(sf::Color::White);
	mGameEndText->getText()->setStyle(sf::Text::Bold);
	mGameEndText->getText()->setPosition(mEndScreenOffset);
}

void Game::_gameOver()
{
	_initGameEnd("GAME OVER!");
}

void Game::_gameWin()
{
	_initGameEnd("YOU WIN!");
}

void Game::_initGameEnd(std::string_view endText)
{
	mGameEndText->getText()->setString(endText.data());
	mMainCamera->setFollowTarget(mGameEndText.get());
	mMainCamera->isClamp = false;
}
