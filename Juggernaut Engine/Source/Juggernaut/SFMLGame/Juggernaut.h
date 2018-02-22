#pragma once

#include "SplashScreen.h"
#include "GameObject.h"

class Juggernaut
{
public:

	enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	Juggernaut(float centX, float centY, bool amExit) //GameState gamSt)
	{
		SetCenterX(centX);
		SetCenterY(centY);
		SetAmIExiting(amExit);
		//SetGameState(gamSt);
	}

	bool IsExiting()
	{
		//bool b = GetAmIExiting();

		if (AmIExiting == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Start()
	{
		if (_gameState != GameState::Uninitialized)
		{
			return;
		}

		window.create(sf::VideoMode(1920, 1080), "SFML works!");

		splashScreen.Show(window);

		_gameState = GameState::Playing;

		while (!IsExiting())
		{
			DoEverything();
		}
	}

	void Initialize()
	{
		_gameState = GameState::Uninitialized;
	}

	void MainLoop()
	{
		Initialize();
		Start();
	}

	void HandleExitConditions()
	{
		sf::Event theEvent;

		while (window.pollEvent(theEvent))
		{
			if (theEvent.type == sf::Event::KeyPressed)
			{
				// move left...
				_gameState = GameState::Exiting;
				SetAmIExiting(true);
			}
			if (theEvent.type == sf::Event::MouseButtonPressed)
			{
				// mouse click...
				_gameState = GameState::Exiting;
				SetAmIExiting(true);
			}
		}
	}

	void DoEverything()
	{
		/*
		GameObject *scene = new GameObject(960, 540, 0.0f, 50.0f, sf::Color::Blue, 50, 50);
		GameObject *sun = new GameObject(960, 640, 45.0f, 50.0f, sf::Color::Red, 250, 50);
		GameObject *earth = new GameObject(960, 740, 90.0f, 50.0f, sf::Color::Green, 350, 50);
		GameObject *moon = new GameObject(960, 840, 135.0f, 50.0f, sf::Color::White, 450, 50);

		GameObject *scene = new GameObject(960, 540, 0.0f, 50.0f, sf::Color::Blue, 0, 0, 960, 540);
		GameObject *sun = new GameObject(960, 540, 45.0f, 50.0f, sf::Color::Red, scene->GetWorldTransform().getPosition().x + 50, scene->GetWorldTransform().getPosition().y, 0, 0);
		GameObject *earth = new GameObject(960, 540, 90.0f, 50.0f, sf::Color::Green, sun->GetWorldTransform().getPosition().x, sun->GetWorldTransform().getPosition().y, 0, 0);
		GameObject *moon = new GameObject(960, 540, 135.0f, 50.0f, sf::Color::White, earth->GetWorldTransform().getPosition().x, earth->GetWorldTransform().getPosition().y, 0, 0);

		GameObject *scene = new GameObject(960, 540, 0.0f, 50.0f, sf::Color::Blue, 0, 0, 960, 540);
		GameObject *sun = new GameObject(960, 540, 45.0f, 50.0f, sf::Color::Red, 50, 0, 0, 0);
		GameObject *earth = new GameObject(960, 540, 90.0f, 50.0f, sf::Color::Green, 100, 0, 0, 0);
		GameObject *moon = new GameObject(960, 540, 135.0f, 50.0f, sf::Color::White, 150, 0, 0, 0);
		*/

		GameObject *scene = new GameObject(0, 0, 0.0f, 50.0f, sf::Color::Blue, 0, 0, 0, 0, 0);
		GameObject *sun = new GameObject(50, 50, 45.0f, 50.0f, sf::Color::Red, 0, 0, 0, 0, 1);
		GameObject *earth = new GameObject(100, 100, 90.0f, 50.0f, sf::Color::Green, 0, 0, 0, 0, 2);
		GameObject *moon = new GameObject(150, 150, 135.0f, 50.0f, sf::Color::White, 0, 0, 0, 0, 3);

		//GameObject *nibiru = new GameObject(centerX, centerY, 0.0f, 50.0f);

		scene->AddChild(sun);
		sun->AddChild(earth);
		earth->AddChild(moon);

		sf::Clock clock;

		while (window.isOpen() && GetAmIExiting() == false)
		{
			HandleExitConditions();

			//sf::Time elapsed = clock.restart();
			sf::Time elapsed = clock.getElapsedTime();


			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//scene->Update(0.02);
			scene->Update(elapsed.asSeconds());

			clock.restart();
			/*
			scene->UpdateMyShape();
			sun->UpdateMyShape();
			earth->UpdateMyShape();
			moon->UpdateMyShape();
			*/

			//void UpdateMyShape(float myXPos, float myYPos, float myRot, sf::Color myCol, float myOriginX, float myOriginY, float mySize)

			/*
			scene->UpdateMyShape(scene->GetWorldTransform().getPosition().x, scene->GetWorldTransform().getPosition().y, scene->GetWorldTransform().getRotation(), sf::Color::Blue, scene->GetWorldTransform().getOrigin().x, scene->GetWorldTransform().getOrigin().y, scene->GetSize());
			sun->UpdateMyShape(sun->GetWorldTransform().getPosition().x, sun->GetWorldTransform().getPosition().y, sun->GetWorldTransform().getRotation(), sf::Color::Red, scene->GetWorldTransform().getOrigin().x, scene->GetWorldTransform().getOrigin().y, sun->GetSize());
			earth->UpdateMyShape(earth->GetWorldTransform().getPosition().x, earth->GetWorldTransform().getPosition().y, earth->GetWorldTransform().getRotation(), sf::Color::Green, sun->GetWorldTransform().getOrigin().x, sun->GetWorldTransform().getOrigin().y, earth->GetSize());
			moon->UpdateMyShape(moon->GetWorldTransform().getPosition().x, moon->GetWorldTransform().getPosition().y, moon->GetWorldTransform().getRotation(), sf::Color::White, earth->GetWorldTransform().getOrigin().x, earth->GetWorldTransform().getOrigin().y, moon->GetSize());
			*/

			scene->UpdateMyShape();
			sun->UpdateMyShape();
			earth->UpdateMyShape();
			moon->UpdateMyShape();

			//sun->Update;
			//earth->Update;
			//moon->Update;

			window.clear();
			window.draw(scene->GetMyCircle());
			window.draw(sun->GetMyCircle());
			window.draw(earth->GetMyCircle());
			window.draw(moon->GetMyCircle());
			window.display();
		}
	}

	float GetCenterX() { return centerX; }
	void SetCenterX(float x) { centerX = x; }
	float GetCenterY() { return centerY; }
	void SetCenterY(float y) { centerY = y; }
	bool GetAmIExiting() { return AmIExiting; }
	void SetAmIExiting(bool val) { AmIExiting = val; }
	//GameState GetGameState() { return _gameState; }
	//void SetGameState(GameState gam) { _gameState = gam; }

private:

	float centerX;
	float centerY;
	bool AmIExiting;
	GameState _gameState;
	sf::RenderWindow window;
	SplashScreen splashScreen;

};
