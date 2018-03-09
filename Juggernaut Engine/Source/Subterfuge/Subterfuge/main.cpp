#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GameObjectManager.h"

int main()
{
	sf::RenderWindow window({ 1920,1080 }, "Huzzah it works");
	window.setFramerateLimit(30);

	sf::Texture tex;

	//sf::Image image; 
	//C:\Users\squee\Documents\GitHub\Game3015\Juggernaut Engine\Assets
	//if (tex.loadFromFile("$(SolutionDir)\..\..\Assets\TheCommissionersMagnificence.png") != true)

	if (!tex.loadFromFile("TheCommissionersMagnificence.png"))
	{
		std::cout << "The Image Was Not Found..." << std::endl;
	}

	sf::Sprite sprite; // (tex);
	sprite.setTexture(tex);
	window.draw(sprite);
	window.display();

	GameObject *gam1 = new GameObject();
	GameObject *gam2 = new GameObject();
	GameObject *gam3 = new GameObject();
	GameObject *gam4 = new GameObject();

	gam1->SetRotation(-90.0f);
	gam2->SetWorldPosition(100,0);
	gam2->SetSphereColor(sf::Color::Red);
	gam3->SetWorldPosition(200, 0);
	gam3->SetSphereColor(sf::Color::Green);
	gam4->SetWorldPosition(300, 0);
	gam4->SetSphereColor(sf::Color::Yellow);

	gam1->SetName("g1");
	gam2->SetName("g2");
	gam3->SetName("g3");
	gam4->SetName("g3");

	gam1->AttachChild(gam2);
	gam2->AttachChild(gam3);
	gam3->AttachChild(gam4);

	GameObjectManager *gamu = new GameObjectManager();
	gamu->PushGameObject(gam1);
	gamu->PushGameObject(gam2);
	gamu->PushGameObject(gam3);
	gamu->PushGameObject(gam4);

	std::cout << "Searching GameObject by name:" << std::endl;

	if (gamu->FindGameObjectByName("g2") != NULL)
	{
		std::cout << "I found the GameObject you were looking for, it's name is: " << gamu->FindGameObjectByName("g2")->GetName() << std::endl;
	}

	std::vector<GameObject*> tempList = gamu->FindGameObjectsByName("g3");

	std::cout << "Searching for multiple GameObjects: " << std::endl;

	int i = 1;

	for (auto& game_object : tempList)
	{
		std::cout << i << ": This GameObject is named: " << game_object->GetName() << std::endl;
		i++;
	}

	std::cout << "Testing for NULL: " << std::endl;
	//std::cout << "Object Name: " << gam1->FindObjectByName("g3")->GetName() << std::endl;
	if (gam1->FindObjectByName("powerman") == NULL)
	{
		std::cout << "No Object Found." << std::endl;
	}
	else
	{
		std::cout << "Found it!" << std::endl;
	}

	gamu->Awake();
	gamu->Start();

	float f = 0.0f;

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
				gamu->FindGameObjectByName("g1")->worldTransform.Position.x += 50.0f;
			}
		}

		gamu->FindGameObjectByName("g2")->SetRotation(50.0f);

		gamu->Update();
		gamu->LateUpdate();

		window.clear();
		for (auto& game_object : gamu->GameObjectLibrary)
		{
			window.draw(game_object->GetSphere());
		}
		window.display();

		//window.clear();
		//window.draw(sprite);
		//window.display();
	}

	return 0;
}