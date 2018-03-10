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

void Juggernaut::RenderTheWindow()
{
	sf::RenderWindow window({ 1920,1080 }, "Huzzah it works");
	window.setFramerateLimit(30);
	
	sf::CircleShape csprite;
	csprite.setFillColor(sf::Color::Blue);
	csprite.setRadius(50.0f);
	csprite.setPosition(0,0);

	GameObject *First = new GameObject();
	GameObject *Second = new GameObject();
	GameObject *Third = new GameObject();
	GameObject *Fourth = new GameObject();

	First->SetWorldPosition(0, 0);
	First->SetLocalPosition(100, 100);
	First->SetSphereColor(sf::Color::Blue);
	Second->SetWorldPosition(0, 0);
	Second->SetLocalPosition(100, 100);
	Second->GetSprite().setOrigin(0,0);
	Second->SetSphereColor(sf::Color::Red);
	Third->SetWorldPosition(0, 0);
	Third->SetLocalPosition(100, 100);
	Third->GetSprite().setOrigin(0, 0);
	Third->SetSphereColor(sf::Color::Yellow);
	Fourth->SetWorldPosition(0, 0);
	Fourth->SetLocalPosition(100, 100);
	Fourth->GetSprite().setOrigin(0, 0);
	Fourth->SetSphereColor(sf::Color::Green);

	
	//Second->SetWorldPosition(Second->AddTransform(First->GetWorldTransform(), Second->GetLocalTransform()).Position.x, Second->AddTransform(First->GetWorldTransform(), Second->GetLocalTransform()).Position.y);

	First->AttachChild(Second);
	Second->AttachChild(Third);
	Third->AttachChild(Fourth);

	//First->Rotate(90.0f);

	Manager.PushGameObject(First);
	Manager.PushGameObject(Second);
	Manager.PushGameObject(Third);
	Manager.PushGameObject(Fourth);

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

	sf::Clock clock; // starts the clock

	Beginning();

	int MoveWhich = 0;

	while (window.isOpen())
	{

		//sf::Time elapsed1 = clock.getElapsedTime();
		//std::cout << elapsed1.asSeconds() << std::endl;
		//clock.restart();

		sf::Time elapsed2 = clock.getElapsedTime();
		std::cout << elapsed2.asSeconds() << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			UserInput(-15.0f, 0.0f, First, Second, Third, Fourth, MoveWhich);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			UserInput(15.0f, 0.0f, First, Second, Third, Fourth, MoveWhich);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			UserInput(0.0f, -15.0f, First, Second, Third, Fourth, MoveWhich);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			UserInput(0.0f, 15.0f, First, Second, Third, Fourth, MoveWhich);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			First->SetWorldRotation(First->GetWorldRotation() + 10.0f);
			First->SetLocalRotation(First->GetLocalRotation() + 10.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			First->SetWorldRotation(First->GetWorldRotation() - 10.0f);
			First->SetLocalRotation(First->GetLocalRotation() - 10.0f);
		}

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
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					MoveWhich++;
					if (MoveWhich > 3)
					{
						MoveWhich = 0;
					}
				}
				/*
				//Second->SetWorldPosition(Second->GetWorldTransform().Position.x + 150.0f, Second->GetWorldTransform().Position.y + 50.0f);
				//Second->LocalTranslate(150.0f, 50.0f);
				First->Translate(150.0f, 50.0f);

				for (auto& game_object : Manager.GetGameObjectLibrary())
				{
					//game_object->Rotate(10.0f);
					//window.draw(game_object->GetSprite());
					//window.draw(game_object->GetSphere());
				}
				*/
			}
		}

		if (MoveWhich == 0)
		{
			std::cout << "Object: First" << std::endl;
		}
		if (MoveWhich == 1)
		{
			std::cout << "Object: Second" << std::endl;
		}
		if (MoveWhich == 2)
		{
			std::cout << "Object: Third" << std::endl;
		}
		if (MoveWhich == 3)
		{
			std::cout << "Object: Fourth" << std::endl;
		}

		for (auto& game_object : Manager.GetGameObjectLibrary())
		{
			if (game_object->parent != NULL)
			{
				//game_object->Rotate(game_object->parent->GetWorldTransform(), game_object->parent->GetLocalRotation());
				//game_object->Rotate(game_object->parent->GetWorldTransform(), 1.0f + elapsed2.asSeconds);
			}
			else
			{
				//game_object->Rotate(elapsed2.asSeconds() * 10.0f);
				//game_object->SetLocalRotation(elapsed2.asSeconds() * 100.0f);
				//game_object->Rotate(1.0f);
			}
			//window.draw(game_object->GetSphere());
		}

		MainLoop();

		window.clear();
		//window.draw(First->GetSphere());
		for (auto& game_object : Manager.GetGameObjectLibrary())
		{
			window.draw(game_object->GetSprite());
			//window.draw(game_object->GetSphere());
		}
		window.display();
	}
}

void Juggernaut::UserInput(float x, float y, GameObject *First, GameObject *Second, GameObject *Third, GameObject *Fourth, int MoveWhich)
{
	if (MoveWhich == 0)
	{
		First->Translate(x, y);
	}
	if (MoveWhich == 1)
	{
		Second->LocalTranslate(x, y);
	}
	if (MoveWhich == 2)
	{
		Third->LocalTranslate(x, y);
	}
	if (MoveWhich == 3)
	{
		Fourth->LocalTranslate(x, y);
	}
}

/*
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
*/