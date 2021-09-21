!Vertex!
#version 450 core

layout (location = 0) in vec3 pos;

uniform mat4 MVPMatrix;


//DO NOT TOUCH
void main()
{
	gl_Position = MVPMatrix * {0}(); 
}

//Implement Shader Here
vec4 {0}()
{
	vec4 Color = iColor;
	return Color;
}
!Fragment!
#version 450 core


out vec4 FragColor;
uniform vec4 iColor;

//DO NOT TOUCH
void main()
{
	FragColor = {0}();
}

//Implement Shader Here
vec4 {0}()
{
	vec4 Color = iColor;
	return Color;
}