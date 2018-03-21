#pragma once

#include "GameObject.h"
#include "Pawn.h"

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
	std::vector<GameObject*> GetGameObjectLibrary() { return GameObjectLibrary; }

	std::vector<GameObject*> GameObjectLibrary;
	
	void PushPawn(Pawn* pwn);
	Pawn* FindPawnByName(std::string nam);
	std::vector<Pawn*> FindPawnsByName(std::string nam);
	std::vector<Pawn*> GetPawnLibrary() { return PawnLibrary; }

	std::vector<Pawn*> PawnLibrary;

};

