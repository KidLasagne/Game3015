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
	First->SetSphereColor(sf::Color::Blue);
	Second->SetWorldPosition(0, 0);
	Second->SetLocalPosition(100, 100);
	Second->SetSphereColor(sf::Color::Red);
	Third->SetWorldPosition(0, 0);
	Third->SetLocalPosition(100, 100);
	Third->SetSphereColor(sf::Color::Yellow);
	Fourth->SetWorldPosition(0, 0);
	Fourth->SetLocalPosition(100, 100);
	Fourth->SetSphereColor(sf::Color::Green);

	
	//Second->SetWorldPosition(Second->AddTransform(First->GetWorldTransform(), Second->GetLocalTransform()).Position.x, Second->AddTransform(First->GetWorldTransform(), Second->GetLocalTransform()).Position.y);

	First->AttachChild(Second);
	Second->AttachChild(Third);
	Third->AttachChild(Fourth);

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

	Beginning();

	while (window.isOpen())
	{
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