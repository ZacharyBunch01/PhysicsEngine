// GLM
#include <glm/glm/glm.hpp>

// Pragma
#pragma once

class Collider
{
public:
    enum ColliderType
    {
        BOX_COLLIDER,
        SPHERE_COLLIDER,
        PLANE_COLLIDER,
        NULL_COLLIDER
    };

    Collider();
    Collider(ColliderType colliderType);

    ColliderType GetType() const;

    // Box collider specific
    void SetBox(const glm::vec3& center, const glm::vec3& halfSize);
    glm::vec3 GetBoxCenter() const;
    glm::vec3 GetBoxHalfSize() const;

    // Sphere collider specific
    void SetSphere(const glm::vec3& center, float radius);
    glm::vec3 GetSphereCenter() const;
    float GetSphereRadius() const;

    // Plane collider specific
    void SetPlane(const glm::vec3& normal, float distance);
    glm::vec3 GetPlaneNormal() const;
    float GetPlaneDistance() const;

private:
    ColliderType type;

    // Box collider properties
    glm::vec3 boxCenter;
    glm::vec3 boxHalfSize;

    // Sphere collider properties
    glm::vec3 sphereCenter;
    float sphereRadius;

    // Plane collider properties
    glm::vec3 planeNormal;
    float planeDistance;
};

