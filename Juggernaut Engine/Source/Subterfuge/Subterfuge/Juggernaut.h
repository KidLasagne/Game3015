#pragma once

#include "GameObjectManager.h"
#include <windows.h>
#include <stdio.h>
#include "Pawn.h"
#include "StorageNode.h"

#define arraySize 10

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
	void Subterfuge();
	void UserInput(float x, float y, GameObject *First, GameObject *Second, GameObject *Third, GameObject *Fourth, int MoveWhich);
	int myX;
	int myY;
	int boardSize;
	void SetBoardSize(int siz) { boardSize = siz; }
	int GetBoardSize() { return boardSize; }
	void TransmuteBoard(int bSize);
	void ShowBoard(sf::RenderWindow& win);
	void PrintBoard();
	void ShowText(std::string str, sf::RenderWindow& win);

	int board[10][10];
	StorageNode Database[10][10];

	std::string DisplayString;
	
	GameObjectManager Manager;
	bool ExceedsRequirements;
};

