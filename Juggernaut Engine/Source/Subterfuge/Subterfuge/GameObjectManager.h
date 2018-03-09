#pragma once

#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void PushGameObject(GameObject* gam);
	GameObject* FindGameObjectByName(std::string nam);
	std::vector<GameObject*> FindGameObjectsByName(std::string nam);

	std::vector<GameObject*> GameObjectLibrary;

};

