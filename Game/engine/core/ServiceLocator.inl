#include "ServiceLocator.h"

template<typename ...Arg>
inline void ServiceLocator::Subscribe(ServiceType type, Arg&& ...pack)
{
	mServices[type]->Subscribe(std::forward<Arg>(pack)...);
}

template<typename ...Arg>
inline void ServiceLocator::Unsubscribe(ServiceType type, Arg&& ...pack)
{
	mServices[type]->UnSubscribe(std::forward<Arg>(pack)...);
}

inline void ServiceLocator::ChangeRenderSystem(RenderLayer current, RenderLayer to, NonOwnPtr<RenderElement> obj)
{
	mServices[ServiceType::RenderSystem]->ChangeRenderLayer(current, to, obj);
}

inline void ServiceLocator::RegisterService(ServiceType service, NonOwnPtr<Service> system)
{
	mServices.emplace(service, std::move(system));
}

inline void ServiceLocator::UnregisterService(ServiceType service)
{
	mServices.erase(service);
}

inline NonOwnPtr<Camera> ServiceLocator::getMainCamera()
{
	return mServices[ServiceType::RenderSystem]->getMainCamera();
}

inline GameInput ServiceLocator::getKeyInput()
{
	return mServices[ServiceType::InputHandler]->getKeyInput();
}

inline NonOwnPtr<SpriteComponent> ServiceLocator::getSprite(Asset::Image img)
{
	return mServices[ServiceType::AssetManager]->getImage(img);
}

inline NonOwnPtr<SoundComponent> ServiceLocator::getSound(Asset::Sound sound)
{
	return mServices[ServiceType::AssetManager]->getSound(sound);
}

inline NonOwnPtr<FontComponent> ServiceLocator::getFont(Asset::Font font)
{
	return mServices[ServiceType::AssetManager]->getFont(font);

}

inline bool ServiceLocator::GameWin()
{
	return mIsWin;
}

inline bool ServiceLocator::GameOver()
{
	return mIsLoose;
}