#include "Precompiled.h"

#include "GameObjectManager.h"
#include "engine/component/GameObject.h"

GameObjectManager::GameObjectManager()
{
	ServiceLocator::instance().RegisterService(ServiceType::GameObjectManager, this);
}

GameObjectManager::~GameObjectManager()
{
	ServiceLocator::instance().UnregisterService(ServiceType::GameObjectManager);
}

void GameObjectManager::update(float deltaTime)
{
	for (auto&& obj : mObjectList)
	{
		if (!obj.isNull())
		{
			obj->update(deltaTime);
		}
	}
	_purgeObjects();
}
void GameObjectManager::Subscribe(NonOwnPtr<GameObject> obj)
{
	mObjectList.emplace_back(std::move(obj));
}

void GameObjectManager::UnSubscribe(NonOwnPtr<GameObject> obj)
{
	mRemoveList.emplace_back(std::move(obj));
}

void GameObjectManager::_purgeObjects()
{
	if (mRemoveList.size() > 0)
	{
		for (auto&& obj : mRemoveList)
		{
			mObjectList.remove(mRemoveList.back());
		}
		mRemoveList.clear();
	}
}
