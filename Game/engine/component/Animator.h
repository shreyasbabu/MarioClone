#pragma once

enum class  AnimationState : int
{
	STATE_ZERO = 0,
	STATE_ONE = 1,
	STATE_TWO = 2,
	STATE_THREE = 3,
	STATE_FOUR = 4
};

class Animator
{
public:
	Animator(NonOwnPtr<RenderElement> element, uint16_t startIndex, uint16_t endIndex, float switchTime);
	void update(float deltaTime);

	void setAnimationState(AnimationState state, uint16_t startIndex, uint16_t endIndex);
	AnimationState getAnimationState() const;

private:

	void _changeAnimationState(float detaTime);
	void _idleAnimation();

	AnimationState mAnimationState = AnimationState::STATE_ZERO;
	NonOwnPtr<RenderElement> mRenderElement;
	uint16_t mStartIndex = 0;
	uint16_t mEndIndex = 0;
	uint16_t mCurrentImageCount = 0;
	float mSwitchTime = 0.0f;
	float mCurrentTime = 0.0f;
};

