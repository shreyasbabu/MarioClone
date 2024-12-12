#pragma once



namespace sf
{
	class Sprite;
}

enum class RenderLayer : int;

class IComponent
{
public:
	virtual ~IComponent() = default;
	virtual void update(float deltaTime) = 0;

	//Render
	virtual const sf::Sprite& draw() const
	{ 
		static sf::Sprite sprite;
		return sprite; 
	};
	virtual RenderLayer getRenderLayer() const 
	{ 
		return RenderLayer{};
	};


	//virtual collision()
};

