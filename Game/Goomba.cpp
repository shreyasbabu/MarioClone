#include "Precompiled.h"
#include "Goomba.h"

Goomba::Goomba(std::string_view name, RenderLayer layer, const NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size)
	: Actor(name, layer, texture, size)
	, mAnimator(std::make_unique<Animator>(std::move(getRenderElement()), 0, 0, 0.5f))
{
	mAnimator->setAnimationState(AnimationState::STATE_ONE, 3, 4);
	mDieSound.setBuffer(ServiceLocator::instance().getSound(Asset::Sound::stomp)->mSoundBuffer);
}

void Goomba::update(float deltaTime)
{
	if (!mIsDead)
	{
		mPosition.x += mSpeed * deltaTime * mDirection;
		Actor::update(deltaTime);

	}
	mAnimator->update(deltaTime);

	if (mIsDead)
	{
		currentDeathTimer += deltaTime;
		if (currentDeathTimer > deathMaxTimer)
		{
			this->~Goomba();
		}
	}
}

void Goomba::_resolveTopCollision(std::string_view other)
{
}

void Goomba::_resolveBottomCollision(std::string_view other)
{
	if (other == "Mario")
	{
		mAnimator->setAnimationState(AnimationState::STATE_ZERO, 5, 5);
		mIsDead = true;
		mDieSound.play();
	}
}

void Goomba::_resolveLeftCollision(std::string_view other)
{
	if (other != "Mario")
	{
		mDirection < 0 ? mDirection = 1 : mDirection = -1;
	}
}

void Goomba::_resolveRightCollision(std::string_view other)
{
	if (other != "Mario")
	{
		mDirection < 0 ? mDirection = 1 : mDirection = -1;
	}
}
