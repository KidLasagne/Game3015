#pragma once

#include "GameObjectManager.h"

class Juggernaut
{
public:
	Juggernaut();
	~Juggernaut();

	void Initialize();
	void Beginning();
	void MainLoop();
	GameObjectManager GetGameObjectManager() { return Manager; }
	void RenderTheWindow();
	void UserInput(float x, float y, GameObject *First, GameObject *Second, GameObject *Third, GameObject *Fourth, int MoveWhich);
	//GameObject* SpawnNewObject(float newX, float newY, float scale, std::string name, sf::Color fillCol, float radius);
	//GameObject* SpawnNewObject();

	GameObjectManager Manager;
};

