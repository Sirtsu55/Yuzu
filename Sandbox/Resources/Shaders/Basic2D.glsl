!Vertex!
#version 450 core



layout (location = 0) in vec3 pos;


uniform mat4 MVPMatrix;

void main()
{

	gl_Position = MVPMatrix * vec4(pos, 1.0f); 
}


!Fragment!
#version 450 core


struct Light
{
	vec3 Color;
	vec3 Position;
	float Intensity;
};

out vec4 FragColor;
uniform vec4 iColor;
layout (binding = 0) buffer LightBuffer
{
	Light _WorldLights;
};

void main()
{
	FragColor = iColor;
}
