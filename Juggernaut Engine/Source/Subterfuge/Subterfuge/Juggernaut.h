#pragma once

#include "GameObjectManager.h"
#include <windows.h>
#include <stdio.h>

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

	GameObjectManager Manager;
	bool ExceedsRequirements;
};

