#include "PhysicsEngine.h"

/*
PhysicsEngine::PhysicsEngine()
{
}


PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddRigidBody(Rigidbody rigidBody) {
	rigidBodies.Add(rigidBody);
}

void PhysicsEngine::IntegrateBodies(float dT) 
{
	for (auto& rb : rigidBodies)
	{
		rb.Integrate(dT);
	}
}

bool PhysicsEngine::IsGrounded(Rigidbody rigidBody) 
{
	for (auto& rb : rigidBodies)
	{
		if (rb != rigidBody) 
		{
			if (rigidBody.aabb.bLeft.x < rb.aabb.tRight.x && rigidBody.aabb.tRight.x > rb.aabb.bLeft.x && std::abs (rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= groundedTol) 
			{
				if (std::abs(rigidBody.currentVelocity.y) < groundedTol)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void PhysicsEngine::CheckCollisions() 
{
	for (auto& bodyA : rigidBodies )
	{
		for (auto& bodyB : rigidBodies)
		{
		//foreach(Rigidbody bodyA in rigidBodies.GetRange(0, rigidBodies.Count - 1)) {
		//foreach(PhysicsRBody bodyB in rigidBodies.GetRange(rigidBodies.IndexOf(bodyA), rigidBodies.Count - rigidBodies.IndexOf(bodyA))) {
			if (bodyA != bodyB) 
			{
				CollisionPair pair = new CollisionPair();
				CollisionInfo colInfo = new CollisionInfo();
				pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;

				sf::Vector2f distance = bodyB.transform.position - bodyA.transform.position;

				sf::Vector2f halfSizeA = (bodyA.aabb.tRight - bodyA.aabb.bLeft) / 2;
				sf::Vector2f halfSizeB = (bodyB.aabb.tRight - bodyB.aabb.bLeft) / 2;

				sf::Vector2f gap = new sf::Vector2f(std::abs(distance.x), std::abs(distance.y)) - (halfSizeA + halfSizeB);

				// Seperating Axis Theorem test
				if (gap.x < 0 && gap.y < 0) {
					//Debug.Log("Collided!!!");

					if (collisions.ContainsKey(pair)) {
						collisions.Remove(pair);
					}

					if (gap.x > gap.y) {
						if (distance.x > 0) {
							// ... Update collision normal
						}
						else {
							// ... Update collision normal
						}
						colInfo.penetration = gap.x;
					}
					else {
						if (distance.y > 0) {
							// ... Update collision normal
						}
						else {
							// ... Update collision normal
						}
						colInfo.penetration = gap.y;
					}
					collisions.Add(pair, colInfo);
				}
				else if (collisions.ContainsKey(pair)) {
					//Debug.Log("removed");
					collisions.Remove(pair);
				}
			}
		}
	}
}

void PhysicsEngine::ResolveCollisions() 
{
	for (auto& pair : collisions.Keys)
	{
	//foreach(CollisionPair pair in collisions.Keys) {
		float minBounce = std::min(pair.rigidBodyA.bounciness, pair.rigidBodyB.bounciness);
		float velAlongNormal = sf::Vector2f .Dot(pair.rigidBodyB.currentVelocity - pair.rigidBodyA.currentVelocity, collisions[pair].collisionNormal);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		if (pair.rigidBodyA.mass == 0)
			invMassA = 0;
		else
			invMassA = 1 / pair.rigidBodyA.mass;

		if (pair.rigidBodyB.mass == 0)
			invMassB = 0;
		else
			invMassB = 1 / pair.rigidBodyB.mass;

		j /= invMassA + invMassB;

		sf::Vector2f impulse = j * collisions[pair].collisionNormal;

		// ... update velocities

		if (std::abs(collisions[pair].penetration) > 0.01f) {
			PositionalCorrection(pair);
		}
	}
}


//______________ Why do we need this function?
//______________ Try taking it out and see what happens

void PhysicsEngine::PositionalCorrection(CollisionPair c) {
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (c.rigidBodyA.mass == 0)
		invMassA = 0;
	else
		invMassA = 1 / c.rigidBodyA.mass;

	if (c.rigidBodyB.mass == 0)
		invMassB = 0;
	else
		invMassB = 1 / c.rigidBodyB.mass;

	sf::Vector2f correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

	sf::Vector2f temp = c.rigidBodyA.transform.position;
	temp -= invMassA * correction;
	c.rigidBodyA.transform.position = temp;

	temp = c.rigidBodyB.transform.position;
	temp += invMassB * correction;
	c.rigidBodyB.transform.position = temp;
}

void PhysicsEngine::UpdatePhysics() {
	// .... 
}

// Update is called once per frame
void PhysicsEngine::FixedUpdate() {
	UpdatePhysics();
}

*/