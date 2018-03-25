#include "Juggernaut.h"

Juggernaut::Juggernaut()
{
}


Juggernaut::~Juggernaut()
{
}

void Juggernaut::Initialize() 
{
	ExceedsRequirements = true;

	HANDLE mutex = CreateMutex(NULL, TRUE, L"Juggernaut");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		std::cout << "Another App Instance Running, Shutting Down..." << std::endl;
		ExceedsRequirements = false;
		// There's another instance running.  What do you do?
	}
	else
	{
		std::cout << "No Other App Instances Found, Running Program..." << std::endl;
	}

	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	std::cout << "RAM Available: " << status.ullTotalPhys << std::endl;

	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo);

	// Display the contents of the SYSTEM_INFO structure. 

	printf("Hardware information: \n");
	printf("  OEM ID: %u\n", siSysInfo.dwOemId);
	printf("  Number of processors: %u\n",
		siSysInfo.dwNumberOfProcessors);
	printf("  Page size: %u\n", siSysInfo.dwPageSize);
	printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
	printf("  Minimum application address: %lx\n",
		siSysInfo.lpMinimumApplicationAddress);
	printf("  Maximum application address: %lx\n",
		siSysInfo.lpMaximumApplicationAddress);
	printf("  Active processor mask: %u\n",
		siSysInfo.dwActiveProcessorMask);

	std::cout << "Free Disc Space: " << GetFreeSpace() << std::endl;

	if (GetFreeSpace() > 52428)
	{
		std::cout << "You have enough free space." << std::endl;
	}
	else
	{
		std::cout << "You do not have enough free space. Exiting Program." << std::endl;
		ExceedsRequirements = false;
	}

	if (status.ullTotalPhys > 4276000000)
	{
		std::cout << "You have enough RAM." << std::endl;
	}
	else
	{
		std::cout << "You do not have enough RAM. Exiting Program." << std::endl;
		ExceedsRequirements = false;
	}

	if (siSysInfo.dwProcessorType > 386)
	{
		std::cout << "Your processor exceeds the requirements." << std::endl;
	}
	else
	{
		std::cout << "Your processor does not meet the requirements. Exiting Program." << std::endl;
		ExceedsRequirements = false;
	}

	// Initialize Game Here.
	myX = 0;
	myY = 0;
	SetBoardSize(10);

	//board = new int[10][10];

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			// Ah I see, I don't need to initialize it because it isn't a pointer.
			//Database[x][y] = new StorageNode();
		}
	}
	//*board[0][0] = 1;
}

void Juggernaut::PrintBoard()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			std::cout << board[x][y];
			if (x == 9)
			{
				std::cout << std::endl;
			}
		}
	}
}

void Juggernaut::Beginning() 
{
	//Initialize();
	GetGameObjectManager().Awake();
	GetGameObjectManager().Start();
}

void Juggernaut::MainLoop() 
{
	GetGameObjectManager().Update();
	GetGameObjectManager().LateUpdate();
}

void Juggernaut::ShowText(std::string str, sf::RenderWindow& win)
{
	sf::Font font;
	if (!font.loadFromFile("AnotherDayInParadise.ttf"))
	{
		std::cout << "Failed to load font..." << std::endl;
		// error...
		return;
	}

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

						// set the string to display
	text.setString(str);

	// set the character size
	text.setCharacterSize(75); // in pixels, not points!

							   // set the color
	//text.setColor(sf::Color::Red);
	text.setFillColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold);

	text.setPosition(1100, 100);

	// inside the main loop, between window.clear() and window.display()
	win.draw(text);
}

Pawn* RetrieveLowestTurnOrder(GameObjectManager Manager)
{
	float currentLowest = 101;
	Pawn* pwned = new Pawn();
	for (auto& pawn : Manager.GetPawnLibrary())
	{
		if (pawn->turnOrderPoints < currentLowest)
		{
			pwned = pawn;
			currentLowest = pawn->turnOrderPoints;
		}
	}
	return pwned;
}

Pawn::vectorBool Juggernaut::SearchForConflicts(sf::Vector2i vectorDrawer[10], int &randyStoreX, int &randyStoreY)
{
	Pawn::vectorBool pawny;
	pawny.action = true;
	pawny.myXPos = randyStoreX;
	pawny.myYPos = randyStoreY;

	for (int i = 0; i < 10; i++)
	{
		if (vectorDrawer[i] == sf::Vector2i{ randyStoreX, randyStoreY })
		{
			randyStoreX = std::floor(generateRandom(0, 9));
			randyStoreY = std::floor(generateRandom(0, 9));
			
			Pawn::vectorBool v2 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);

			if (v2.action == true)
			{
				pawny.myXPos = randyStoreX;
				pawny.myYPos = randyStoreY;
				pawny.action = true;
				return pawny;
			}
			else
			{
				randyStoreX = std::floor(generateRandom(0, 9));
				randyStoreY = std::floor(generateRandom(0, 9));

				Pawn::vectorBool v2 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
			}
		}
	}
	return pawny;
}

float Juggernaut::generateRandom(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, std::nextafter(max, DBL_MAX));

	return dis(gen);

	//std::mt19937 eng{ std::chrono::high_resolution_clock::now().time_since_epoch().count() };
	//return std::uniform_real_distribution<>(min, max)(eng);
}

void Juggernaut::Subterfuge()
{
	sf::RenderWindow window({ 1920,1080 }, "SUBTERFUGE");
	window.setFramerateLimit(30);

	sf::Texture tex;

	if (!tex.loadFromFile("TheCommissionersMagnificence.png"))
	{
		std::cout << "The Image Was Not Found..." << std::endl;
	}

	sf::Sprite sprite; // (tex);
	sprite.setTexture(tex);
	window.draw(sprite);
	window.display();

	Initialize();

	bool tempBool = false;
	while (tempBool == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				tempBool = true;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				tempBool = true;
			}
		}
	}

	if (ExceedsRequirements == false)
	{
		return;
	}

	//TransmuteBoard(boardSize);

	Pawn *First = new Pawn();
	Pawn *Second = new Pawn();
	Pawn *Third = new Pawn();
	Pawn *Fourth = new Pawn();
	Pawn *Fifth = new Pawn();
	Pawn *Sixth = new Pawn();
	Pawn *Seventh = new Pawn();
	Pawn *Eighth = new Pawn();

	sf::Vector2i vectorDrawer[10];

	for (int i = 0; i < 10; i++)
	{
		vectorDrawer[i] = { 0, 0 };
	}

	int randX = std::floor(First->generateRandom(0, 9));
	int randY = std::floor(First->generateRandom(0, 9));

	First->Move(randX, randY, board);
	First->team = 1;
	First->getObject()->SetSphereColor(sf::Color::Red);
	First->SetClass(1);

	vectorDrawer[0] = { randX, randY };

	int randyStoreX = std::floor(First->generateRandom(0, 9));
	int randyStoreY = std::floor(First->generateRandom(0, 9));

	Pawn::vectorBool v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[1] = sf::Vector2i{v3.myXPos, v3.myYPos};

	Second->Move(randyStoreX, randyStoreY, board);
	Second->team = 2;
	Second->getObject()->SetSphereColor(sf::Color::Blue);
	Second->SetClass(1);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[2] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	Third->Move(randyStoreX, randyStoreY, board);
	Third->team = 1;
	Third->getObject()->SetSphereColor(sf::Color::Red);
	Third->SetClass(2);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[3] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	Fourth->Move(randyStoreX, randyStoreY, board);
	Fourth->team = 2;
	Fourth->getObject()->SetSphereColor(sf::Color::Blue);
	Fourth->SetClass(2);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[4] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	Fifth->Move(randyStoreX, randyStoreY, board);
	Fifth->team = 1;
	Fifth->getObject()->SetSphereColor(sf::Color::Red);
	Fifth->SetClass(3);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[5] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	Sixth->Move(randyStoreX, randyStoreY, board);
	Sixth->team = 2;
	Sixth->getObject()->SetSphereColor(sf::Color::Blue);
	Sixth->SetClass(3);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[6] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	Seventh->Move(randyStoreX, randyStoreY, board);
	Seventh->team = 1;
	Seventh->getObject()->SetSphereColor(sf::Color::Red);
	Seventh->SetClass(4);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[7] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	Eighth->Move(randyStoreX, randyStoreY, board);
	Eighth->team = 2;
	Eighth->getObject()->SetSphereColor(sf::Color::Blue);
	Eighth->SetClass(4);

	randyStoreX = std::floor(First->generateRandom(0, 9));
	randyStoreY = std::floor(First->generateRandom(0, 9));
	v3 = SearchForConflicts(vectorDrawer, randyStoreX, randyStoreY);
	vectorDrawer[8] = sf::Vector2i{ v3.myXPos, v3.myYPos };
	randyStoreX = v3.myXPos;
	randyStoreY = v3.myYPos;

	//Manager.PushGameObject(First->getObject());
	Manager.PushPawn(First);
	Manager.PushPawn(Second);
	Manager.PushPawn(Third);
	Manager.PushPawn(Fourth);
	Manager.PushPawn(Fifth);
	Manager.PushPawn(Sixth);
	Manager.PushPawn(Seventh);
	Manager.PushPawn(Eighth);

	sf::Clock clock; // starts the clock
	sf::Clock clock2;

	DisplayString = "Starting Game...";
	std::string DisplayString2 = "No String Used Here...";

	sf::CircleShape ciri;
	sf::CircleShape circi;

	bool casting = false;

	for (auto& pawn : Manager.GetPawnLibrary())
	{
		clock.restart();
		clock2.restart();
		pawn->ShedTime();
	}

	while (window.isOpen())
	{
		window.clear();

		sf::Time elapsed = clock.getElapsedTime();
		sf::Time elapsed2 = clock2.getElapsedTime();

		//std::cout << elapsed1.asSeconds() << std::endl;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				casting = true;
			}
			Pawn* sp = RetrieveLowestTurnOrder(Manager);
			if(sp->unitType == 3 || sp->unitType == 4)
			{
				if (sp->team > 1)
				{
					casting = true;
				}
			}

			if (casting == false)
			{
				Pawn::vectorBool vec;

				//vec = First->DoUserInput(event, board, Database);
				Pawn* storagePawn = RetrieveLowestTurnOrder(Manager);
				if (storagePawn->team == 1)
				{
					vec = storagePawn->DoUserInput(event, board, Database);
				}
				else if(storagePawn->team >= 2)
				{
					vec = storagePawn->AutomateMovement(board, Database);
				}


				circi.setFillColor(sf::Color::White);
				circi.setScale(1, 1);
				circi.setRadius(75.0f);
				if (storagePawn != NULL)
				{
					circi.setPosition(storagePawn->getObject()->Transform.Position.x - 25.0f, storagePawn->getObject()->Transform.Position.y - 25.0f);
				}

				//MoveXtoLastPosition(storagePawn, window,circi);

				if (vec.moving == true)
				{
					DisplayString = vec.str;
				}
				clock.restart();

				if (vec.attacking == true)
				{
					//std::cout << "ATTACKING!!!!" << std::endl;
					DisplayString2 = "Attacking Enemy.... \n(automated)";
					clock2.restart();

					for (auto& pawn : Manager.GetPawnLibrary())
					{
						if (pawn->myX == vec.myXPos && pawn->myY == vec.myYPos)
						{
							DisplayString2 = "Found the First...";

							for (auto& pawn2 : Manager.GetPawnLibrary())
							{
								if (pawn2->myX == vec.x && pawn2->myY == vec.y)
								{
									DisplayString2 = "It's in the loop...";
									clock.restart();
									DisplayString2 = pawn->Attack(*pawn2);
									//pawn->attacks--;

									while (pawn->attacks > 0 && pawn2->unitType != 0)
									{
										DisplayString2 = pawn->Attack(*pawn2);
										//pawn->attacks--;
									}
									//pawn->RestartTurn();
									vec.turnOver = true;
									pawn->UpdatePosition();
									pawn2->UpdatePosition();
								}
							}
						}
					}
				}

				if (vec.turnOver == true)
				{
					clock.restart();
					DisplayString += "\n End of Turn...";

					for (auto& pawn : Manager.GetPawnLibrary())
					{
						pawn->ShedTime();
					}

					Pawn* p = RetrieveLowestTurnOrder(Manager);
					circi.setPosition(p->getObject()->Transform.Position.x - 25.0f, p->getObject()->Transform.Position.y - 25.0f);
				}

				if (vec.action == true)
				{
					std::cout << "Go to sleep... target X = " << vec.x << " target Y = " << vec.y << std::endl;
					for (auto& pawn : Manager.GetPawnLibrary())
					{
						if (pawn->myX == vec.x && pawn->myY == vec.y)
						{
							for (auto& pawn2 : Manager.GetPawnLibrary())
							{
								if (pawn2->myX == vec.myXPos && pawn2->myY == vec.myYPos)
								{
									clock.restart();
									DisplayString = pawn2->Attack(*pawn);
								}
							}
						}
					}
				}
			}
			else if (casting == true)
			{
				Pawn::stringBool strb;
				Pawn* storagePawn = RetrieveLowestTurnOrder(Manager);
				if (storagePawn->team > 1)
				{
					strb = storagePawn->AutomateMagic("Fire", board, Database);
					DisplayString = strb.myStr;
				}
				else
				{
					strb = storagePawn->UseMagic("Fire", event, window);
					DisplayString = strb.myStr;
				}

				if (strb.exiting == true)
				{
					casting = false;
				}
				if (strb.attacking == true)
				{
					for (auto& pawn : Manager.GetPawnLibrary())
					{
						if (pawn->myX == strb.vect.x && pawn->myY == strb.vect.y)
						{
							for (auto& pawn2 : Manager.GetPawnLibrary())
							{
								if (pawn2->myX == strb.targetVect.x && pawn2->myY == strb.targetVect.y)
								{
									if (pawn2->unitType == 0)
									{
										DisplayString2 = "Can't attack nothing...";
										clock2.restart();
									}
									else
									{
										if (pawn->mp >= 10)
										{
											int hip = (pawn->generateRandom((pawn->magic / 2), pawn->magic));
											if (pawn->unitType == 4)
											{
												pawn2->hp += hip;
												DisplayString2 = "You Healed " + std::to_string(hip) + " points of damage...";
												clock2.restart();
											}
											else
											{
												pawn2->hp -= hip;
												DisplayString2 = "You dealt " + std::to_string(hip) + " points of damage...";
												clock2.restart();
											}
											pawn->mp -= 10;
											if (pawn2->hp <= 0)
											{
												pawn2->Die();
											}
											clock.restart();
										}
										else
										{
											DisplayString2 = "No MP...";
											clock.restart();
											clock2.restart();
										}
									}
								}
							}
						}
					}
					casting = false;

					if (storagePawn->team > 1 && storagePawn->attacks <= 0)
					{
						for (auto& pawn : Manager.GetPawnLibrary())
						{
							pawn->ShedTime();
						}
						storagePawn->RestartTurn();
						casting = false;
					}
				}

				ciri = strb.circi;
					
				//RetrieveLowestTurnOrder(Manager)->UseMagic("Fire", event);
				clock.restart();
			}
			//PrintBoard();
			std::cout << std::endl;
			//DoUserInput(event);

			TransmuteBoard(10.0f);
		}


		for (auto& game_object : Manager.GetPawnLibrary())
		{
			if (game_object->getObject()->parent != NULL)
			{
				//game_object->Rotate(game_object->parent->GetWorldTransform(), 1.0f + elapsed2.asSeconds);
			}
			else
			{
				//game_object->Rotate(elapsed2.asSeconds() * 10.0f);
			}
		}

		MainLoop();

		clock.restart();

		if (elapsed2.asSeconds() < 4.0f)
		{
			std::string stringy = DisplayString + "\n" + DisplayString2;
			ShowText(stringy, window);
		}
		else
		{
			ShowText(DisplayString, window);
		}

		if (casting == true)
		{
			window.draw(ciri);
		}

		window.draw(circi);

		for (auto& pawn : Manager.GetPawnLibrary())
		{
			if (pawn->hp <= 0)
			{
				// Do Absolutely Nothing...
			}
			else
			{
				window.draw(pawn->getObject()->circleShape);
			}
			window.draw(pawn->getObject()->GetSprite());
		}
		ShowBoard(window);
		window.display();
	}
}

void Juggernaut::TransmuteBoard(int bSize)
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			board[x][y] = 0;
			Database[x][y].InitAllValues();
		}
	}
	for (auto& pawn : Manager.GetPawnLibrary())
	{
		board[pawn->myX][pawn->myY] = pawn->unitType ;
		Database[pawn->myX][pawn->myY].CopyOverAllValues(pawn->myX, pawn->myY, pawn->strength, pawn->dexterity, pawn->magic, pawn->mp, pawn->hp, pawn->team, pawn->attacks, pawn->movementLeft, pawn->unitType);
	}
}

void Juggernaut::ShowBoard(sf::RenderWindow& win)
{
	for (int y = 0; y <= boardSize; y++)
	{
		for (int x = 0; x <= boardSize; x++)
		{	
			if (y == 0)
			{
				sf::RectangleShape rectangle;
				rectangle.setSize(sf::Vector2f(3, (100 * (arraySize) )));
				rectangle.setOutlineColor(sf::Color::White);
				rectangle.setOutlineThickness(2);
				rectangle.setPosition(100 * x, 0);

				win.draw(rectangle);
			}
			if (x == 0)
			{
				sf::RectangleShape rectangle;
				rectangle.setSize(sf::Vector2f(100 * (arraySize), 3));
				rectangle.setOutlineColor(sf::Color::White);
				rectangle.setOutlineThickness(2);
				rectangle.setPosition(0,100 * y);

				win.draw(rectangle);
			}
		}
	}
}

void Juggernaut::MoveXtoLastPosition(Pawn* pwn, sf::RenderWindow& win, sf::CircleShape circ)
{
	//circ.setPosition(pwn->getObject()->Transform.Position.x, pwn->getObject()->Transform.Position.y);
	//win.draw(circ);
}

void Juggernaut::RenderTheWindow()
{
}

void Juggernaut::UserInput(float x, float y, GameObject *First, GameObject *Second, GameObject *Third, GameObject *Fourth, int MoveWhich)
{
	if (MoveWhich == 0)
	{
		First->Translate(First->Transform.Position.x + x, First->Transform.Position.y + y);
		//First->TranslateMe(x,y);
	}
	if (MoveWhich == 1)
	{
		Second->Translate(Second->Transform.Position.x + x, Second->Transform.Position.y + y);
		//Second->TranslateMe(x, y);
	}
	if (MoveWhich == 2)
	{
		Third->Translate(Third->Transform.Position.x + x, Third->Transform.Position.y + y);
		//Third->TranslateMe(x, y);
	}
	if (MoveWhich == 3)
	{
		Fourth->Translate(Fourth->Transform.Position.x + x, Fourth->Transform.Position.y + y);
		//Fourth->TranslateMe(x, y);
	}
}

GameObject* SpawnNewObject(float newX, float newY, float scale, std::string name, sf::Color fillCol, float radius)
{
	GameObject* spawned = new GameObject();
	spawned->SetPosition(newX, newY);
	spawned->SetScale(scale);
	spawned->SetSphereColor(fillCol);
	spawned->SetRadius(radius);

	return spawned;
}

GameObject* SpawnNewObject()
{
	GameObject* spawned = new GameObject();
	return spawned;
}
