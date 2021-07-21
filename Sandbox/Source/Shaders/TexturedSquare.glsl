!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 vertcolor;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in float texid;

out vec2 TexCoord;
out vec4 VertCol;
out float TexID;

uniform mat4 MVPMatrix;



void main()
{
	gl_Position = MVPMatrix * vec4(pos, 1.0f); 
	TexCoord = texcoord;
	VertCol = vertcolor;
	TexID = texid;
}









!Fragment!
#version 450 core

in vec2 TexCoord;
in vec4 VertCol;
in float TexID;
out vec4 FragColor;

uniform sampler2D Textures[32];


void main()
{
	int TexID = int(TexID);
	FragColor = texture(Textures[TexID], TexCoord);

}
