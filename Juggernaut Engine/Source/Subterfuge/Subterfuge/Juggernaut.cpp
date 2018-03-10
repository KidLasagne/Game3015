#include "Juggernaut.h"

Juggernaut::Juggernaut()
{
}


Juggernaut::~Juggernaut()
{
}

void Juggernaut::Initialize() 
{
	// Initialize Game Here.
}

void Juggernaut::Beginning() 
{
	Initialize();
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

	sf::Clock clock; // starts the clock

	Beginning();

	while (window.isOpen())
	{

		//sf::Time elapsed1 = clock.getElapsedTime();
		//std::cout << elapsed1.asSeconds() << std::endl;
		//clock.restart();

		sf::Time elapsed2 = clock.getElapsedTime();
		std::cout << elapsed2.asSeconds() << std::endl;

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
				Second->SetLocalPosition(Second->GetLocalTransform().Position.x + 150.0f, Second->GetLocalTransform().Position.y + 50.0f);

				for (auto& game_object : Manager.GetGameObjectLibrary())
				{
					//game_object->Rotate(10.0f);
					//window.draw(game_object->GetSprite());
					//window.draw(game_object->GetSphere());
				}
			}
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