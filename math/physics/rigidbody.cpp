#include "rigidbody.hpp"

RigidBody::RigidBody(PhysicsID in, const glm::vec3& inPos, const glm::vec3& inVelocity, float inRadius)
    : physicsID(in), position(inPos), velocity(inVelocity), radius(inRadius), collider(Collider::BOX_COLLIDER)
{
    switch (in)
    {
    case BOX:
        InitBoxCollider();
        break;
    case PLANE:
        InitPlaneCollider();
        break;
    case SPHERE:
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
    this->collider = Collider(Collider::BOX_COLLIDER);
}

void RigidBody::InitPlaneCollider()
{
    this->collider = Collider(Collider::PLANE_COLLIDER);
}

void RigidBody::InitSphereCollider()
{
    this->collider = Collider(Collider::SPHERE_COLLIDER);
}
