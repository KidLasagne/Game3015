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

	bool IsExiting();

	void Start();

	void Initialize()
	{
		_gameState = GameState::Uninitialized;
	}

	void MainLoop()
	{
		Initialize();
		Start();
	}

	void HandleExitConditions();

	void DoEverything();

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
