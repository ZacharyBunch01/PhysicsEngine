cmake_minimum_required(VERSION 3.15)
project(PhysicsEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS OpenGL deprecation spam
add_definitions(-DGL_SILENCE_DEPRECATION)

# Tell ImGui OpenGL3 backend to use GLEW as the loader
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)

# GLM experimental extensions
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# -------------------------
# Include directories
# -------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/graphics
    ${CMAKE_SOURCE_DIR}/src/math
    ${CMAKE_SOURCE_DIR}/src/math/physics
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/window

    ${CMAKE_SOURCE_DIR}/imgui

    # GLEW, GLFW, GLM (note GLM is under OpenGL-Root/include/GLM)
    ${CMAKE_SOURCE_DIR}/OpenGL-Root/include
    ${CMAKE_SOURCE_DIR}/OpenGL-Root/include/GLM
)

# -------------------------
# Source files
# -------------------------

# All your engine/game code
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# ImGui sources – explicitly list the ones we want (no Win32 backend)
set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_stdlib.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_impl_opengl3.cpp
)

add_executable(PhysicsEngine
    ${ENGINE_SOURCES}
    ${IMGUI_SOURCES}
)

# -------------------------
# Link libraries
# -------------------------

target_link_libraries(PhysicsEngine
    /opt/homebrew/opt/glew/lib/libGLEW.dylib
    /opt/homebrew/opt/glfw/lib/libglfw.3.dylib
)

# macOS frameworks needed for OpenGL + windowing
target_link_libraries(PhysicsEngine
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

target_include_directories(PhysicsEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/OpenGL-Root/include
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_definitions(PhysicsEngine PRIVATE
    GLFW_INCLUDE_NONE
    IMGUI_IMPL_OPENGL_LOADER_GLEW
    GL_SILENCE_DEPRECATION
)

set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/graphics/shaders)
set(SHADER_DST_DIR ${CMAKE_BINARY_DIR}/graphics/shaders)

add_custom_command(TARGET PhysicsEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_DST_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_SRC_DIR} ${SHADER_DST_DIR}
)



