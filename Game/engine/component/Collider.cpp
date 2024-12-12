#include "Precompiled.h"

#include "Collider.h"

Collider::Collider(CollisionLayer layer, std::string_view name)
	: mLayer(layer)
	, mName(name)
{
	ServiceLocator::instance().Subscribe(ServiceType::CollisionSystem, layer, this);
}

Collider::~Collider()
{
	ServiceLocator::instance().Unsubscribe(ServiceType::CollisionSystem, mLayer, this);
}

void Collider::update(float deltaTime)
{
}

void Collider::onCollision(NonOwnPtr<Collider> other, const sf::FloatRect& collisionRect)
{
	mCollisionLogic(other, collisionRect);
}

std::string_view Collider::getName() const
{
	return mName;
}

void Collider::setName(std::string_view name)
{
	mName = name;
}

const sf::FloatRect& Collider::getRidgidbody() const
{
	return mRidgeBody;
}

sf::FloatRect& Collider::getRidgidbody()
{
	return mRidgeBody;
}

void Collider::setRidgidbody(sf::FloatRect ridgidbody)
{
	mRidgeBody = std::move(ridgidbody);
}

void Collider::setCollisionLayer(CollisionLayer layer)
{
	mLayer = layer;
}

void Collider::setCollisionLogic(std::function<void(NonOwnPtr<Collider>, const sf::FloatRect&)> collisionLogic)
{
	mCollisionLogic = std::move(collisionLogic);
}
