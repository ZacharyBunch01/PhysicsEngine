#include "rigidbody.hpp"

RigidBody::RigidBody(PhysicsID in, const glm::vec3 inPos, const glm::vec3 inVelocity, glm::vec3 inMinExtents, glm::vec3 inMaxExtents) : physicsID(in), position(inPos), velocity(inVelocity), minExtents(inMinExtents), maxExtents(inMaxExtents) {
	initPhys(in);
}

RigidBody::RigidBody(PhysicsID in, const glm::vec3 inPos, const glm::vec3 inVelocity, float inRadius)
    : physicsID(in), position(inPos), velocity(inVelocity), radius(inRadius)
{
	initPhys(in);
}

void RigidBody::initPhys(PhysicsID in) {
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

void RigidBody::InitRigidBody(const glm::vec3 inPos, const glm::vec3 inVelocity)
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
    this->collider = std::make_unique<BoundingBox>(this->minExtents, this->maxExtents);
}

void RigidBody::InitPlaneCollider()
{
    this->collider = std::make_unique<BoundingBox>(this->minExtents, this->maxExtents);
}

void RigidBody::InitSphereCollider()
{
	this->collider = std::make_unique<BoundingSphere>(this->position, this->radius);
}
