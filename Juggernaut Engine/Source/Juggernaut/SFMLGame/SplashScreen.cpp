#include "stdafx.h"
#include "SplashScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };



SplashScreen::SplashScreen()
{
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture tex;

	//sf::Image image; 
	//C:\Users\squee\Documents\GitHub\Game3015\Juggernaut Engine\Assets
	//if (tex.loadFromFile("$(SolutionDir)\..\..\Assets\TheCommissionersMagnificence.png") != true)

	if (!tex.loadFromFile("TheCommissionersMagnificence.png"))
	{ 
		std::cout << "The Image Was Not Found..." << std::endl;
		return; 
	}

	sf::Sprite sprite; // (tex);
	sprite.setTexture(tex);
	renderWindow.draw(sprite); 
	renderWindow.display();

	sf::Event theEvent;
	bool IsQuittingLoop = false;

	while (IsQuittingLoop == false)
	{
		while (renderWindow.pollEvent(theEvent))
		{
			if (theEvent.type == sf::Event::KeyPressed)
			{
				std::cout << "Exiting...(keyPressed)" << std::endl;
				IsQuittingLoop = true;
				return;
			}
			if (theEvent.type == sf::Event::MouseButtonPressed)
			{
				std::cout << "Exiting...(mouseClick)" << std::endl;
				IsQuittingLoop = true;
				return;
			}
		}
	}
	/*
	sf::Event event; 
	while(renderWindow.pollEvent(event))
	{ 
		if(event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed )
		{ 
			return; 
		} 
	} 
	*/
}