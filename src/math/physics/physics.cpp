#include "physics.hpp"
#include <GLM/glm/glm.hpp>
#include <algorithm> // For std::max

void PhysicsEngine::Simulate(float delta, Scene& scene)
{

    HandleCollisions(scene);

    for (unsigned int i = 0; i < scene.GetNumOfObjects(); i++)
    {
        scene.GetObject(i)->rigidBody.Integrate(delta);
    }
}

void PhysicsEngine::HandleCollisions(Scene& scene)
{
    // std::cout << "HandleCollisions is being called" << std::endl;

    // Broad Phase (skipped for simplicity in this example)

    // Narrow Phase and Resolution
    for (int i = 0; i < scene.GetNumOfObjects(); ++i) 
    {
        for (int j = 0; j < scene.GetNumOfObjects(); ++j)
        {
            auto objA = scene.GetObject(i);
            auto objB = scene.GetObject(j);

	    if (objA == objB)
	    	continue;

            if (CheckCollision(objA->rigidBody, objB->rigidBody).getDoesCollide())
            {
		std::cout << "Collision!!!" << std::endl;

                ResolveCollision(objA->rigidBody, objB->rigidBody);
            }
        }
    }
}

CollisionData PhysicsEngine::CheckCollision(const RigidBody& bodyA, const RigidBody& bodyB)
{
	return bodyA.collider->Collision(*bodyB.collider);
}

void PhysicsEngine::ResolveCollision(RigidBody& bodyA, RigidBody& bodyB)
{
    // Calculate relative velocity
    glm::vec3 relativeVelocity = bodyB.velocity - bodyA.velocity;

    // Calculate collision normal
    glm::vec3 collisionNormal = glm::normalize(bodyB.position - bodyA.position);

    // Calculate relative velocity in terms of the normal direction
    float velocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);

    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0)
        return;

    // Calculate restitution (elasticity)
    float e = std::min(bodyA.restitution, bodyB.restitution);

    // Calculate impulse scalar
    float j = -(1 + e) * velocityAlongNormal;
    j /= (1 / bodyA.mass + 1 / bodyB.mass);

    // Apply impulse
    glm::vec3 impulse = j * collisionNormal;
    bodyA.velocity -= (1 / bodyA.mass) * impulse;
    bodyB.velocity += (1 / bodyB.mass) * impulse;

    // Positional correction to avoid sinking
    float percent = 0.8f; // usually 20% to 80%
    float slop = 0.01f;   // usually 0.01 to 0.1
    glm::vec3 correction = std::max((bodyA.radius + bodyB.radius - glm::length(bodyB.position - bodyA.position)) - slop, 0.0f)
        / (1 / bodyA.mass + 1 / bodyB.mass) * percent * collisionNormal;
    bodyA.position -= (1 / bodyA.mass) * correction;
    bodyB.position += (1 / bodyB.mass) * correction;
}
