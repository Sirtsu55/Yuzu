!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 MVPMatrix;

out vec3 Normal;
out vec3 VertPos;

vec4 Colorer()
{
	vec3 VertPos = pos;
	vec3 Normal = vec3(1.0f);

	return vec4(VertPos, 1.0f);
}

//DO NOT TOUCH
void main()
{
	gl_Position = MVPMatrix * Colorer(); 
}

//Implement Shader Here
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
in vec3 VertPos;


//Implement Shader Here
vec4 Colorer()
{
	
	return vec4(iColor);
}

//DO NOT TOUCH
void main()
{
	FragColor = Colorer();
}

