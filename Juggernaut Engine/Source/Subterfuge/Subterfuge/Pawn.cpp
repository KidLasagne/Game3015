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
	team = 0;
	attacks = 2;
	movementLeft = 6;
	unitType = 1;
	
	for(int x = 0; x < 10; x++)
	{
		for(int y = 0; y < 10; y++)
		{
			theDatabase[x][y] = new StorageNode();
			theDatabase[x][y]->InitAllValues();
		}
	}

	myGameObject = new GameObject();
	//myGameObject->InitializeGameObject();
	UpdatePosition();
}

Pawn::~Pawn()
{

}

void Pawn::Die()
{
	strength = 0;
	dexterity = 0;
	magic = 0;
	mp = 0;
	hp = 0;
	team = 0;
	attacks = 0;
	movementLeft = 0;
	unitType = 0;

	myGameObject->SetTexture("Mage.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->Transform.Position.x, myGameObject->Transform.Position.y, 1, 1, 0.0f);
}

void Pawn::RestartTurn()
{
	movementLeft = 6;
	attacks = 2;
}

void Pawn::Attack(Pawn* other)
{
	attacks--;
}

bool Pawn::IsTurnOver()
{
	if (attacks <= 0)
	{
		return true;
	}
	return false;
}

void Pawn::DoUserInput(sf::Event event, int board[10][10], StorageNode database[10][10])
{
	if (attacks > 0)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (myX > 0)
			{
				if (board[myX - 1][myY] == 0)
				{
					Move(myX - 1, myY, board);
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			if (myX < 10 - 1)
			{
				if (board[myX + 1][myY] == 0)
				{
					Move(myX + 1, myY, board);
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			if (myY > 0)
			{
				if (board[myX][myY - 1] == 0)
				{
					Move(myX, myY - 1, board);
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			if (myY < 10 - 1)
			{
				if (board[myX][myY + 1] == 0)
				{
					Move(myX, myY + 1, board);
				}
			}
		}
	}
	else
	{
		std::cout << "Ending Turn." << std::endl;
		//RestartTurn();
	}
}

void Pawn::Move(int xPos, int yPos, int board[10][10]) 
{
	//*board[myX][myY] = 0;
	myX = xPos;
	myY = yPos;
	//*board[myX][myY] = unitType;
	UpdatePosition();
	movementLeft--;
	if (movementLeft <= 0)
	{
		attacks--;
		movementLeft = 6;
	}
}

void Pawn::UpdatePosition() 
{
	myGameObject->SetPosition(100 * myX, 100 * myY);
	std::cout << "My x: " << myX << "My y: " << myY << std::endl ;
	std::cout << "Moves Left: " << attacks << " , Steps Left: " << movementLeft << std::endl;
}
