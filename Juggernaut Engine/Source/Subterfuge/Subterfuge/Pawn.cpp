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
	attacks = 2;
	movementLeft = 4;
	unitType = 1;
	turnOrderPoints = 100;
	rawMovement = movementLeft;
	rawAttacks = attacks;
	yDir = -1;
	xDir = 0;
	amIMoving = false;
	
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

void Pawn::SetClass(int i)
{
	if (i == 1)
	{
		strength = 55;
		dexterity = 45;
		magic = 0;
		mp = 50;
		hp = 80;
		attacks = 2;
		movementLeft = 4;
		unitType = 1;
		turnOrderPoints = 100;
		rawMovement = movementLeft;
		rawAttacks = attacks;
		myGameObject->SetTexture("Soldier.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition( myGameObject->Transform ).x , myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);;
	}
	else if (i == 2)
	{
		strength = 25;
		dexterity = 53;
		magic = 25;
		mp = 50;
		hp = 45;
		attacks = 3;
		movementLeft = 5;
		unitType = 2;
		turnOrderPoints = 100;
		rawMovement = movementLeft;
		rawAttacks = attacks;
		myGameObject->SetTexture("Rogue.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);;
	}
	else if (i == 3)
	{
		strength = 10;
		dexterity = 43;
		magic = 100;
		mp = 100;
		hp = 30;
		attacks = 2;
		movementLeft = 3;
		unitType = 3;
		turnOrderPoints = 100;
		rawMovement = movementLeft;
		rawAttacks = attacks;
		myGameObject->SetTexture("Mage.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);;
	}
}

void Pawn::ShedTime()
{
	turnOrderPoints -= (dexterity * 0.3);
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
	std::cout << "This shouldn't be triggering constantly..." << std::endl;
	turnOrderPoints = 100;
	movementLeft = rawMovement;
	attacks = rawAttacks;
}

Pawn::stringBool Pawn::UseMagic(std::string spellName, sf::Event event, sf::RenderWindow& win)
{
	stringBool strb;
	strb.exiting = false;
	strb.attacking = false;

	if (attacks <= 0)
	{
		strb.exiting = true;
		spellPosX = 0;
		spellPosY = 0;
		RestartTurn();
		return strb;
	}
	else if (unitType != 3 && unitType != 4)
	{
		strb.exiting = true;
		spellPosX = 0;
		spellPosY = 0;
		strb.myStr = "Can't cast magic...";
		return strb;
	}

	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setScale(1, 1);
	circ.setRadius(50.0f);

	if (spellName == "Fire")
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			spellPosX--;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		{
			spellPosX++;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
		{
			spellPosY++;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
		{
			spellPosY--;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			strb.exiting = true;
			spellPosX = 0;
			spellPosY = 0;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
		{
			attacks--;
			strb.attacking = true;
			strb.vect = { myX, myY };
			strb.targetVect = { myX + spellPosX, myY + spellPosY };
			spellPosX = 0;
			spellPosY = 0;
			return strb;
		}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		//{
		//	spellPosX = 0;
		//	spellPosY = 0;
		//}

		//getObject()->circleShape.setPosition(100 * (myX + spellPosX), 100 * (myY + spellPosY));
		circ.setPosition(100 * (myX + spellPosX), 100 * (myY + spellPosY));
		
		strb.circi = circ;

		strb.vect = {myX, myY};
		strb.targetVect = {myX + spellPosX, myY + spellPosY};
	}

	strb.myStr = "Casting Spell... \n(escape to quit, return to cast)";
	return strb;
}

std::string Pawn::Attack(Pawn &other)
{
	attacks--;

	std::string str = "Empty. If this is displayed, something has gone wrong.";
	float dexValue = (dexterity * 0.7) / (other.dexterity);

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
			float damage = std::floorf(strength + generateRandom( -(strength * 0.4), (strength * 0.4)));

			if (other.xDir == 1)
			{
				if (xDir == 1)
				{
					damage = damage * 2.5;
				}
				else if (xDir == 0)
				{
					damage = damage * 1.5;
				}
			}
			else if (other.xDir == -1)
			{
				if (xDir == -1)
				{
					damage = damage * 2.5;
				}
				else if (xDir == 0)
				{
					damage = damage * 1.5;
				}
			}
			else if (other.yDir == 1)
			{
				if (yDir == 1)
				{
					damage = damage * 2.5;
				}
				else if (yDir == 0)
				{
					damage = damage * 1.5;
				}
			}
			else if (other.yDir == -1)
			{
				if (yDir == -1)
				{
					damage = damage * 2.5;
				}
				else if (yDir == 0)
				{
					damage = damage * 1.5;
				}
			}

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
		float damage = std::floorf(strength + generateRandom(-(strength * 0.4), (strength * 0.4)));

		if (other.xDir == 1)
		{
			if (xDir == 1)
			{
				damage = damage * 2.5;
			}
			else if (xDir == 0)
			{
				damage = damage * 1.5;
			}
		}
		else if (other.xDir == -1)
		{
			if (xDir == -1)
			{
				damage = damage * 2.5;
			}
			else if (xDir == 0)
			{
				damage = damage * 1.5;
			}
		}
		else if (other.yDir == 1)
		{
			if (yDir == 1)
			{
				damage = damage * 2.5;
			}
			else if (yDir == 0)
			{
				damage = damage * 1.5;
			}
		}
		else if (other.yDir == -1)
		{
			if (yDir == -1)
			{
				damage = damage * 2.5;
			}
			else if (yDir == 0)
			{
				damage = damage * 1.5;
			}
		}

		other.hp -= damage;
		if (other.hp <= 0)
		{
			other.Die();
			str = std::to_string(static_cast<int> (damage)) + " damage. \nThe enemy was killed";
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
	vec.str = "Moves Left: " + std::to_string(movementLeft) + " Actions: " + std::to_string(attacks);
	vec.turnOver = false;


	if (attacks > 0)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		{
			if (myX > 0)
			{
				if (board[myX - 1][myY] == 0)
				{
					yDir = 0;
					xDir = -1;
					Move(myX - 1, myY, board);
					amIMoving = true;
					return vec;
				}
				else if (database[myX - 1][myY].team != team)
				{
					yDir = 0;
					xDir = -1;
					vec.action = true;
					vec.x = myX - 1;
					vec.y = myY;
					UpdatePosition();
					amIMoving = false;
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
					yDir = 0;
					xDir = 1;
					Move(myX + 1, myY, board);
					amIMoving = true;
					return vec;
				}
				else if (database[myX + 1][myY].team != team)
				{
					yDir = 0;
					xDir = 1;
					vec.action = true;
					vec.x = myX + 1;
					vec.y = myY;
					UpdatePosition();
					amIMoving = false;
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
					yDir = 1;
					xDir = 0;
					Move(myX, myY - 1, board);
					amIMoving = true;
					return vec;
				}
				else if (database[myX][myY - 1].team != team)
				{
					yDir = 1;
					xDir = 0;
					vec.action = true;
					vec.x = myX;
					vec.y = myY - 1;
					UpdatePosition();
					amIMoving = false;
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
					yDir = -1;
					xDir = 0;
					Move(myX, myY + 1, board);
					amIMoving = true;
					return vec;
				}
				else if (database[myX][myY + 1].team != team)
				{
					yDir = -1;
					xDir = 0;
					vec.action = true;
					vec.x = myX;
					vec.y = myY + 1;
					UpdatePosition();
					amIMoving = false;
					return vec;
				}
			}
		}
	}
	else
	{
		RestartTurn();
		vec.turnOver = true;
		std::cout << "Ending Turn." << std::endl;
		//RestartTurn();
	}

	vec.moving = amIMoving;

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
		movementLeft = rawMovement;
	}
}

void Pawn::UpdatePosition() 
{
	myGameObject->SetPosition(100 * myX, 100 * myY);

	if (xDir == 1)
	{
		if (unitType == 1)
		{
			myGameObject->SetTexture("SoldierR.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 2)
		{
			myGameObject->SetTexture("RogueR.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 3)
		{
			myGameObject->SetTexture("MageR.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
	}
	else if (xDir == -1)
	{
		if (unitType == 1)
		{
			myGameObject->SetTexture("SoldierL.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 2)
		{
			myGameObject->SetTexture("RogueL.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 3)
		{
			myGameObject->SetTexture("MageL.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
	}
	else if (yDir == 1)
	{
		if (unitType == 1)
		{
			myGameObject->SetTexture("SoldierU.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 2)
		{
			myGameObject->SetTexture("RogueU.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 3)
		{
			myGameObject->SetTexture("MageU.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
	}
	else if (yDir == -1)
	{
		if (unitType == 1)
		{
			myGameObject->SetTexture("Soldier.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 2)
		{
			myGameObject->SetTexture("Rogue.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
		else if (unitType == 3)
		{
			myGameObject->SetTexture("Mage.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
	}

	//if (xDir = 1)
	//{
	//	myGameObject->SetPosition(100 * myX, 100 * myY );
	//}

	std::cout << "My x: " << myX << "My y: " << myY << std::endl ;
	std::cout << "Moves Left: " << attacks << "Raw Moves: " << rawAttacks << " Steps Left:" << movementLeft << " Raw:" << rawMovement << std::endl;
}
