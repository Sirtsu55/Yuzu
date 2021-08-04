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


out vec4 FragColor;
uniform vec4 iColor;



void main()
{
	FragColor = iColor;
}
