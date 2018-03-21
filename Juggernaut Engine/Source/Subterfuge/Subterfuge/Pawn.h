#pragma once

#include "GameObject.h"

class Pawn
{
public:
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
	
	void Attack(Pawn* other);
	void Move(int xPos, int yPos, int board[10][10]);
	void UpdatePosition();
	bool IsTurnOver();
	void DoUserInput(sf::Event event, int board[10][10]);

	void CopyArray(int *arrayFrom[10][10], int *arrayTo[10][10]);

	int *theBoard[10][10];

	void RestartTurn();

	GameObject* getObject() { return myGameObject; }

	GameObject* myGameObject;
};

