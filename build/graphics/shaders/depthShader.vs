#version 330 core

layout(location = 0) in vec3 vPos;

uniform mat4 lightMat;
uniform mat4 modelMat;

void main()
{
	gl_Position = lightMat * modelMat * vec4(vPos, 1.0f);
	// gl_Position = lightMat * vec4(vPos, 1.0f);
}
