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
	bool Subterfuge();
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
	Pawn::vectorBool SearchForConflicts(sf::Vector2i vectorDrawer[10], int &randyStoreX, int &randyStoreY);
	float generateRandom(float min, float max);
	void MoveXtoLastPosition(Pawn* pwn, sf::RenderWindow& win, sf::CircleShape circ);
	void ExitGame();

	int board[10][10];
	StorageNode Database[10][10];
	sf::Vector2f LastPosition;

	std::string DisplayString;
	
	GameObjectManager Manager;
	bool ExceedsRequirements;
};

