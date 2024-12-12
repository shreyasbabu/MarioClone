#pragma once

#include "engine/component/GameObject.h"
#include "engine/component/Animator.h"

class Actor : public GameObject
{
public:
	Actor(std::string_view name, RenderLayer layer, const NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size);
	~Actor() override = default;

	void update(float deltaTime) override;
	
	NonOwnPtr<Collider> getCollider() const;

protected:
	virtual void _resolveTopCollision(std::string_view other) {};
	virtual void _resolveBottomCollision(std::string_view other) {};
	virtual void _resolveLeftCollision(std::string_view other) {};
	virtual void _resolveRightCollision(std::string_view other) {};

	std::unique_ptr<Collider> mCollider;
	bool mIsDead = false;
private:
	void _initCollisionLogic();
};

