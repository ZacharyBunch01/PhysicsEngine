#version 330 core

in vec2 textureCoords;

out vec4 color;
in vec3 lightCol;
in vec3 normal;
in vec3 fragPos;
in vec3 lightDir;
in float lightStr;
in vec3 lightPosition;
in vec4 fragPosLight;
in vec3 viewPos;
    
uniform sampler2D shadowMap;

uniform vec3 direction;

void main()
{
	vec3 objectColor = vec3(1.0f, 0.0f, 0.0f);
	vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);
	ambientColor *= lightCol;

	vec3 norm = normalize(normal);

	vec3 lightDir = normalize(lightPosition - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightCol;

	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = 0.0f; 
	vec3 halfwayDir = normalize(lightDir + direction);
	spec = pow(max(dot(norm, halfwayDir), 0.0f), 32.0f);
	vec3 specular = spec * lightCol * lightStr * 0.5f;

	vec3 projectionCoords = fragPosLight.xyz / fragPosLight.w;
	projectionCoords = projectionCoords * 0.5f + 0.5f;
	
	float closestDepth = texture(shadowMap, projectionCoords.xy).r;
	float currentDepth = projectionCoords.z;

	float bias = max(0.05f * (1.0f - dot(norm, lightDir)), 0.005f);

	float shadow = 0.0f;

	vec2 texelSize = 1.0f / textureSize(shadowMap, 0);

	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projectionCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;
		}
	}

	shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;

	shadow /= 9.0f;

	if(projectionCoords.z > 1.0f)
		shadow = 0.0f;

	vec3 result = (ambientColor + (1.0 - shadow) * (diffuse + specular)) * objectColor;

	color = vec4(result, 1.0f);
}