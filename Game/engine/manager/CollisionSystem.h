#pragma once

#include "engine/core/ISystem.h"
#include "engine/core/EnableAsService.h"

class Collider;

enum class CollisionLayer : int
{
	none = 0,
	background,
	floor,
	object
};

class CollisionSystem : public ISystem , public EnableAsService
{
public:
	CollisionSystem(NonOwnPtr<sf::RenderWindow> window);
	virtual ~CollisionSystem() override;

	void update(float deltaTime) override;

	//pesudo global functionaly
	void Subscribe(CollisionLayer layer, NonOwnPtr<Collider> obj) override;
	void UnSubscribe(CollisionLayer layer, NonOwnPtr<Collider> obj) override;
	void ChangeCollisionLayer(CollisionLayer currentLayer, CollisionLayer changeTo, NonOwnPtr<Collider> obj) override;

private:
	std::map <CollisionLayer, std::list<NonOwnPtr<Collider>>> mCollidersList;
	std::vector<CollisionLayer> mCollisionOrder{ CollisionLayer::background, CollisionLayer::floor, CollisionLayer::object };
};

