//Project files
#include "math/physics/rigidbody.hpp"

// Pragma
#pragma once

struct Object
{
public:
    Object(const char* modelPath, PhysicsID in, glm::vec3 inPosition = glm::vec3(0.0f), glm::vec3 minExtents = glm::vec3(0.1f), glm::vec3 maxExtents = glm::vec3(1.0f));
    Object(const char* modelPath, PhysicsID in = PhysicsID::SPHERE, glm::vec3 inPosition = glm::vec3(0.0f), float inRadius = 1.0f);
    Object(const char* modelPath, PhysicsID in, glm::vec3 inPosition = glm::vec3(0.0f));

    const char* modelFile;

    glm::vec3 Position = glm::vec3(0.0f);
    glm::quat Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(1.0f);

    glm::vec3 Velocity = glm::vec3(0.0f);
    float Mass = 1.0f;
    glm::vec3 Force = glm::vec3(0.0f);
    //Collider collider;
    RigidBody rigidBody = RigidBody(PhysicsID::BOX, glm::vec3(0.0f), glm::vec3(0.0f), 0.0f);

    std::vector <glm::vec3> vertices;
    std::vector <glm::vec2> textureCoords;
    std::vector <glm::vec3> normals;

    void render();
    void destroy();

    bool affectedByGravity = true;

    void ApplyGravity(float dt, glm::vec3 gravity);

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int normalBuffer;
    unsigned int textureBuffer;

    PhysicsID physicsID;

    void InitPhysicsBody();

    glm::vec3 minExtents = glm::vec3(0.0f);
    glm::vec3 maxExtents = glm::vec3(0.0f);

    float radius = 0.0f;
};

