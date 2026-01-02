
//std
#include <vector>
#include <memory>

//GLM
#include <GLM/glm/glm.hpp>

//Project files
#include "object.hpp"
#include "light.hpp"

//Pragma
#pragma once

class Scene
{
private:
	std::vector <Object*> mObjects;
	std::vector <Light*> mLights;

public:
	void AddObject(std::shared_ptr<Object> object);
	void RemoveObject(std::shared_ptr<Object> object);

	int GetNumOfObjects();

	Object std::unique_ptr<Object>GetObject(int index);

	void AddLight(std::shared_ptr<Light> light);
	void RemoveLight(std::shared_ptr<Light> light);

	void RenderScene();
	void RenderShadows();

	void Update(float dt);

	void Unload();

	glm::vec3 gravity = glm::vec3(0.0f, -1.0f, 0.0f);
};

