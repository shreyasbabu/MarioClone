#pragma once

#include "game/Actor.h"

class Mario : public Actor
{
public:
	Mario(std::string_view name, RenderLayer layer, const NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size);
	~Mario() = default;

	void update(float deltaTime) override;
	void Jump();
	bool isJumping() const;
	bool isDead() const;
	NonOwnPtr<Animator> getAnimator() const;


private:
	void _resolveTopCollision(std::string_view other) override;
	void _resolveBottomCollision(std::string_view other) override;
	void _resolveLeftCollision(std::string_view other) override;
	void _resolveRightCollision(std::string_view other) override;
	void _die();
	void _clampLevelMovement();

	sf::Sound mJumpSound;
	sf::Sound mDieSound;
	std::unique_ptr<Animator> mAnimator;
	bool isJump = false;
	float mJumpHeight = 0.0f;
	constexpr static float mJumpdecleration = 0.005f;
	constexpr static float mMaxJumpHeight = -2.00f;
};

