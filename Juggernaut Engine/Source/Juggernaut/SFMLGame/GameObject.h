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

	GameObject(float myX, float myY, float ang, float siz)
	{
		parent = NULL;
		
		transform.setPosition(myX,myY);
		transform.setRotation(ang);
		SetSize(siz);
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
		storageTransformable.setRotation(selfTransform.getRotation() * otherTransformable.getRotation());
		storageTransformable.setPosition(selfTransform.getRotation() * (otherTransformable.getPosition() - selfTransform.getPosition() ) );


		//sf::Transformable storageTransformable;
		//storageTransformable.setRotation(selfTransform.getRotation() * otherTransformable.getRotation());
		//storageTransformable.setPosition(selfTransform.getRotation() * (otherTransformable.getPosition() + selfTransform.getPosition()));

		//storageTransformable.setScale(selfTransform.getScale);
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

	/*
	MyClass operator* (float x, const MyClass& y)
	{
		//...
	}
	*/

	void MakeRotate(float msec)
	{
		//transform.setRotation(transform.getRotation() + msec);
		transform.rotate(msec);
	}

protected:

	GameObject* parent;
	sf::Transformable worldTransform;
	sf::Transformable transform;
	std::vector<GameObject*> children;
	float size;

};