#include "Precompiled.h"

#include "GameObject.h"

GameObject::GameObject()
{
	_subscribeToManagers();
}

GameObject::GameObject(std::string_view name, RenderLayer layer, NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size)
	: mName(name)
	, mRenderElement(std::make_unique<RenderElement>(layer, texture, size))
{
	_subscribeToManagers();
}

GameObject::GameObject(std::string_view name, std::unique_ptr<RenderElement>&& elemen)
	: mName(name)
	, mRenderElement(std::move(elemen))
{
		_subscribeToManagers();
}

GameObject::~GameObject()
{
	_unsubscribeFromManagers();
}

void GameObject::update(float deltaTime)
{
	if(mRenderElement)
	{
		mRenderElement->setPos(sf::Vector2f(mPosition.x - getHalfImageSize().x, mPosition.y - getHalfImageSize().y));
	}
}

std::string_view GameObject::getName() const
{
	return mName;
}

void GameObject::setName(std::string_view name)
{
	mName = name;
}

const sf::Vector2f& GameObject::getPos() const
{
	return mPosition;
}

void GameObject::setPos(const sf::Vector2f& pos)
{
	mPosition = pos;
}

void GameObject::setRenderElement(std::unique_ptr<RenderElement> renderElement)
{
	mRenderElement = std::move(renderElement);
}

NonOwnPtr<RenderElement> GameObject::getRenderElement() const
{
	return mRenderElement.get();
}

const sf::Vector2u& GameObject::getHalfImageSize() const
{
	if (mRenderElement)
	{
		return mRenderElement->getHalfImageSize();
	}
	return mHalfImgSize; // better way than lazy staic return??
}

void GameObject::setScale(float x, float y)
{
	if (mRenderElement)
	{
		mRenderElement->setScale(x, y);
	}
}

void GameObject::_subscribeToManagers()
{
	ServiceLocator::instance().Subscribe(ServiceType::GameObjectManager, this);
}

void GameObject::_unsubscribeFromManagers()
{
	ServiceLocator::instance().Unsubscribe(ServiceType::GameObjectManager, this);
}
