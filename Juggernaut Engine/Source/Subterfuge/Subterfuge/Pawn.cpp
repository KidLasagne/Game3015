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
	else if (i == 4)
	{
		strength = 10;
		dexterity = 42;
		magic = 100;
		mp = 100;
		hp = 30;
		attacks = 3;
		movementLeft = 3;
		unitType = 4;
		turnOrderPoints = 100;
		rawMovement = movementLeft;
		rawAttacks = attacks;
		myGameObject->SetTexture("Priest2.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);;
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
	myGameObject->GetSphere().setScale(1.0, 1.0);
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

	std::cout << "ATTACKING NOW!!!!" << std::endl;

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

	if (attacks < 1 && team > 2)
	{
		str = "No more attacks";
		RestartTurn();
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

	if (team > 1)
	{
		vec = AutomateMovement(board, database);
		return vec;
	}

	myGameObject->GetSphere().setScale(1.5, 1.5);

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

Pawn::stringBool Pawn::AutomateMagic(std::string spellname, int board[10][10], StorageNode database[10][10])
{
	attacks--;
	stringBool v;
	v.attacking = true;
	v.myStr = "\nEnemy Casting Magic...";
	v.exiting = false;
	v.targetVect = { 0,0 };
	v.vect = {myX, myY};

	if (spellname == "Fire")
	{
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (database[x][y].unitType == 3 || database[x][y].unitType == 4)
				{
					if (database[x][y].team != team && unitType != 4)
					{
						v.myStr += "\nCasting Offensive Magic";
						v.targetVect = { x , y };
						return v;
					}
					else if (database[x][y].team == team && unitType == 4)
					{
						v.myStr += "\nHealing Damage";
						v.targetVect = { x , y };
						return v;
					}
				}
				else if (database[x][y].unitType == 2 && unitType != 4)
				{
					if (database[x][y].team != team)
					{
						v.myStr += "\nCasting Offensive Magic";
						v.targetVect = { x , y };
						return v;
					}
					else if (database[x][y].team == team && unitType == 4)
					{
						v.myStr += "\nHealing Damage";
						v.targetVect = { x , y };
						return v;
					}
				}
				else if (database[x][y].unitType == 1 && unitType != 4)
				{
					if (database[x][y].team != team)
					{
						v.myStr += "\nCasting Offensive Magic";
						v.targetVect = { x , y };
						return v;
					}
					else if (database[x][y].team == team && unitType == 4)
					{
						v.myStr += "\nHealing Damage";
						v.targetVect = { x , y };
						return v;
					}
				}
			}
		}
	}

	v.attacking = false;
	v.exiting = true;
	v.myStr += "\nNo enemies to attack...\nEnding Turn";
	//RestartTurn();
	return v;
}

Pawn::vectorBool Pawn::AutomateMovement(int board[10][10], StorageNode database[10][10])
{
	Pawn::vectorBool v4;
	v4.action = false;
	v4.turnOver = false;
	v4.moving = false;
	v4.myXPos = myX;
	v4.myYPos = myY;
	v4.x = 0;
	v4.y = 0;
	v4.attacking = false;

	bool canIAttack = false;
	
	int enemyX = 0;
	int enemyY = 0;
	int moveX = 0;
	int moveY = 0;

	if (attacks > 0)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (x > 0)
				{
					if (database[myX - 1][myY].unitType != 0 && database[myX - 1][myY].team != team)
					{
						enemyX = myX - 1;
						enemyY = myY;

						v4.action = false;
						v4.myXPos = myX;
						v4.myYPos = myY;
						v4.x = enemyX;
						v4.y = enemyY;
						v4.attacking = true;
						canIAttack = true;
						return v4;
					}
				}
				if (y > 0)
				{
					if (database[myX][myY - 1].unitType != 0 && database[myX][myY - 1].team != team)
					{
						enemyX = myX;
						enemyY = myY - 1;

						v4.action = false;
						v4.myXPos = myX;
						v4.myYPos = myY;
						v4.x = enemyX;
						v4.y = enemyY;
						v4.attacking = true;
						canIAttack = true;
						return v4;
					}
				}
				if (x < 10 - 1)
				{
					if (database[myX + 1][myY].unitType != 0 && database[myX + 1][myY].team != team)
					{
						enemyX = myX + 1;
						enemyY = myY;

						v4.action = false;
						v4.myXPos = myX;
						v4.myYPos = myY;
						v4.x = enemyX;
						v4.y = enemyY;
						v4.attacking = true;
						canIAttack = true;
						return v4;
					}
				}
				if (y < 10 - 1)
				{
					if (database[myX][myY + 1].unitType != 0 && database[myX][myY + 1].team != team)
					{
						enemyX = myX;
						enemyY = myY + 1;

						v4.action = false;
						v4.myXPos = myX;
						v4.myYPos = myY;
						v4.x = enemyX;
						v4.y = enemyY;
						v4.attacking = true;
						canIAttack = true;
						return v4;
					}
				}
			}
		}
		if (canIAttack == true)
		{
			std::cout << "Attacking..." << std::endl;
			v4.str = "Attacking...";
			return v4;
		}
		else
		{
			std::cout << "Moving Around..." << std::endl;
			v4.str = "Moving Around...";

			int Virus[10][10];
			int TempBoard[10][10];
			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 10; x++)
				{
					Virus[x][y] = board[x][y];
					TempBoard[x][y] = board[x][y];
				}
			}
			Virus[myX][myY] = 99;
			for (int i = 0; i < movementLeft; i++)
			{
				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (Virus[x][y] == 99)
						{
							if (x > 0)
							{
								TempBoard[x - 1][y] = 99;
							}
							if (y > 0)
							{
								TempBoard[x][y - 1] = 99;
							}
							if (x < 10 - 1)
							{
								TempBoard[x + 1][y] = 99;
							}
							if (y < 10 - 1)
							{
								TempBoard[x][y + 1] = 99;
							}
						}
					}
				}

				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 10; x++)
					{
						Virus[x][y] = TempBoard[x][y];
					}
				}
			}

			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 10; x++)
				{
					TempBoard[x][y] = 0;
				}
			}

			enemyX = 0;
			enemyY = 0;

			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 10; x++)
				{
					if (Virus[x][y] == 99)
					{
						if (x > 0)
						{
							if (database[x - 1][y].team != team && database[x - 1][y].unitType != 0)
							{
								if (unitType == 3 || unitType == 4)
								{
									enemyX = x - 1;
									enemyY = y;
									TempBoard[x][y] = 3;
								}
								else if (unitType == 2)
								{
									enemyX = x - 1;
									enemyY = y;
									TempBoard[x][y] = 2;
								}
								else if (unitType == 1)
								{
									enemyX = x - 1;
									enemyY = y;
									TempBoard[x][y] = 1;
								}
							}
						}
						if (y > 0)
						{
							if (database[x][y - 1].team != team && database[x][y - 1].unitType != 0)
							{
								if (unitType == 3 || unitType == 4)
								{
									enemyX = x;
									enemyY = y - 1;
									TempBoard[x][y] = 3;
								}
								else if (unitType == 2)
								{
									enemyX = x;
									enemyY = y - 1;
									TempBoard[x][y] = 2;
								}
								else if (unitType == 1)
								{
									enemyX = x;
									enemyY = y - 1;
									TempBoard[x][y] = 1;
								}
							}
						}
						if (x < 10 - 1)
						{
							if (database[x + 1][y].team != team && database[x + 1][y].unitType != 0)
							{
								if (unitType == 3 || unitType == 4)
								{
									enemyX = x + 1;
									enemyY = y;
									TempBoard[x][y] = 3;
								}
								else if (unitType == 2)
								{
									enemyX = x + 1;
									enemyY = y;
									TempBoard[x][y] = 2;
								}
								else if (unitType == 1)
								{
									enemyX = x + 1;
									enemyY = y;
									TempBoard[x][y] = 1;
								}
							}
						}
						if (y < 10 - 1)
						{
							if (database[x][y + 1].team != team && database[x][y + 1].unitType != 0)
							{
								if (unitType == 3 || unitType == 4)
								{
									enemyX = x;
									enemyY = y + 1;
									TempBoard[x][y] = 3;
								}
								else if (unitType == 2)
								{
									enemyX = x;
									enemyY = y + 1;
									TempBoard[x][y] = 2;
								}
								else if (unitType == 1)
								{
									enemyX = x;
									enemyY = y + 1;
									TempBoard[x][y] = 1;
								}
							}
						}
					}
				}
			}

			int highestValue = 0;
			moveX = 8;
			moveY = 8;

			int dx = 0;
			int dy = 0;

			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 10; x++)
				{
					if (TempBoard[x][y] == 3)
					{
						highestValue = 3;
						moveX = x;
						moveY = y;
						dx = x - myX;
						dy = y - myY;
					}
					else if (TempBoard[x][y] == 2 && highestValue < TempBoard[x][y])
					{
						highestValue = 2;
						moveX = x;
						moveY = y;
						dx = x - myX;
						dy = y - myY;
					}
					else if (TempBoard[x][y] == 1 && highestValue < TempBoard[x][y])
					{
						highestValue = 1;
						moveX = x;
						moveY = y;
						dx = x - myX;
						dy = y - myY;
					}
				}
			}

			dx = std::abs(dx);
			dy = std::abs(dy);

			if (highestValue > 0)
			{
				myX = moveX;
				myY = moveY;
				UpdatePosition();
				movementLeft -= dx + dy;

				if (movementLeft <= 0)
				{
					attacks--;
					movementLeft = rawMovement;

					if (attacks <= 0)
					{
						RestartTurn();
						v4.turnOver = true;
						std::cout << "Ending Turn." << std::endl;
					}
					else
					{
						v4.action = true;
						v4.myXPos = moveX;
						v4.myYPos = moveY;
						v4.x = enemyX;
						v4.y = enemyY;

						std::cout << "Restarting Because I can Still Move...." << std::endl;
						v4.str = "Restarting Because I can Still Move....";

						//AutomateMovement(board, database);
					}
				}
			}
			else // if Highest Value <= 0
			{
				int markX = 0;
				int markY = 0;
				
				bool didIFindSomething = false;
					
				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 10; x++)
					{
						if (database[x][y].team != team && database[x][y].unitType != 0)
						{
							if (unitType == 3 || unitType == 4)
							{
								highestValue = 3;
								markX = x;
								markY = y;
								didIFindSomething = true;
							}
							else if (unitType == 2)
							{
								highestValue = 2;
								markX = x;
								markY = y;
								didIFindSomething = true;
							}
							else if (unitType == 1)
							{
								highestValue = 1;
								markX = x;
								markY = y;
								didIFindSomething = true;
							}
						}
					}
				}

				int highestX = 10;
				int highestY = 10;

				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 10; x++)
					{
						dx = x - myX;
						dy = y - myY;
						dx = std::abs(dx);
						dy = std::abs(dy);
						if (markX - x < highestX && markX != x && dx + dy <= movementLeft)
						{
							highestX = x;
							highestY = y;
						}
					}
				}

				bool itWorked = false;

				if (didIFindSomething == false)
				{
					int randy = generateRandom(0,2);
					
					if (randy >= 1)
					{
						if (myY + movementLeft < 10)
						{
							if (database[myX][myY + movementLeft].unitType == 0)
							{
								moveY = myY + movementLeft;
								moveX = myX;
								itWorked = true;
							}
						}
						else if (myX + movementLeft < 10)
						{
							 if (database[myX + movementLeft][myY].unitType == 0)
							{
								moveY = myY;
								moveX = myX + movementLeft;
								itWorked = true;
							}
						}
						if(itWorked == false)
						{
							movementLeft--;
							if (myX < 9 && myY < 9)
							{
								if (database[myX + 1][myY + 1].unitType == 0)
								{
									moveX = myX + 1;
									moveY = myY + 1;
								}
							}
							if (myX < 9 && myY > 0)
							{
								if (database[myX + 1][myY - 1].unitType == 0)
								{
									moveX = myX + 1;
									moveY = myY - 1;
								}
							}
							if (myX > 0 && myY > 0)
							{
								if (database[myX - 1][myY - 1].unitType == 0)
								{
									moveX = myX - 1;
									moveY = myY - 1;
								}
							}
							if (myX > 0 && myY < 9)
							{
								if (database[myX - 1][myY + 1].unitType == 0)
								{
									moveX = myX - 1;
									moveY = myY + 1;
								}
							}
							if (myY > 0)
							{
								if (database[myX][myY - 1].unitType == 0)
								{
									moveX = myX;
									moveY = myY - 1;
								}
							}
							if (myX < 9)
							{
								if (database[myX + 1][myY].unitType == 0)
								{
									moveX = myX + 1;
									moveY = myY;
								}
							}
							if (myX > 0)
							{
								if (database[myX - 1][myY].unitType == 0)
								{
									moveX = myX - 1;
									moveY = myY;
								}
							}
							if (myY < 9)
							{
								if (database[myX][myY + 1].unitType == 0)
								{
									moveX = myX;
									moveY = myY + 1;
								}
							}
						}
					}
				}
				else
				{
					myX = moveX;
					myY = moveY;
				}
				UpdatePosition();

				if (highestX == 10 && highestY == 10)
				{
					if (itWorked == true)
					{
						movementLeft = 0;
					}
					else
					{
						movementLeft--;
					}
				}
				else
				{
					movementLeft -= dx + dy;
				}

				if (movementLeft <= 0)
				{
					attacks--;
					movementLeft = rawMovement;

					if (attacks <= 0)
					{
						RestartTurn();
						v4.turnOver = true;
						std::cout << "Ending Turn." << std::endl;
					}
					else
					{
						v4.action = true;
						v4.myXPos = moveX;
						v4.myYPos = moveY;
						v4.x = enemyX;
						v4.y = enemyY;

						std::cout << "Restarting Because I can Still Move...." << std::endl;
						v4.str = "Restarting Because I can Still Move....";

						//AutomateMovement(board, database);
					}
				}
			}
		}
	}
	else if (attacks <= 0)
	{
		RestartTurn();
		v4.turnOver = true;
		v4.str = "No attacks left, ending turn.";
		std::cout << "NO ATTACKS LEFT!!!" << std::endl;
		v4.myXPos = myX;
		v4.myYPos = myY;
		v4.attacking = false;
		v4.action = false;
		v4.moving = false;
	}

	return v4;
}

void Pawn::Move(int xPos, int yPos, int board[10][10]) 
{
	myX = xPos;
	myY = yPos;
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
		else if (unitType == 4)
		{
			myGameObject->SetTexture("Priest2R.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
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
		else if (unitType == 4)
		{
			myGameObject->SetTexture("Priest2L.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
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
		else if (unitType == 4)
		{
			myGameObject->SetTexture("Priest2U.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
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
		else if (unitType == 4)
		{
			myGameObject->SetTexture("Priest2.png", myGameObject->sprite, 100, 100, 0, 0, myGameObject->GetPosition(myGameObject->Transform).x, myGameObject->GetPosition(myGameObject->Transform).y, 1, 1, 0.0f);
		}
	}

	//if (xDir = 1)
	//{
	//	myGameObject->SetPosition(100 * myX, 100 * myY );
	//}

	std::cout << "My x: " << myX << "My y: " << myY << std::endl ;
	std::cout << "Moves Left: " << attacks << "Raw Moves: " << rawAttacks << " Steps Left:" << movementLeft << " Raw:" << rawMovement << std::endl;
}
