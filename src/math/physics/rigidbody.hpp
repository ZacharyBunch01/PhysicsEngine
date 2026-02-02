//std
#include <memory>

// GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>
#include <GLM/glm/common.hpp>

// Project Files
#include "collider.hpp"

// Pragma
#pragma once

enum class PhysicsID { BOX, SPHERE, PLANE, NULLBODY };

class RigidBody
{
public:
    RigidBody(PhysicsID in = PhysicsID::BOX, const glm::vec3 inPos = glm::vec3(0.0f), const glm::vec3 inVelocity = glm::vec3(0.0f), glm::vec3 inMinExtents = glm::vec3(0.1f), glm::vec3 inMaxExtents = glm::vec3(1.0f));
    RigidBody(PhysicsID in, const glm::vec3 inPos, const glm::vec3 inVelocity, float inRadius);
    void InitRigidBody(const glm::vec3 inPos, const glm::vec3 inVelocity);

    // Updates rigidbody position; called by the physics engine
    void Integrate(float delta);

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 velocity = glm::vec3(0.0f);
    float radius = 1.0f;
    float mass = 1.0f; // Default mass
    float restitution = 0.5f; // Default restitution (elasticity)

    glm::vec3 minExtents = glm::vec3(0.1);
    glm::vec3 maxExtents = glm::vec3(1.0f);

    // Update velocity according to input
    void SetVelocity(const glm::vec3& vel);

    std::unique_ptr<Collider>collider = nullptr;

private:
    PhysicsID physicsID;

    void InitBoxCollider();
    void InitPlaneCollider();
    void InitSphereCollider();

    void initPhys(PhysicsID in);
};

