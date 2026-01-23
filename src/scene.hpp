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

constexpr static glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);

class Scene
{
private:
	// Using smart pointers for safety 
	std::vector <std::unique_ptr<Object>> mObjects;
	std::vector <std::unique_ptr<Light>> mLights;

public:
	void AddObject(std::unique_ptr<Object> object);
	void RemoveObject(Object* object);

	int GetNumOfObjects() const;

	Object* GetObject(int index);

	void AddLight(std::unique_ptr<Light> light);
	void RemoveLight(Light* light);
	
	void RenderScene();
	void RenderShadows();

	void Update(float dt);

	void Unload();
};

