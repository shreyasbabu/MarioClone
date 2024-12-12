#pragma once

#include"engine/manager/CollisionSystem.h"

//enum class HitSides : uint8_t
//{
//	none,
//	top,
//	bottom,
//	left,
//	right
//};

class Collider
{
public:
	Collider(CollisionLayer layer, std::string_view name = "");
	~Collider();

	void update(float deltaTime);
	void onCollision(NonOwnPtr<Collider> other, const sf::FloatRect& collisionRect);
	
	std::string_view getName() const;
	void setName(std::string_view name);

	const sf::FloatRect& getRidgidbody() const;
	sf::FloatRect& getRidgidbody();
	//HitSides getSidesHit() const;
	//void resetHitsInfo();
	void setRidgidbody(sf::FloatRect ridgidbody);
	void setCollisionLayer(CollisionLayer layer);
	//void setCollisionLogic(std::function<HitSides(NonOwnPtr<Collider>, const sf::FloatRect&)> collisionLogic);
	void setCollisionLogic(std::function<void(NonOwnPtr<Collider>, const sf::FloatRect&)> collisionLogic);

	std::function<void(NonOwnPtr<Collider>,const sf::FloatRect&)> mCollisionLogic;
	//std::function<HitSides(NonOwnPtr<Collider>,const sf::FloatRect&)> mCollisionLogic;

private:
	std::string mName;
	sf::FloatRect mRidgeBody;
	CollisionLayer mLayer = CollisionLayer::floor;
	//HitSides mSidesHit = HitSides::none;
};