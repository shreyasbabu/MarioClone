#pragma once

#include "RenderElement.h"
#include "engine/component/Collider.h"

class RenderElement;

class GameObject
{

public:
	GameObject();
	GameObject(std::string_view name, RenderLayer layer, NonOwnPtr<sf::Texture> texture, const sf::Vector2u& size);
	GameObject(std::string_view name, std::unique_ptr<RenderElement>&& elemen);

	virtual ~GameObject();

	virtual void update(float deltaTime);
	std::string_view getName() const;
	void setName(std::string_view name);
	virtual const sf::Vector2f& getPos() const;
	virtual void setPos(const sf::Vector2f& pos);
	virtual void setRenderElement(std::unique_ptr<RenderElement> renderElement);
	virtual NonOwnPtr<RenderElement> getRenderElement() const;

	const sf::Vector2u& getHalfImageSize() const;
	virtual void setScale(float x, float y);

protected:
	sf::Vector2f mPosition{};

private:
	void _subscribeToManagers();
	void _unsubscribeFromManagers();

	sf::Vector2u mHalfImgSize{};
	std::unique_ptr<RenderElement> mRenderElement;
	std::string mName;
};

