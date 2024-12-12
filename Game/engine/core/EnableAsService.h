#pragma once
/*
	- I am not a fan of having multiple singletons
	- This class acts as a pusedo global functions holder,
	- (I think) This design is as a good compromise between singletons vs passing around handlers all over the place
	- This approch also means we need to consciously make a decision to expose a function globally
	- Another benifit is we get to see all the global calls in one place
*/

namespace Asset
{
	enum class Image;
	enum class Sound;
	enum class Font;
}

class Camera;
class Collider;
class GameObject;
class RenderElement;
struct SpriteComponent;
struct SoundComponent;
struct FontComponent;
enum class RenderLayer : int;
enum class CollisionLayer : int;
enum class GameInput : int;

// cannot mark function as pure virtual as we dont need other classes to have unnecessery overrides;
class EnableAsService
{
public:
	virtual ~EnableAsService() = default;

	//GameObjectManager
	virtual void Subscribe(NonOwnPtr<GameObject> obj) {};
	virtual void UnSubscribe(NonOwnPtr<GameObject> obj) {};

	//RenderSystem
	virtual void Subscribe(RenderLayer layer, NonOwnPtr<RenderElement> obj) {};
	virtual void UnSubscribe(RenderLayer layer, NonOwnPtr<RenderElement> obj) {};
	virtual void ChangeRenderLayer(RenderLayer currentLayer, RenderLayer changetTo, NonOwnPtr<RenderElement> obj) {};
	virtual NonOwnPtr<Camera> getMainCamera() { return nullptr; };

	//CollisionSystem
	virtual void Subscribe(CollisionLayer layer, NonOwnPtr<Collider> obj) {};
	virtual void UnSubscribe(CollisionLayer layer, NonOwnPtr<Collider> obj) {};
	virtual void ChangeCollisionLayer(CollisionLayer currentLayer, CollisionLayer changeTo, NonOwnPtr<Collider> obj) {};

	//InputHandler
	virtual GameInput getKeyInput() const { return static_cast<GameInput>(0); };

	//AssetManager
	virtual NonOwnPtr<SpriteComponent> getImage(Asset::Image img) { return nullptr; };
	virtual	NonOwnPtr<SoundComponent> getSound(Asset::Sound sound) { return nullptr; };
	virtual	NonOwnPtr<FontComponent> getFont(Asset::Font sound) { return nullptr; };

protected:
	EnableAsService() = default;
	EnableAsService(const EnableAsService& other) = default;
	EnableAsService& operator=(const EnableAsService& other) = default;
	EnableAsService(EnableAsService&& other) = default;
	EnableAsService& operator=(EnableAsService&& other) = default;
};

using Service = EnableAsService;