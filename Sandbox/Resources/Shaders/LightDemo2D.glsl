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
#version 450


in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D Image0;



uniform vec3 LightLocation;
uniform vec3 ObjectLocation;
uniform float LightIntensity;





void main()
{
	float Distance = distance(ObjectLocation,  LightLocation);


	float FinalLightIntensity = (1 / (Distance * Distance)) * LightIntensity;
	vec4 PixelColor = texture(Image0, TexCoord) * vec4(1.0f, 0.0f, 1.0f, 1.0f);

	FragColor = FinalLightIntensity * PixelColor;
}
