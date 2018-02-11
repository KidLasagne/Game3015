#pragma once

class SceneGraph
{ 
	public:

		enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

		SceneGraph(float centX, float centY, bool amExit) //GameState gamSt)
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
			GameObject *scene = new GameObject(960, 540, 0.0f, 50.0f, sf::Color::Blue, 50, 50);
			GameObject *sun = new GameObject(960, 540, 45.0f, 50.0f, sf::Color::Red, 250, 50);
			GameObject *earth = new GameObject(960, 540, 90.0f, 50.0f, sf::Color::Green, 350, 50);
			GameObject *moon = new GameObject(960, 540, 135.0f, 50.0f, sf::Color::White, 450, 50);

			//GameObject *nibiru = new GameObject(centerX, centerY, 0.0f, 50.0f);

			scene->AddChild(sun);
			sun->AddChild(earth);
			earth->AddChild(moon);

			sf::Clock clock;

			while (window.isOpen() && GetAmIExiting() == false)
			{
				HandleExitConditions();

				sf::Time elapsed = clock.restart();

				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				scene->Update(0.02);

				scene->UpdateMyShape();
				sun->UpdateMyShape();
				earth->UpdateMyShape();
				moon->UpdateMyShape();

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

};
