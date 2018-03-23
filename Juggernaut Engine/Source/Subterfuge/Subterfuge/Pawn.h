#pragma once

#include "GameObject.h"
#include "StorageNode.h"
#include <ctime>
#include <random>
#include <chrono>

class Pawn
{
public:

	struct vectorBool
	{
		int x;
		int y;
		bool action;
		int myXPos;
		int myYPos;
		bool turnOver;
	};

	Pawn();
	~Pawn();

	int myX;
	int myY;

	float strength;
	float dexterity;
	float magic;
	int mp;
	int hp;
	int team;
	int attacks;
	int movementLeft;
	int unitType;
	float turnOrderPoints;
	int rawMovement;
	int rawAttacks;

	std::string Attack(Pawn &other);
	void Move(int xPos, int yPos, int board[10][10]);
	void UpdatePosition();
	bool IsTurnOver();
	vectorBool DoUserInput(sf::Event event, int board[10][10], StorageNode database[10][10]);
	void Die();
	float Pawn::rand_FloatRange(float a, float b);
	float generateRandom(float min, float max);
	void ShedTime();
	void SetClass(int i);

	//void CopyArray(int *arrayFrom[10][10], int *arrayTo[10][10]);

	int *theBoard[10][10];
	StorageNode *theDatabase[10][10];

	void RestartTurn();

	GameObject* getObject() { return myGameObject; }

	GameObject* myGameObject;
};

