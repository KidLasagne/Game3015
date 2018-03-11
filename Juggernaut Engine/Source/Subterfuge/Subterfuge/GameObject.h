#pragma once

#define M_PI 3.14159265358979323846

#include "BaseComponent.h"
#include "transform.h"
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>


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

	//void SetLocalPosition(float x, float y);
	void SetRotation(float rot);
	void SetPosition(float x, float y);
	//void SetWorldRotation(float rot);
	void SetScale(float s);
	void InitializeGameObject();
	void SetTexture(std::string name, sf::Sprite spr, float width, float height, float startX, float startY, float posX, float posY, float scaleX, float scaleY, float rot);
	void RenderSprite();
	sf::Sprite GetSprite();
	void SetName(std::string str) { name = str; }
	std::string GetName() { return name; }
	void AttachChild(GameObject*);
	void PushBaseComponent(BaseComponent* baseC);
	GameObject* FindObjectByName(std::string nam);
	transform AddTransform(transform otherTransform, transform selfTransform);
	void GameObject::Rotate(float angle);
	void GameObject::Rotate(transform center, float angle);
	double GameObject::Deg2Rad(double degrees);
	sf::CircleShape GetSphere() { return circleShape; }
	void SetSphereColor(sf::Color sphereColor) { circleShape.setFillColor(sphereColor); }
	void SetRadius(float rad) { circleShape.setRadius(rad); }
	float GetRadius() { return circleShape.getRadius(); }
	float GetRotation() { return Transform.Rotation; }
	//float GetLocalRotation() { return Transform.Rotation; }
	void SnapToParent();
	void SnapToParentWithRotation();
	void Translate(float Xtarget, float Ytarget);
	void TranslateMe(float VectorX, float VectorY);
	//void LocalTranslate(float VectorX, float VectorY);

	sf::Vector2f GetPosition(transform target);

	transform GetTransform() { return Transform; }
	//transform GetLocalTransform() { return Transform; }

	//transform worldTransform;
	transform Transform;
	std::string name;

	GameObject* parent;
	std::vector<GameObject*> childObjects;
	std::vector<BaseComponent*> BaseComponentList;

	sf::Texture texture;
	sf::Sprite sprite; // (tex);
	sf::CircleShape circleShape;

};

