#pragma once

class GameObject;

class GameObjectManager : public EnableAsService
{
public:
	GameObjectManager();
	~GameObjectManager() override;

	void update(float deltaTime);

	//pesudo global functionaly
	void Subscribe(NonOwnPtr<GameObject> obj) override;
	void UnSubscribe(NonOwnPtr<GameObject> obj) override;

private:
	void _purgeObjects();

	std::list<NonOwnPtr<GameObject>> mObjectList;
	std::list<NonOwnPtr<GameObject>> mRemoveList;
};

