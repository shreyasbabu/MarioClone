#pragma once

#include "Precompiled.h"
#include "manager/AssetManager.h"

class AssetManager;
class Camera;
class CollisionSystem;
class GameObject;
class GameObjectManager;
class RenderSystem;
struct SpriteComponente;
enum class GameInput : int;

enum class ServiceType : int
{
	GameObjectManager = 0,
	RenderSystem,
	CollisionSystem,
	AudioManager,
	InputHandler,
	AssetManager,
	Game,
	HUD
};

class ServiceLocator
{
public:
	~ServiceLocator() = default;
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) = delete;

	static ServiceLocator& instance()
	{
		static ServiceLocator _instance;
		return _instance;
	}
	inline void RegisterService(ServiceType service, NonOwnPtr<Service> system);
	inline void UnregisterService(ServiceType service);

	// all of the functions below can be converted to some form of template, can even make use of perfect forwarding here
	//.....but I prefer long readable code rather than short cryptic code ....TBD

	template<typename...Arg>
	inline void Subscribe(ServiceType type, Arg&&...pack);
	template<typename...Arg>
	inline void Unsubscribe(ServiceType type, Arg&&...pack);

	//Render System
	inline void ChangeRenderSystem(RenderLayer current, RenderLayer to, NonOwnPtr<RenderElement> obj);
	inline NonOwnPtr<Camera> getMainCamera();
	
	//InputHandler
	inline GameInput getKeyInput();
	
	//AssetManager
	inline NonOwnPtr<SpriteComponent> getSprite(Asset::Image img);
	inline NonOwnPtr<SoundComponent> getSound(Asset::Sound sound);
	inline NonOwnPtr<FontComponent> getFont(Asset::Font font);

	inline bool GameWin();
	inline bool GameOver();

	bool mIsWin = false;
	bool mIsLoose = false;

private:
	ServiceLocator() = default;

	std::map<ServiceType, NonOwnPtr<Service>> mServices;

};

#include "ServiceLocator.inl"

