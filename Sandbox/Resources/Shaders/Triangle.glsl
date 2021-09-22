!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;

uniform mat4 MVPMatrix;

vec4 Colorer()
{
	vec3 VertPos = pos;
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

out vec4 FragColor;
uniform vec4 iColor;
layout (std430, binding = 0) buffer LightBuffer
{
	Light _WorldLights[];
};

//Implement Shader Here
vec4 Colorer()
{
	vec3 Color = vec3(_WorldLights[2].ColorAndRadius.rgb);
	return vec4(Color, 1.0f);
}


//DO NOT TOUCH
void main()
{
	FragColor = Colorer();
}

