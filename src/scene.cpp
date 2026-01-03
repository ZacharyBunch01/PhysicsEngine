#include "scene.hpp"
#include "window/window.hpp"
#include "math/matrices.hpp"

#include <algorithm>

extern Window window;
extern unsigned int shaderID, depthShaderID;

void Scene::AddObject(std::unique_ptr<Object> object)
{
	if (!object) return;

	mObjects.push_back(std::move(object));
}

void Scene::RemoveObject(Object* object)
{
	if (!object)
		return;

	auto itr = std::find_if(mObjects.begin(), mObjects.end(),
        [object](const std::unique_ptr<Object>& ptr) { return ptr.get() == object; });

	if (itr == mObjects.end()) return;
	
	(*itr)->destroy();
	mObjects.erase(itr);
}

int Scene::GetNumOfObjects() const
{
	return static_cast<int>(mObjects.size());
}

Object* Scene::GetObject(int index)
{
	if (index < 0 || index >= static_cast<int>(mObjects.size())) return nullptr;
	return mObjects.at(index).get();
}

void Scene::AddLight(std::unique_ptr<Light> light)
{
	if (light == nullptr) return;

	mLights.push_back(std::move(light));
}

void Scene::RemoveLight(Light* light)
{
	if (!light) return;

	auto itr = std::find_if(mLights.begin(), mLights.end(), 
	[light](const std::unique_ptr<Light>& ptr) { return ptr.get() == light; });

	if (itr == mLights.end()) return;

	mLights.erase(itr);
}

void Scene::RenderShadows()
{
	for (auto& lightPtr : mLights)
	{
		Light* light = lightPtr.get();

		// light->render(); // Applies uniform variables to the shader.

		// Render framebuffer texture
		glUseProgram(depthShaderID);
		glViewport(0, 0, light->getShadowWidth(), light->getShadowHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, light->getDepthMapBuffer());
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);

		for (auto& objectPtr : mObjects)
			objectPtr->render();
	}

	glUseProgram(shaderID);

	// Reset framebuffer, viewport, and screen.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, int(window.getWidth()), int(window.getHeight()));
	glUseProgram(shaderID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
}

void Scene::RenderScene()
{
	for (auto& lightPtr : mLights)
	{
		Light* light = lightPtr.get();

		light->render();

		// RenderShadows();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, light->getDepthMap());
	} 

		RenderShadows();

		for (auto& objectPtr : mObjects)
			objectPtr->render();

//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::Update(float dt)
{
	for (auto& objectPtr : mObjects)
	{
		if (objectPtr ->affectedByGravity)
			objectPtr->ApplyGravity(dt, gravity);
	}
}
 
void Scene::Unload()
{
	while (!mObjects.empty()) { 
		mObjects.back()->destroy();
		mObjects.pop_back();
	}

	while (!mLights.empty())
		mLights.pop_back();
}
