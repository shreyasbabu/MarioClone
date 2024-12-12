#include "Precompiled.h"

#include "RenderSystem.h"
#include "engine/component/RenderElement.h"
#include "engine/component/Camera.h"

RenderSystem::RenderSystem(NonOwnPtr<sf::RenderWindow> window)
	:ISystem(window)
{
	ServiceLocator::instance().RegisterService(ServiceType::RenderSystem, this);
	_initLayers();
	mMainCamera = std::make_unique<Camera>();
	mMainCamera->mCamera.setSize(static_cast<sf::Vector2f>(window->getSize()));
}

RenderSystem::~RenderSystem()
{
	ServiceLocator::instance().UnregisterService(ServiceType::RenderSystem);
}

void RenderSystem::update(float deltaTime)
{
	if (mWindow.isNull())
	{
		return;
	}

	mWindow->clear();
	_drawElements();
	mWindow->setView(mMainCamera->mCamera);
	mMainCamera->update(deltaTime);
	mWindow->display();
}

void RenderSystem::Subscribe(RenderLayer layer, NonOwnPtr<RenderElement> obj)
{
	mRenderObjectList[layer].emplace_back(std::move(obj));
}

void RenderSystem::UnSubscribe(RenderLayer layer, NonOwnPtr<RenderElement> obj)
{
	mRenderObjectList[layer].remove(obj);
}

void RenderSystem::ChangeRenderLayer(RenderLayer currentLayer, RenderLayer changeTo, NonOwnPtr<RenderElement> obj)
{
	UnSubscribe(currentLayer, obj);
	Subscribe(changeTo, obj);
}

NonOwnPtr<Camera> RenderSystem::getMainCamera()
{
	return mMainCamera.get();
}

void RenderSystem::_initLayers()
{
	mRenderObjectList.emplace(RenderLayer::none, std::list<NonOwnPtr<RenderElement>>());
	for (auto&& layer : mLayerOrder)
	{
		mRenderObjectList.emplace(layer, std::list<NonOwnPtr<RenderElement>>());
	}
}

void RenderSystem::_drawElements()
{
	for (auto&& layerOrder : mLayerOrder)
	{
		for (auto&& renderElement : mRenderObjectList[layerOrder])
		{
			if (!renderElement.isNull())
			{
				if (!renderElement->isText)
				{
					mWindow->draw((renderElement->draw()));
					//mWindow->draw((renderElement->debugDraw()));
				}
				else
				{
					mWindow->draw((*renderElement->getText()));
				}
			}
		}
	}
}
