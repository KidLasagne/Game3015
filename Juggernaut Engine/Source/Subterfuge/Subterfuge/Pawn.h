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
	
	void Attack(Pawn* other);
	void Move(int xPos, int yPos);
	void UpdatePosition();

	GameObject* getObject() { return myGameObject; }

	GameObject* myGameObject;
};

