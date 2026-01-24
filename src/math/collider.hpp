//std
#include <stdio.h>
#include <iostream>
#include <vector>

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>

//Pragma
#pragma once

enum class ColliderID { BOX, SPHERE, PLANE, NULLBODY };

class CollisionData
{
public:
	CollisionData(const bool inDoesCollide, const float inDistance) : doesCollide(inDoesCollide), distance(inDistance)
	{

	}

	bool getDoesCollide() const
	{
		return doesCollide;
	}

	float getDistance() const 
	{
		return distance;
	}

private:
	const bool doesCollide;
	const float distance;

};

class BoundingBox;
class BoundingSphere;

class Collider
{
public:
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);
	glm::quat Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

	Collider(ColliderID inType) : type(inType) {
		switch(inType) {
			case(ColliderID::BOX):
			break;
			case(ColliderID::SPHERE):
			break;
			case(ColliderID::PLANE):
			break;

			default:
				break;;	
		}	
	}

	virtual ~Collider() = default; // Free up memory from our Bounding collider uniqe ptr

	CollisionData Collision(const Collider& other) const;

	virtual void Transform(const glm::vec3& translation);

	void MoveCollider(glm::vec3 inPos);

	ColliderID GetType() const 
	{
		return type;
	}

	void SetType(ColliderID inType);

private:
	ColliderID type;
	//BoundingBox box;
	//BoundingSphere sphere;
};

class BoundingBox : public Collider
{
public:
	BoundingBox(const glm::vec3& inMinExtents, const glm::vec3& inMaxExtents) : Collider(ColliderID::BOX), minExtents(inMinExtents), maxExtents(inMaxExtents)
	{

	}

	CollisionData CollisionBoundingBox(const BoundingBox& box) const;

	glm::vec3 GetMinExtents() const
	{
		return minExtents;
	}

	glm::vec3 GetMaxExtents() const
	{
		return maxExtents;
	}

private:
	const glm::vec3 minExtents;
	const glm::vec3 maxExtents;
};

class BoundingPlane : public Collider
{
public:
	BoundingPlane(const glm::vec3& inNormal, const float& inDistance) : Collider(ColliderID::PLANE), normal(inNormal), distance(inDistance)
	{

	}

	BoundingPlane Normalized() const;

	CollisionData CollisionBoundingSphere(const BoundingSphere& sphere) const;

	glm::vec3 GetNormal() const
	{
		return normal;
	}

	float GetDistance() const
	{
		return distance;
	}
	
private:
	const glm::vec3 normal;
	const float distance;
};

class BoundingSphere : public Collider
{
public:
	BoundingSphere(const glm::vec3& inCenter, float inRadius) : Collider(ColliderID::SPHERE), center(inCenter), radius(inRadius)
	{
		
	}

	CollisionData CollisionBoundingSphere(const BoundingSphere& sphere);

	virtual void Transform(const glm::vec3& translation);

	glm::vec3 GetCenter() const
	{
		return center;
	}

	float GetRadius() const
	{
		return radius;
	}

	void SetRadius(float inRadius) {
		this->radius = inRadius;
	}

private:
	glm::vec3 center;
	float radius; 
};

