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
	//GameObject* SpawnNewObject(float newX, float newY, float scale, std::string name, sf::Color fillCol, float radius);
	//GameObject* SpawnNewObject();

	GameObjectManager Manager;
};

