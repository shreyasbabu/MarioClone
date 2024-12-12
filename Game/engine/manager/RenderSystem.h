#pragma once

#include "engine/core/ISystem.h"
#include "engine/core/EnableAsService.h"

class Camera;

enum class RenderLayer : int
{
	none = 0,
	background,
	floor,
	hills,
	object,
	HUD,
};

class RenderSystem : public ISystem , public EnableAsService
{
public:
	RenderSystem(NonOwnPtr<sf::RenderWindow> window);
	virtual ~RenderSystem() override;

	void update(float deltaTime) override;

	//pesudo global functionaly
	void Subscribe(RenderLayer layer, NonOwnPtr<RenderElement> obj) override;
	void UnSubscribe(RenderLayer layer, NonOwnPtr<RenderElement> obj) override;
	void ChangeRenderLayer(RenderLayer current, RenderLayer changeTo, NonOwnPtr<RenderElement> obj) override;
	NonOwnPtr<Camera> getMainCamera() override;

private:
	void _initLayers();
	void _drawElements();

	std::unique_ptr<Camera> mMainCamera;
	std::map <RenderLayer, std::list<NonOwnPtr<RenderElement>>> mRenderObjectList;
	const std::vector<RenderLayer> mLayerOrder{RenderLayer::background, RenderLayer::floor, RenderLayer::hills, RenderLayer::object };

};