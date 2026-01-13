//Project Files
#include "src/window/window.hpp"
#include "src/util/shaderLoader.hpp"
#include "src/scene.hpp"
#include "src/window/controls.hpp"
#include "src/player.hpp"
#include "src/graphics/gui.hpp"

Window window(800, 600, "Physics Engine");
  
Player player;

glm::mat4 projectionMat;
glm::mat4 viewMat;
glm::mat4 modelMat;

unsigned int shaderID;
unsigned int depthShaderID;

extern float deltaTime;

Scene scene;

Object cube("res/cube.obj", BOX);

Object floorObject("res/cube.obj", BOX);

Light light(glm::vec3(3.0f, 10.0f, 4.0f), glm::vec3(1.0f, 10.0f, 1.0f), 0.05f, glm::vec3(0.0f, 0.0f, 0.0f));
Light light2(glm::vec3(-5.0f, 10.0f, -5.0f), glm::vec3(0.2f, 0.75f, 0.2f), 1.0f, glm::vec3(0.0f));

int main()
{   
    shaderID = LoadShader("shaders/vertexShader.vs", "shaders/fragmentShader.frag");
    depthShaderID = LoadShader("shaders/depthShader.vs", "shaders/depthShader.frag");

    if(window.getWindow() == NULL)
    {
        std::cout << "Window failed to initialize" << std::endl;
        return -1;
    }

    GUI::Init();

    glClearColor(0.15f, 0.2f, 0.3f, 1.0f);

    cube.Position.y = 20.0f;
    cube.affectedByGravity = true;
    cube.rigidBody.InitRigidBody(cube.Position, cube.Velocity);

    floorObject.Position.y = 1.0f;
    floorObject.Scale.y *= 0.5f;
    floorObject.Scale.x *= 10.0f;
    floorObject.Scale.z *= 10.0f;
    floorObject.rigidBody.InitRigidBody(floorObject.Position, floorObject.Velocity);
    floorObject.affectedByGravity = false;

    scene.AddObject(&cube);
    scene.AddObject(&floorObject);
    scene.AddLight(&light);
    //scene.RemoveLight(&light);
    //scene.AddLight(&light2);

    cube.rigidBody.collider = BOX_COLLIDER;
    floorObject.rigidBody.collider = BOX_COLLIDER;

    while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window.getWindow()) == 0 )
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);

        ComputeControls();

        scene.Update(deltaTime);

        glm::mat4 MVPmat = projectionMat * viewMat;

        unsigned int MVPID = glGetUniformLocation(shaderID, "MVP");
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVPmat[0][0]);

        scene.RenderScene();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    scene.Unload();
    GUI::Destroy();

    glDeleteProgram(shaderID);
    glDeleteProgram(depthShaderID);

    glfwDestroyWindow(window.getWindow());
    glfwTerminate();
    
    return 0;
}
