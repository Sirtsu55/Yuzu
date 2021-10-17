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
	vec4 PositionRadius;
	
	float SpecularIntensity;
	float Power;


};

struct Material
{
	vec4 Color;
	vec3 Diffuse;
	vec3 Ambient;
	vec3 Specular;
	float Shine;

};


layout (std430, binding = 0) buffer LightBuffer
{
	Light _WorldLights[];
};



uniform unsigned int NumberOfLights;
uniform vec3 CameraPos;
uniform Material Mat;


in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;



vec3 CalcLight(int LightIndex)
{
	Light light = _WorldLights[LightIndex];


	vec3 viewDir = normalize(CameraPos - FragPos);


    vec3 lightDir = normalize(light.PositionRadius.xyz - FragPos);

    // diffuse shading
    float diff = max(dot(Normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // attenuation
    float dist    = length(light.PositionRadius.xyz - FragPos);
    float attenuation = 1.0 / (dist * dist);    

    // combine results
    vec3 ambient  = light.ColorAmbience.w  * light.ColorAmbience.xyz;
    vec3 diffuse  = light.ColorAmbience.xyz  * diff;

    vec3 specular =  vec3(light.SpecularIntensity) * spec;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.Power;

}

//DO NOT TOUCH
void main()
{

	
	vec3 result;

	for(int i = 0; i < NumberOfLights; i++)
	{
		result += CalcLight(i);
	}

	result *= Mat.Color.xyz;

	FragColor = vec4(result, Mat.Color.w);
}

