#include "Pawn.h"


Pawn::Pawn()
{
	myX = 0;
	myY = 0;
	strength = 50;
	dexterity = 50;
	magic = 50;
	mp = 50;
	hp = 50;

	myGameObject = new GameObject();
	//myGameObject->InitializeGameObject();
	UpdatePosition();
}


Pawn::~Pawn()
{
}

void Pawn::Attack(Pawn* other)
{

}

void Pawn::Move(int xPos, int yPos) 
{
	myX = xPos;
	myY = yPos;
	UpdatePosition();
}

void Pawn::UpdatePosition() 
{
	myGameObject->SetPosition(100 * myX, 100 * myY);
	std::cout << "My x: " << myX << "My y: " << myY << std::endl ;
}
