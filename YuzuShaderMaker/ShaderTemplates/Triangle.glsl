!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;


void main()
{

	gl_Position = vec4(pos, 1.0f); 
}


!Fragment!
#version 450 core


out vec4 FragColor;




void main()
{
	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
