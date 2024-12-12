#include "Precompiled.h"

#include "CollisionSystem.h"
#include "engine/component/Collider.h"

CollisionSystem::CollisionSystem(NonOwnPtr<sf::RenderWindow> window)
	:ISystem(window)
{
	ServiceLocator::instance().RegisterService(ServiceType::CollisionSystem, this);

	mCollidersList.emplace(CollisionLayer::none, std::list<NonOwnPtr<Collider>>());
	for (auto&& layer : mCollisionOrder)
	{
		mCollidersList.emplace(layer, std::list<NonOwnPtr<Collider>>());
	}
}

CollisionSystem::~CollisionSystem()
{
	ServiceLocator::instance().UnregisterService(ServiceType::CollisionSystem);
}

void CollisionSystem::update(float deltaTime)
{
	//final idea would be to check only tiles around the object i.e the tiles the object can collide with around it (scales with size)


	for (auto&& obj : mCollidersList[CollisionLayer::object])
	{
		if (obj->getName() == "Mario" || obj->getName() == "Goomba" )
		{
			for (auto&& tile : mCollidersList[CollisionLayer::floor])
			{
				sf::FloatRect outRect;
				if (obj->getRidgidbody().intersects(tile->getRidgidbody(), outRect))
				{
					obj->onCollision(tile, outRect);
				}
			}
		}
		for (auto&& otherObj : mCollidersList[CollisionLayer::object])
		{
			sf::FloatRect outRect;
			if (obj->getRidgidbody().intersects(otherObj->getRidgidbody(), outRect) && &obj != &otherObj)
			{
				obj->onCollision(otherObj, outRect);
			}
		}
	}
}

void CollisionSystem::Subscribe(CollisionLayer layer, NonOwnPtr<Collider> obj)
{
	mCollidersList[layer].emplace_back(std::move(obj));
}

void CollisionSystem::UnSubscribe(CollisionLayer layer, NonOwnPtr<Collider> obj)
{
	mCollidersList[layer].remove(obj);
}

void CollisionSystem::ChangeCollisionLayer(CollisionLayer currentLayer, CollisionLayer changeTo, NonOwnPtr<Collider> obj)
{
	UnSubscribe(currentLayer, obj);
	Subscribe(changeTo, obj);
}
