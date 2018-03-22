#include "StorageNode.h"


StorageNode::StorageNode()
{
}


StorageNode::~StorageNode()
{
}

void StorageNode::CopyOverAllValues(int x, int y, float str, float dex, float mag, int magicPoints, int hitPoints, int tm, int attks, int movleft, int uType)
{
	myX = x;
	myY = y;
	strength = str;
	dexterity = dex;
	magic = mag;
	mp = magicPoints;
	hp = hitPoints;
	team = tm;
	attacks = attks;
	movementLeft = movleft;
	unitType = uType;
}

void StorageNode::InitAllValues()
{
	myX = 0;
	myY = 0;
	strength = 0;
	dexterity = 0;
	magic = 0;
	mp = 0;
	hp = 0;
	team = 0;
	attacks = 0;
	movementLeft = 0;
	unitType = 0;
}