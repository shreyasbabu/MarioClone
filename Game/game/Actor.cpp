#include "Precompiled.h"

#include "Actor.h"

Actor::Actor(std::string_view name, RenderLayer layer, const NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size)
	: GameObject(name, layer, texture, size)
	, mCollider(std::make_unique<Collider>(CollisionLayer::object, name))
{
	_initCollisionLogic();
}

void Actor::update(float deltaTime)
{
	mPosition.y = mPosition.y + (GRAVITY *  deltaTime);
	mCollider->setRidgidbody(sf::FloatRect(getPos().x - getHalfImageSize().x * SCALE
										, getPos().y - getHalfImageSize().y * SCALE
										, getRenderElement()->getImageSize().x * SCALE
										, getRenderElement()->getImageSize().y * SCALE));
	
	GameObject::update(deltaTime);
}

NonOwnPtr<Collider> Actor::getCollider() const
{
	return Make_NonOwnPtr(mCollider.get());
}

void Actor::_initCollisionLogic()
{
	mCollider->setCollisionLogic(std::move([this](NonOwnPtr<Collider> other, const sf::FloatRect& collisionRect) 
	{
		const std::string_view otherName = other->getName();
		if (!other.isNull() && !mIsDead)
		{
			const float height = collisionRect.height;
			const float width = collisionRect.width;
			const sf::FloatRect otherCollisionRect = other->getRidgidbody();
			// collision from left or right side
			if (width < height) 
			{
				const float deltaRight = std::abs(otherCollisionRect.left - collisionRect.left);
				const float deltaLeft = std::abs((otherCollisionRect.left + otherCollisionRect.width) - collisionRect.left);
				// left collision 
				if (deltaLeft < deltaRight) 
				{
					setPos(sf::Vector2f(otherCollisionRect.left + (otherCollisionRect.width + 33.0f), getPos().y));
					_resolveLeftCollision(otherName);
				}
				// right collision
				else 
				{
					setPos(sf::Vector2f(otherCollisionRect.left - 33.0f, getPos().y));
					_resolveRightCollision(otherName);
				}
			}
			else // collision from top or bottom side
			{
				const float deltaTop = std::abs(otherCollisionRect.top - collisionRect.top);
				const float deltaBottom = std::abs((otherCollisionRect.top + otherCollisionRect.height) - collisionRect.top);
				// Top collision 
				if (deltaTop < deltaBottom) 
				{
					setPos(sf::Vector2f(getPos().x, otherCollisionRect.top - 35.0f));
					_resolveTopCollision(otherName);
				}
				// Bottom collision
				else 
				{
					setPos(sf::Vector2f(getPos().x, otherCollisionRect.top + otherCollisionRect.height + 40.0f));
					_resolveBottomCollision(otherName);
				}
			}
		}
	}));
}
