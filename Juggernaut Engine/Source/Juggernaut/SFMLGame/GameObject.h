#pragma once
//#include "GameObject.h"
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

class GameObject
{
public:

	GameObject() 
	{
		parent = NULL; 
	}

	GameObject(float myX, float myY, float ang, float siz, sf::Color col, float originX, float originY)
	{
		parent = NULL;
		
		transform.setPosition(myX,myY);
		transform.setRotation(ang);
		SetSize(siz);
		SetColor(col);
		SetOrigin(originX, originY);
	}
	~GameObject(void);
	void SetTransform(const sf::Transformable &matrix) { transform = matrix; }
	sf::Transformable GetTransform() { return transform; }
	sf::Transformable GetWorldTransform() { return worldTransform; }
	void SetParent(GameObject* p) { parent = p; }
	void AddChild(GameObject* s);
	void SetSize(float newSize)
	{
		size = newSize;
	}
	float GetSize()
	{
		return size;
	}
	virtual void Update(float msec);
	sf::Transformable MultiplyTransforms(sf::Transformable selfTransform, sf::Transformable otherTransformable)
	{
		sf::Transformable storageTransformable;
		storageTransformable.setRotation(selfTransform.getRotation() + otherTransformable.getRotation());
		storageTransformable.setPosition(storageTransformable.getRotation() * (otherTransformable.getPosition().x + selfTransform.getPosition().x), storageTransformable.getRotation() * (otherTransformable.getPosition().y + selfTransform.getPosition().y ) );

		return storageTransformable;
	}

	/*
	sf::Transformable operator* (const sf::Transformable& other) const
	{
		sf::Transformable storageTransformable;
		storageTransformable.setRotation(transform.getRotation() * other.getRotation());
		storageTransformable.setPosition(transform.getRotation() * (other.getPosition() + transform.getPosition()));
		//storageTransformable.setScale(selfTransform.getScale);
		

		return storageTransformable;
	}
	*/

	void UpdateMyShape()
	{
		myCircle.setPosition(transform.getPosition());
		myCircle.setRotation(transform.getRotation());
		myCircle.setOrigin(transform.getOrigin());
		myCircle.setFillColor(myColor);
		myCircle.setRadius(size);
	}

	void MakeRotate(float msec)
	{
		//transform.setRotation(transform.getRotation() + msec);
		transform.rotate(msec);
	}

	void SetColor(sf::Color col)
	{
		myColor = col;
	}

	void SetOrigin(float orgX, float orgY)
	{
		transform.setOrigin(orgX,orgY);
	}

	sf::CircleShape GetMyCircle()
	{
		return myCircle;
	}

protected:

	GameObject* parent;
	sf::Transformable worldTransform;
	sf::Transformable transform;
	std::vector<GameObject*> children;
	float size;
	sf::CircleShape myCircle;
	sf::Color myColor;
};