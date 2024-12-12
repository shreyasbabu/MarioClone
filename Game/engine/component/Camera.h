#pragma once

#include "Precompiled.h"
#include "component/RenderElement.h"

class Camera
{
public:
	void update(float deltaTime)
	{
		sf::Vector2f currentPos = mFollowTarget->getPos();
		if (isClamp)
		{
			uint32_t scaledLevelWidth = LEVEL_WIDTH * SCALE * 16;
			if (currentPos.x - (SCREEN_WIDTH * 0.5f) <= 0.0f)
			{
				currentPos.x = SCREEN_WIDTH * 0.5f;
			}
			else if (currentPos.x + (SCREEN_WIDTH * 0.5f) >= scaledLevelWidth)
			{
				currentPos.x = scaledLevelWidth - (SCREEN_WIDTH * 0.5f);
			}
			if (currentPos.y - (SCREEN_HEIGHT * 0.5f) <= 0.0f)
			{
				currentPos.y = SCREEN_HEIGHT * 0.5f;
			}
			else if (currentPos.y + (SCREEN_HEIGHT * 0.5f) >= SCREEN_HEIGHT)
			{
				currentPos.y = SCREEN_HEIGHT * 0.5f;
			}
		}
		mCamera.setCenter(currentPos);
	}

	void setFollowTarget(NonOwnPtr<RenderElement> target)
	{
		mFollowTarget = std::move(target);
	}


	sf::View mCamera;
	NonOwnPtr<RenderElement> mFollowTarget;
	bool isClamp = true;
};

