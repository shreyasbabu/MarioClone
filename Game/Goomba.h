#pragma once

#include "game/Actor.h"

class Goomba : public Actor
{
public:
	Goomba(std::string_view name, RenderLayer layer, const NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size);
	~Goomba() override = default;

	void update(float deltaTime) override;

private:
	void _resolveTopCollision(std::string_view other) override;
	void _resolveBottomCollision(std::string_view other) override;
	void _resolveLeftCollision(std::string_view other) override;
	void _resolveRightCollision(std::string_view other) override;

	sf::Sound mDieSound;
	std::unique_ptr<Animator> mAnimator;
	float mSpeed = 0.25f;
	int mDirection = 1;
	float currentDeathTimer = 0.0f;
	const float deathMaxTimer = 1250.0f;
};

