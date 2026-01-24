#include "collider.hpp"

void Collider::SetType(ColliderID inType) {
	this->type = inType;
}

float MaxFunction(glm::vec3& vec)
{
	float result = vec[0];

	for (int i = 0; i < 3; i++)
	{
		if (vec[i] > result)
			result = vec[i];
	}

	return result;
}

glm::vec3 MaxFunction(glm::vec3& vec, glm::vec3& vec2)
{
	glm::vec3 result;

	for (int i = 0; i < 3; i++)
	{
		result[i] = vec[i] > vec2[i] ? vec[i] : vec2[i];
	}

	return result;
}

void Collider::MoveCollider(glm::vec3 inPos)
{
	this->Position = inPos;

	switch (this->type)
	{
	case(ColliderID::BOX):

		break;
	case(ColliderID::PLANE):
		

		break;
	case(ColliderID::SPHERE):
		  

		break;
	}
}

CollisionData Collider::Collision(const Collider& other) const
{
	BoundingBox* box;
	BoundingSphere* sphere;
	BoundingPlane* plane;

	// This is really terrible, I'm so sorry.
	switch (type)
	{
	case(ColliderID::BOX):

		switch (other.GetType())
		{
		case(ColliderID::BOX):
				// std::cout << "box-box" << std::endl;

				box = (BoundingBox*)this;
				return box->CollisionBoundingBox((BoundingBox&)other);
			break;

		case(ColliderID::SPHERE):

			break;

		case(ColliderID::PLANE):

			break;
		}

		break;

	case(ColliderID::SPHERE):

		switch (other.GetType())
		{
		case(ColliderID::BOX):

			/*
			CollisionData collisionData = scene.GetObject(i)->GetBoundingSphere().CollisionBoundingBox(scene.GetObject(i)->GetBoundingBox());

			if (collisionData.getDoesCollide())
			{
				scene.GetObject(i)->rigidBody.SetVelocity(scene.GetObject(i)->Velocity * glm::vec3(-1.0f));
				scene.GetObject(j)->rigidBody.SetVelocity(scene.GetObject(j)->Velocity * glm::vec3(-1.0f));
			}
			*/

			break;

		case(ColliderID::SPHERE):

			// std::cout << "sphere-sphere" << std::endl;

			sphere = (BoundingSphere*)this;

			return sphere->CollisionBoundingSphere((BoundingSphere&)other);

			break;

		case(ColliderID::PLANE):

			break;
		}

		break;

	case(ColliderID::PLANE):

		switch (other.GetType())
		{
		case(ColliderID::BOX):

			break;

		case(ColliderID::SPHERE):

			break;

		case(ColliderID::PLANE):

			break;
		}

		break;
	}


	exit(1);

	return CollisionData(false, 0);
}

void Collider::Transform(const glm::vec3& translation)
{

}


CollisionData BoundingBox::CollisionBoundingBox(const BoundingBox& box) const
{
	glm::vec3 distance1 = box.GetMinExtents() - maxExtents;
	glm::vec3 distance2 = minExtents - box.GetMaxExtents();
	glm::vec3 distances = glm::vec3(MaxFunction(distance1, distance2));

	float maxDistance = MaxFunction(distances);

	return CollisionData(maxDistance < 0, maxDistance);
}

BoundingPlane BoundingPlane::Normalized() const
{
	float maginitude = normal.length();

	return BoundingPlane(normal / maginitude, distance / maginitude);
}

CollisionData BoundingPlane::CollisionBoundingSphere(const BoundingSphere& sphere) const
{
	float distanceFromSphereCenter = glm::abs(glm::dot(normal, sphere.GetCenter()) + distance);
	float distanceFromSphere = distanceFromSphereCenter - sphere.GetRadius();

	return CollisionData(distanceFromSphere < 0, distanceFromSphere);
}

CollisionData BoundingSphere::CollisionBoundingSphere(const BoundingSphere& sphere)
{
	float radiusDistance = radius + sphere.radius;
	float centerDistance = glm::length(sphere.Position - this->Position);
	float distance = centerDistance - radiusDistance;

	return CollisionData(centerDistance < radiusDistance, distance);
}

void BoundingSphere::Transform(const glm::vec3& translation)
{
	center += translation;
}
