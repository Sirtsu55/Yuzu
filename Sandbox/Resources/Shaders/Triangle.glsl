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
	vec4 ColorAndRadius;
	vec4 PositionAndIntensity;
};
layout (std430, binding = 0) buffer LightBuffer
{
	Light _WorldLights[];
};


out vec4 FragColor;
uniform vec4 iColor;

in vec3 Normal;
in vec3 FragPos;





//Implement Shader Here
vec4 Colorer()
{
	
	return vec4(iColor);
}

//DO NOT TOUCH
void main()
{
	vec4 ImplColor = Colorer();
	FragColor = ImplColor;
}

