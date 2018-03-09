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

	gam1->SetName("g1");
	gam2->SetName("g2");
	gam3->SetName("g3");
	gam4->SetName("g3");

	gam1->AttachChild(gam2);
	gam1->AttachChild(gam3);
	gam1->AttachChild(gam4);

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
	std::cout << "Object Name: " << gam1->FindObjectByName("g3")->GetName() << std::endl;
	if (gam1->FindObjectByName("powerman") == NULL)
	{
		std::cout << "No Object Found." << std::endl;
	}
	else
	{
		std::cout << "Found it!" << std::endl;
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//window.clear();
		//window.draw(sprite);
		//window.display();
	}

	return 0;
}