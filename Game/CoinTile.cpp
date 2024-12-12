#include "Precompiled.h"

#include "CoinTile.h"

#include "engine/component/Animator.h"

CoinTile::CoinTile(std::string_view name, std::unique_ptr<Animator>&& animator, std::unique_ptr<RenderElement>&& element, std::unique_ptr<Collider>&& collider)
	: GameObject(name, std::move(element))
	, mAnimator(std::move(animator))
	, mCollider(std::move(collider))
{
	_initCollisionLogic();
	mAnimator->setAnimationState(AnimationState::STATE_ONE, 24, 26);
	mCoinSound.setBuffer(ServiceLocator::instance().getSound(Asset::Sound::coin)->mSoundBuffer);
}

void CoinTile::update(float deltaTime)
{
	mAnimator->update(deltaTime);
}

void CoinTile::_initCollisionLogic()
{
	mCollider->setCollisionLogic(std::move([this](NonOwnPtr<Collider> other, const sf::FloatRect& collisionRect) 
	{
		if (!other.isNull())
		{
			const sf::FloatRect otherCollisionRect = other->getRidgidbody();
			if (collisionRect.height < collisionRect.width) 
			{
				const float deltaRight = std::abs(otherCollisionRect.left - collisionRect.left);
				const float deltaLeft = std::abs((otherCollisionRect.left + otherCollisionRect.width) - collisionRect.left);
				// left collision 
				if (deltaLeft < deltaRight) 
				{
				}
				// right collision
				else 
				{
					if (!isUsed)
					{
						setPos(sf::Vector2f(getPos().x, otherCollisionRect.top - 35.0f));
						mAnimator->setAnimationState(AnimationState::STATE_ZERO, 27, 27);
						isUsed = true;
						mCoinSound.play();
					}
				}
			}
			else
			{
				const float deltaTop = std::abs(otherCollisionRect.top - collisionRect.top);
				const float deltaBottom = std::abs((otherCollisionRect.top + otherCollisionRect.height) - collisionRect.top);
				// Top collision 
				if (deltaTop < deltaBottom) 
				{

				}
				// Bottom collision
				else 
				{
				}
			}
		}
	}));
}
