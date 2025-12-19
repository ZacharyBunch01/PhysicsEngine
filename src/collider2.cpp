#include "collider.hpp"

Collider::Collider() : type(NULL_COLLIDER) {}

Collider::Collider(ColliderType colliderType) : type(colliderType) {}

Collider::ColliderType Collider::GetType() const
{
    return type;
}

// Box collider specific
void Collider::SetBox(const glm::vec3& center, const glm::vec3& halfSize)
{
    type = BOX_COLLIDER;
    boxCenter = center;
    boxHalfSize = halfSize;
}

glm::vec3 Collider::GetBoxCenter() const
{
    return boxCenter;
}

glm::vec3 Collider::GetBoxHalfSize() const
{
    return boxHalfSize;
}

// Sphere collider specific
void Collider::SetSphere(const glm::vec3& center, float radius)
{
    type = SPHERE_COLLIDER;
    sphereCenter = center;
    sphereRadius = radius;
}

glm::vec3 Collider::GetSphereCenter() const
{
    return sphereCenter;
}

float Collider::GetSphereRadius() const
{
    return sphereRadius;
}

// Plane collider specific
void Collider::SetPlane(const glm::vec3& normal, float distance)
{
    type = PLANE_COLLIDER;
    planeNormal = normal;
    planeDistance = distance;
}

glm::vec3 Collider::GetPlaneNormal() const
{
    return planeNormal;
}

float Collider::GetPlaneDistance() const
{
    return planeDistance;
}
