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
		std::string str;
		bool moving;
		bool attacking;
	};

	struct stringBool
	{
		std::string myStr;
		bool exiting;
		sf::Vector2i vect;
		sf::Vector2i targetVect;
		sf::CircleShape circi;
		bool attacking;
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
	int xDir;
	int yDir;
	int spellPosX;
	int spellPosY;
	bool amIMoving;

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
	stringBool UseMagic(std::string spellName, sf::Event event, sf::RenderWindow& win);
	vectorBool AutomateMovement(int board[10][10], StorageNode database[10][10]);
	stringBool Pawn::AutomateMagic(std::string spellname, int board[10][10], StorageNode database[10][10]);

	//void CopyArray(int *arrayFrom[10][10], int *arrayTo[10][10]);

	int *theBoard[10][10];
	StorageNode *theDatabase[10][10];

	void RestartTurn();

	GameObject* getObject() { return myGameObject; }

	GameObject* myGameObject;
};

