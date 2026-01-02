#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTextureCoords;

uniform mat4 modelMat;
uniform mat4 MVP;
uniform mat4 lightMat;

out vec2 textureCoords;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform float lightStrength;

out vec3 normal;
out vec3 fragPos;
out vec3 lightDir;
out vec3 lightCol;
out float lightStr;
out vec3 lightPosition;
out vec4 fragPosLight;

void main()
{
	mat4 finalMVP = MVP * modelMat;

	fragPos = vec3(modelMat * vec4(vPos, 1.0f));

	normal = transpose(inverse(mat3(modelMat))) * vNormal;

	textureCoords = vTextureCoords;

	fragPosLight = lightMat * vec4(fragPos, 1.0f);

	gl_Position = finalMVP * vec4(fragPos, 1.0f);

	lightDir = normalize(lightPos - fragPos);

	lightCol = lightColor;

	lightStr = lightStrength;

	lightPosition = lightPos;
}
