!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;


out vec3 Normal;
out vec3 FragPos;


vec4 Colorer()
{

	return vec4(pos, 1.0f);
}

//DO NOT TOUCH
void main()
{
	vec4 VertexPos = Colorer();

	FragPos = vec3(ModelMatrix * VertexPos);
	Normal = NormalMatrix * normal;
	gl_Position = MVPMatrix * VertexPos; 
}




!Fragment!
#version 450 core



struct Light
{
	vec4 ColorAmbience;
	vec4 PositionIntensity;
};


layout (std430, binding = 0) buffer LightBuffer
{
	Light _WorldLights[];
};


uniform vec4 iColor;

uniform unsigned int NumberOfLights;
uniform vec3 CameraPos;

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;





//Implement Shader Here
vec4 Colorer()
{
	
	return iColor;
}

vec3 CalcLight(int LightIndex)
{
	Light light = _WorldLights[LightIndex];
	const float SpecStrength = 0.5f;

	vec3 normal = normalize(Normal);
	vec3 lightdir = normalize(light.PositionIntensity.xyz - FragPos);
	vec3 viewdir = normalize(CameraPos - FragPos);
	float diff = max(dot(lightdir, normal), 0.0f);


	vec3 reflectiondir = reflect(-lightdir, normal);


	float spec = pow(max(dot(viewdir, reflectiondir), 0.0), 32);

	vec3 specular = SpecStrength * spec * light.ColorAmbience.xyz;  

	vec3 diffuse = diff * light.ColorAmbience.xyz;
	vec3 ambient = light.ColorAmbience.w * light.ColorAmbience.xyz;

	return diffuse + ambient + specular;

}

//DO NOT TOUCH
void main()
{

	vec4 ImplColor = Colorer();

	
	vec3 result;

	for(int i = 0; i < NumberOfLights; i++)
	{
		result += CalcLight(i);
	}

	result *= ImplColor.xyz;

	FragColor = vec4(result, ImplColor.w);
}

