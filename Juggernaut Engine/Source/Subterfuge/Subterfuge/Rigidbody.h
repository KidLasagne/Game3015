#pragma once

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "PhysicsEngine.h"
#include "BaseComponent.h"
#include "transform.h"
#include "GameObject.h"

class Rigidbody
{
public:
	/*

	Rigidbody(GameObject* gam);
	~Rigidbody();

	float mass = 1.0f;                             // Mass of the RigidBody
	float bounciness = 1;                        // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity = true;                    // Whether or not this body obeys gravity
	sf::Vector2f gravity = sf::Vector2f(0, -9.8f);     // The gravity vector applied to this body

	sf::Vector2f currentVelocity;                     // The current velocity the body is moving at
	sf::Vector2f maxVelocity = sf::Vector2f(10.0f, 10.0f); // The maximum allowed velocity for this object

	bool grounded;

	struct AABB
	{
		sf::Vector2f bLeft;
		sf::Vector2f tRight;
	};

	AABB aabb;

	sf::Vector2f totalForces;
	PhysicsEngine engine;

	void AddForce(sf::Vector2f force);
	void Stop();
	bool IsGrounded();
	void SetAABB();
	void Start();
	void Integrate(float dT);

	transform Transform;
	GameObject* attachedObject;

	*/
};

