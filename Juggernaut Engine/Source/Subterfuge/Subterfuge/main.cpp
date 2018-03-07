#include <SFML/Graphics.hpp>
#include "GameObject.h"

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