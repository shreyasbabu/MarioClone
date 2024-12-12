#pragma once

#include "engine/component/GameObject.h"

class Animator;
class Collider;
class RenderElement;

class CoinTile : public GameObject
{
public:
	CoinTile(std::string_view name, std::unique_ptr<Animator>&& animator, std::unique_ptr<RenderElement>&& element, std::unique_ptr<Collider>&& collider);
	 ~CoinTile() override = default;

	void update(float deltaTime) override;
private:
	void _initCollisionLogic();

	sf::Sound mCoinSound;
	std::unique_ptr<Animator> mAnimator;
	std::unique_ptr<Collider> mCollider;
	bool isUsed = false;
};

