#include "rigidbody.hpp"

RigidBody::RigidBody(PhysicsID in, const glm::vec3& inPos, const glm::vec3& inVelocity, float inRadius)
    : physicsID(in), position(inPos), velocity(inVelocity), radius(inRadius)
{
    switch (in)
    {
    case PhysicsID::BOX:
        InitBoxCollider();
        break;
    case PhysicsID::PLANE:
        InitPlaneCollider();
        break;
    case PhysicsID::SPHERE:
        InitSphereCollider();
        break;
    default:
        break;
    }
    InitRigidBody(this->position, this->velocity);
}

void RigidBody::InitRigidBody(const glm::vec3& inPos, const glm::vec3& inVelocity)
{
    this->position = inPos;
    this->velocity = inVelocity;
}

void RigidBody::Integrate(float delta)
{
    // Basic integration using Euler method
    position += velocity * delta;
}

void RigidBody::SetVelocity(const glm::vec3& vel)
{
    velocity = vel;
}

void RigidBody::InitBoxCollider()
{
    this->collider = std::make_unique<Collider>(ColliderID::BOX);
}

void RigidBody::InitPlaneCollider()
{
    this->collider = std::make_unique<Collider>(ColliderID::PLANE);
}

void RigidBody::InitSphereCollider()
{
	this->collider = std::make_unique<BoundingSphere>(this->position, this->radius);
}
