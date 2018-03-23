#include "Pawn.h"


Pawn::Pawn()
{
	myX = 0;
	myY = 0;
	strength = 50;
	dexterity = 50;
	magic = 50;
	mp = 50;
	hp = 75;
	team = 0;
	attacks = 3;
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

	myGameObject->SetTexture("Dead.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->Transform.Position.x, myGameObject->Transform.Position.y, 1, 1, 0.0f);
	myGameObject->GetSphere().setScale(0, 0);
}

void Pawn::RestartTurn()
{
	movementLeft = 6;
	attacks = 2;
}

std::string Pawn::Attack(Pawn &other)
{
	attacks--;

	std::string str = "Empty. If this is displayed, something has gone wrong.";
	float dexValue = dexterity / other.dexterity;

	if(dexValue < 1.0f)
	{
		//std::srand(std::time(0)); //use current time as seed for random generator
		int random_variable = generateRandom(0.0f, 1.0f);
		if (random_variable > dexValue)
		{
			// The attack Misses.
			str = "You missed.";
		}
		else
		{
			float damage = std::floorf(strength + generateRandom( -(strength * 0.3), (strength * 0.3)));
			other.hp -= damage;
			if (other.hp <= 0)
			{
				other.Die();
				str = std::to_string(static_cast<int> (damage)) + " damage. The enemy was killed";
				return str;
			}
			str = "You dealt " + std::to_string(static_cast<int> (damage)) + " points of damage.";
		}
	}
	else
	{
		float damage = std::floorf(strength + generateRandom(-(strength * 0.3), (strength * 0.3)));
		other.hp -= damage;
		if (other.hp <= 0)
		{
			other.Die();
			str = std::to_string(static_cast<int> (damage)) + " damage. The enemy was killed";
			return str;
		}
		str = "You dealt " + std::to_string(static_cast<int> (damage)) + " points of damage.";
	}

	return str;
}

float Pawn::rand_FloatRange(float a, float b)
{
	std::srand(std::time(0));
	return ((b - a)*((float)rand() / RAND_MAX)) + a;
}

float Pawn::generateRandom(float min, float max) 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, std::nextafter(max, DBL_MAX));

	return dis(gen);

	//std::mt19937 eng{ std::chrono::high_resolution_clock::now().time_since_epoch().count() };
	//return std::uniform_real_distribution<>(min, max)(eng);
}

bool Pawn::IsTurnOver()
{
	if (attacks <= 0)
	{
		return true;
	}
	return false;
}

Pawn::vectorBool Pawn::DoUserInput(sf::Event event, int board[10][10], StorageNode database[10][10])
{
	vectorBool vec;
	vec.action = false;
	vec.x = 0;
	vec.y = 0;
	vec.myXPos = myX;
	vec.myYPos = myY;


	if (attacks > 0)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (myX > 0)
			{
				if (board[myX - 1][myY] == 0)
				{
					Move(myX - 1, myY, board);
					return vec;
				}
				else if (database[myX - 1][myY].team != team)
				{
					vec.action = true;
					vec.x = myX - 1;
					vec.y = myY;
					return vec;
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
					return vec;
				}
				else if (database[myX + 1][myY].team != team)
				{
					vec.action = true;
					vec.x = myX + 1;
					vec.y = myY;
					return vec;
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
					return vec;
				}
				else if (database[myX][myY - 1].team != team)
				{
					vec.action = true;
					vec.x = myX;
					vec.y = myY - 1;
					return vec;
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
					return vec;
				}
				else if (database[myX][myY + 1].team != team)
				{
					vec.action = true;
					vec.x = myX;
					vec.y = myY + 1;
					return vec;
				}
			}
		}
	}
	else
	{
		std::cout << "Ending Turn." << std::endl;
		//RestartTurn();
	}

	return vec;
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
