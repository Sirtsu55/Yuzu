!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texcoord;

out vec2 TexCoord;
uniform mat4 MVPMatrix;

void main()
{
	gl_Position = MVPMatrix * vec4(pos, 1.0f); 
	TexCoord = texcoord;
}


!Fragment!
#version 450 core

in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D Image0;


void main()
{
	FragColor = texture(Image0, TexCoord);
}
