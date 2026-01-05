// GLEW
#include <GL/glew.h>
#define GLEW_STATIC

// GLM
#include <GLM/glm/glm.hpp>

// Pragma
#pragma once

// My light class.
class Light
{
public:
	Light(glm::vec3 Position = glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3 colorIn = glm::vec3(1.0f), int strengthIn = 1, glm::vec3 directionIn = glm::vec3(0.0f, -10.0f, 0.0f));

	void render();

	unsigned int getDepthMapBuffer() const;
	unsigned int getDepthMap() const;

	unsigned int getShadowWidth() const;
	unsigned int getShadowHeight() const;

	float getNearPlane();
	float getFarPlane();

private:
	glm::vec3 Position;
	glm::vec3 color;
	float strength;
	glm::vec3 direction;

	unsigned int depthMapBuffer;
	unsigned int depthMap;

	const unsigned int sWidth = 1024, sHeight = 1024; // Shadow texture resolution.

	float nearPlane = 0.1f, farPlane = 200.0f; // Min and max view of the shadow depth buffer.

	glm::mat4 lightMat;

	void setUniforms();
};

