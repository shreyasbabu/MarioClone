#pragma once

#include "engine/manager/RenderSystem.h"

class RenderElement 
{
public:
	RenderElement(RenderLayer layer, NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size);
	RenderElement(NonOwnPtr<sf::Font> font, RenderLayer layer = RenderLayer::object);
	~RenderElement();

	virtual void update(float deltTime);
	virtual const sf::Sprite& draw() const;

	RenderLayer getRenderLayer() const;
	void setRenderLayer(RenderLayer layer);
	
	void setTexture(const NonOwnPtr<sf::Texture> texture);
	const NonOwnPtr<sf::Sprite> getSprite() const;
	NonOwnPtr<sf::Sprite> getSprite();
	NonOwnPtr<sf::Text> getText();
	
	const sf::Vector2f& getPos() const;
	void setPos(const sf::Vector2f& pos);
	const sf::Vector2u& getHalfImageSize() const;
	const sf::Vector2u& getImageSize() const;
	void setImageSize(sf::Vector2u size);
	void setScale(float x, float y);

	const sf::Drawable& debugDraw();

	bool isText = false;
private:
	sf::Vector2u mImageSize;
	sf::Vector2u mHalfImageSize;
	std::unique_ptr<sf::Sprite> mSptire;
	std::unique_ptr<sf::Text> mText;
	RenderLayer mRenderLayer = RenderLayer::none;

	sf::RectangleShape debugRectangle{};
};

