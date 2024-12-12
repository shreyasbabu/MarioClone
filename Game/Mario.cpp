#include "Precompiled.h"

#include "Mario.h"

Mario::Mario(std::string_view name, RenderLayer layer, const NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size)
	: Actor(name, layer, texture, size)
	, mAnimator(std::make_unique<Animator>(std::move(getRenderElement()), 0, 0,  PLAYER_SPEED * 0.15f))
{
	mJumpSound.setBuffer(ServiceLocator::instance().getSound(Asset::Sound::jump)->mSoundBuffer);
	mDieSound.setBuffer(ServiceLocator::instance().getSound(Asset::Sound::die)->mSoundBuffer);
}

void Mario::update(float deltaTime)
{
	if (mJumpHeight <= 0.0f)
	{
		mJumpHeight += (mJumpdecleration * deltaTime);
	}

	mPosition.y = mPosition.y + (mJumpHeight * deltaTime);
	_clampLevelMovement();
	
	Actor::update(deltaTime);

	if(mAnimator)
	{
		mAnimator->update(deltaTime);
	}
}

void Mario::Jump()
{
	if (isJump == false && mJumpHeight >= 0.0f)
	{
		isJump = true;
		mJumpHeight = mMaxJumpHeight;
		mJumpSound.play();
	}
}

bool Mario::isJumping() const
{
	return isJump;
}

bool Mario::isDead() const
{
	return mIsDead;
}

NonOwnPtr<Animator> Mario::getAnimator() const
{
	return Make_NonOwnPtr(mAnimator.get());
}

void Mario::_resolveTopCollision(std::string_view other)
{
	if (other == "Goomba")
	{
		mJumpHeight = mMaxJumpHeight * 0.75f;
	}
	if (isJump == true)
	{
		isJump = false;
	}
}

void Mario::_resolveBottomCollision(std::string_view other)
{
}

void Mario::_resolveLeftCollision(std::string_view other)
{
	if (other == "Goomba")
	{
		_die();
	}
}

void Mario::_resolveRightCollision(std::string_view other)
{
	if (other == "Goomba")
	{
		_die();
	}
}

void Mario::_die()
{
	mIsDead = true;
	isJump = false;
	getAnimator()->setAnimationState(AnimationState::STATE_TWO, 6, 6);
	mDieSound.play();
	mJumpHeight = mMaxJumpHeight;
	ServiceLocator::instance().mIsLoose = true;
}

void Mario::_clampLevelMovement()
{
	if (mPosition.x <= getHalfImageSize().x)
	{
		mPosition.x = getHalfImageSize().x;
	}
	if (mPosition.x >= SCALED_LEVEL_WIDTH - getHalfImageSize().x)
	{
		mPosition.x = SCALED_LEVEL_WIDTH - getHalfImageSize().x;
		ServiceLocator::instance().mIsWin = true;
	}
}
