#include <vector>
#include "rigidbody.hpp"
#include "../../scene.hpp"

// Pragma
#pragma once

class PhysicsEngine
{
public:
    void Simulate(float delta, Scene& scene);
    void HandleCollisions(Scene& scene);

private:
   CollisionData CheckCollision(const RigidBody& bodyA, const RigidBody& bodyB);

    void ResolveCollision(RigidBody& bodyA, RigidBody& bodyB);
};

