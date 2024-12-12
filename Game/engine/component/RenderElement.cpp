#include "Precompiled.h"

#include "RenderElement.h"

RenderElement::RenderElement(RenderLayer layer, NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size)
	: mRenderLayer(layer)
	, mImageSize(size)
	, mHalfImageSize(size.x * 0.5f, size.y * 0.5f)
	, mSptire(std::make_unique<sf::Sprite>(*texture))
{
	ServiceLocator::instance().Subscribe(ServiceType::RenderSystem, mRenderLayer, this);
	mSptire->setOrigin(mImageSize.x * 0.5f, mImageSize.y * 0.5f);
	//debugRectangle.setOrigin(mImageSize.x * 0.5f, mImageSize.y * 0.5f);
}

RenderElement::RenderElement(NonOwnPtr<sf::Font> font, RenderLayer layer)
	: mRenderLayer(layer)
	, mText(std::make_unique<sf::Text>())
	, isText(true)
{
	ServiceLocator::instance().Subscribe(ServiceType::RenderSystem, mRenderLayer, this);
	mText->setFont(*font);

}

RenderElement::~RenderElement()
{
	ServiceLocator::instance().Unsubscribe(ServiceType::RenderSystem, mRenderLayer,  this);
}

void RenderElement::update(float deltTime)
{
}

const sf::Sprite& RenderElement::draw() const
{
	return *mSptire;
}

RenderLayer RenderElement::getRenderLayer() const
{
	return mRenderLayer;
}

void RenderElement::setRenderLayer(RenderLayer layer)
{
	ServiceLocator::instance().ChangeRenderSystem(mRenderLayer, layer, this);
	mRenderLayer = layer;
}

void RenderElement::setTexture(const NonOwnPtr<sf::Texture> texture)
{
	mSptire.reset();
	mSptire = std::make_unique<sf::Sprite>(*texture);
}

const sf::Vector2f& RenderElement::getPos() const
{
	if (!isText)
	{
		return mSptire->getPosition();
	}
	else
	{
		return mText->getPosition();
	}
}

void RenderElement::setPos(const sf::Vector2f& pos)
{
	mSptire->setPosition(pos);
	//debugRectangle.setPosition(pos);
}

const NonOwnPtr<sf::Sprite> RenderElement::getSprite() const
{
	return mSptire.get();
}

NonOwnPtr<sf::Sprite> RenderElement::getSprite()
{
	return mSptire.get();
}

NonOwnPtr<sf::Text> RenderElement::getText()
{
	return mText.get();
}

const sf::Vector2u& RenderElement::getHalfImageSize() const
{
	return mHalfImageSize;
}

const sf::Vector2u& RenderElement::getImageSize() const
{
	return mImageSize;
}

void RenderElement::setImageSize(sf::Vector2u size)
{
	mImageSize = std::move(size);
}

void RenderElement::setScale(float x, float y)
{
	mSptire->setScale(x, y);
	//mImageSize.x *= x;
	//mImageSize.y *= y;
	//mHalfImageSize.x *= x;
	//mHalfImageSize.y *= y;
}

const sf::Drawable& RenderElement::debugDraw()
{
	debugRectangle.setSize(sf::Vector2f(mImageSize.x, mImageSize.y));
	debugRectangle.setScale(4.0f, 4.0f);
	debugRectangle.setOutlineColor(sf::Color::Red);
	debugRectangle.setOutlineThickness(1);
	return debugRectangle;
}
