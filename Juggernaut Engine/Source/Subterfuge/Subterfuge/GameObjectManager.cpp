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
	for (auto& pawn : PawnLibrary)
	{
		pawn->getObject()->Awake();
	}
}

void GameObjectManager::Start()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->Start();
	}
	for (auto& pawn : PawnLibrary)
	{
		pawn->getObject()->Start();
	}
}

void GameObjectManager::Update()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->Update();
	}
	for (auto& pawn : PawnLibrary)
	{
		pawn->getObject()->Update();
	}
}

void GameObjectManager::LateUpdate()
{
	for (auto& game_object : GameObjectLibrary)
	{
		game_object->LateUpdate();
	}
	for (auto& pawn : PawnLibrary)
	{
		pawn->getObject()->LateUpdate();
	}
}

void GameObjectManager::PushPawn(Pawn* pwn)
{
	PawnLibrary.push_back(pwn);
	std::cout << "Pushing Pawn." << std::endl;
}

Pawn* GameObjectManager::FindPawnByName(std::string nam)
{
	for (auto& pawn : PawnLibrary)
	{
		if ( pawn->getObject()->GetName() == nam)
		{
			return pawn;
		}
	}

	return NULL;
}

std::vector<Pawn*> GameObjectManager::FindPawnsByName(std::string nam)
{
	std::vector<Pawn*> ObjList;

	for (auto& pawn : PawnLibrary)
	{
		if (pawn->getObject()->GetName() == nam)
		{
			ObjList.push_back(pawn);
		}
	}

	return ObjList;
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

