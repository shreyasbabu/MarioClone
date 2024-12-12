#include "Precompiled.h"

#include "Animator.h"
#include "engine/component/RenderElement.h"

Animator::Animator(NonOwnPtr<RenderElement> element, uint16_t startIndex, uint16_t endIndex, float switchTime)
	: mRenderElement(std::move(element))
	, mStartIndex(startIndex)
	, mEndIndex(endIndex)
	, mSwitchTime(switchTime)
	, mCurrentImageCount(startIndex)
{
}

void Animator::update(float deltaTime)
{
	switch (mAnimationState)
	{
	case AnimationState::STATE_ZERO:
		_changeAnimationState(deltaTime);
		break;
	case AnimationState::STATE_ONE:
		_changeAnimationState(deltaTime);
		break;
	case AnimationState::STATE_TWO:
		_changeAnimationState(deltaTime);
		break;
	case AnimationState::STATE_THREE:
		break;
	case AnimationState::STATE_FOUR:
		break;
	default:
		break;
	}

}

void Animator::setAnimationState(AnimationState state, uint16_t startIndex, uint16_t endIndex)
{
	if(state != mAnimationState)
	{
		//reset states
		mAnimationState = state;
		mStartIndex = startIndex;
		mCurrentImageCount = startIndex;
		mEndIndex = endIndex;
		mCurrentTime = mSwitchTime;
	}
}

AnimationState Animator::getAnimationState() const
{
	return mAnimationState;
}

void Animator::_idleAnimation()
{
	const sf::Vector2u imageSize = mRenderElement->getImageSize();
	mRenderElement->getSprite()->setTextureRect(sf::IntRect(imageSize.x * 0, imageSize.y * 0, imageSize.x, imageSize.y));
}

void Animator::_changeAnimationState(float detaTime)
{
	mCurrentTime += 0.00085f * detaTime;
	if (mCurrentTime >= mSwitchTime)
	{
		if (mCurrentImageCount > mEndIndex)
		{
			mCurrentImageCount = mStartIndex;
		}
		const sf::Vector2u imageSize = mRenderElement->getImageSize();
		mRenderElement->getSprite()->setTextureRect(sf::IntRect(imageSize.x * mCurrentImageCount, imageSize.y * 0, imageSize.x, imageSize.y));
		++mCurrentImageCount;
		mCurrentTime = 0.0f;
	}
}


