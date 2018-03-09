#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Awake()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->Awake();
	}
}

void GameObjectManager::Start()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->Start();
	}
}

void GameObjectManager::Update()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->Update();
	}
}

void GameObjectManager::LateUpdate()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->LateUpdate();
	}
}

void GameObjectManager::PushGameObject(GameObject* gam)
{
	GameObjectLibrary.push_back(gam);
	std::cout << "Pushing Object." << std::endl;
	//std::cout << "Lib Size: " << GameObjectLibrary.size << std::endl;
}

GameObject* GameObjectManager::FindGameObjectByName(std::string nam)
{
	for (auto& game_object : GameObjectLibrary)
	{
		if (game_object->GetName() == nam)
		{
			return game_object;
		}
	}

	return NULL;
}

std::vector<GameObject*> GameObjectManager::FindGameObjectsByName(std::string nam)
{
	std::vector<GameObject*> ObjList;

	for (auto& game_object : GameObjectLibrary)
	{
		if (game_object->GetName() == nam)
		{
			ObjList.push_back(game_object);
		}
	}

	return ObjList;
}

