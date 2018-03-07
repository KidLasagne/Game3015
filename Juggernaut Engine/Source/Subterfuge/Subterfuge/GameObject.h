#pragma once

#include "BaseComponent.h"
#include "transform.h"
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

//using namespace std;

class GameObject
{
public:
	GameObject()
	{
		InitializeGameObject();
	}
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	void SetPosition(float x, float y);
	void SetRotation(float rot);
	void SetScale(float s);
	void InitializeGameObject();
	void SetTexture(std::string name);
	void RenderSprite();
	sf::Sprite GetSprite();

	transform transform;
	
	GameObject* parent;
	std::vector<GameObject*> childObjects;

	sf::Texture texture;
	sf::Sprite sprite; // (tex);
};

