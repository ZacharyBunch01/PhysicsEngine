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
    RigidBody(PhysicsID in, const glm::vec3& inPos, const glm::vec3& inVelocity, float inRadius);

    void InitRigidBody(const glm::vec3& inPos, const glm::vec3& inVelocity);

    // Updates rigidbody position; called by the physics engine
    void Integrate(float delta);

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 velocity = glm::vec3(0.0f);
    float radius = 0.0f;
    float mass = 1.0f; // Default mass
    float restitution = 0.5f; // Default restitution (elasticity)

    // Update velocity according to input
    void SetVelocity(const glm::vec3& vel);

    Collider collider;

private:
    PhysicsID physicsID;

    void InitBoxCollider();
    void InitPlaneCollider();
    void InitSphereCollider();
};

