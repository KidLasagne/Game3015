#include "Rigidbody.h"

/*

Rigidbody::Rigidbody(GameObject* gam)
{
	attachedObject = gam;
	Transform = attachedObject->Transform;
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::AddForce(sf::Vector2f force)
{
	totalForces += force;
}

void Rigidbody::Stop()
{
	currentVelocity = sf::Vector2f (0,0);
	totalForces = sf::Vector2f(0,0);
}

bool Rigidbody::IsGrounded()
{
	grounded = engine.IsGrounded(this);
	return grounded;
}

// ______________ <-What does this function do?

void Rigidbody::SetAABB()
{
	Bounds bound = new Bounds(new sf::Vector2f(0, 0), new sf::Vector2f(1, 1));
	Renderer renderer = GetComponent<Renderer>();

	if (renderer)
	{
		bound = renderer.bounds;
	}

	aabb.bLeft = new sf::Vector2f(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
	aabb.tRight = new sf::Vector2f(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
}

void Rigidbody::Start() {
	SetAABB();
	engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();

	engine.AddRigidBody(this);
}

// ______________ Describe how this function works

void Rigidbody::Integrate(float dT) {
	/// 
	/// ______________ What is the purpose of this part of code?
	/// 
	if (obeysGravity && !IsGrounded()) {
		AddForce(gravity);
	}
	else {
		if (std::abs(currentVelocity.y) < 0.05f) currentVelocity.y = 0;
	}
	///
	///
	///

	sf::Vector2f acceleration = totalForces / mass;
	if (mass == 0)
		acceleration = sf::Vector2f(0.0,0.0);

	currentVelocity += acceleration * dT;

	sf::Vector2f temp = Transform.Position;
	temp += currentVelocity * dT;
	Transform.Position = temp;
	SetAABB();

	totalForces = sf::Vector2f(0,0);
}

*/