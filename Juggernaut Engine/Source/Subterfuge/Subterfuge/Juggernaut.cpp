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

	Second->Move(4,2,board);
	Second->team = 2;
	Second->getObject()->SetSphereColor(sf::Color::Blue);

	//Manager.PushGameObject(First->getObject());
	Manager.PushPawn(First);
	Manager.PushPawn(Second);

	sf::Clock clock; // starts the clock
	DisplayString = "Starting Game...";

	while (window.isOpen())
	{
		window.clear();

		sf::Time elapsed = clock.getElapsedTime();
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
			Pawn::vectorBool vec;


			//vec = First->DoUserInput(event, board, Database);
			vec = RetrieveLowestTurnOrder(Manager)->DoUserInput(event, board, Database);
			
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

		if (elapsed.asSeconds() < 4.0f)
		{
			ShowText(DisplayString, window);
		}

		for (auto& pawn : Manager.GetPawnLibrary())
		{
			pawn->ShedTime();
		}

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
