#pragma once

#include <iostream>
class StorageNode
{
public:
	StorageNode();
	~StorageNode();

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

	void CopyOverAllValues(int x, int y, float str, float dex, float mag, int magicPoints, int hitPoints, int tm, int attks, int movleft, int uType);
	void InitAllValues();
};

