#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float TexIndex;
in vec3 mvVertexPos;
in float Face;

struct Fog 
{
	int isActive;
	vec3 colour;
	float density;
};

uniform sampler2D cubeTexture;
uniform Fog fog;

vec4 calcFog(vec3 pos, vec4 colour, Fog fog) 
{
	float distance = length(pos);
	float fogFactor = 1.0 / exp((distance * fog.density) * (distance * fog.density));
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	vec3 resultColour = mix(fog.colour, colour.xyz, fogFactor);
	return vec4(resultColour.xyz, colour.w);
}

uniform sampler2D textures[5];

void main()
{
	int texIndex = int(round(TexIndex));
	FragColor = texture(textures[texIndex], TexCoord);

	if(fog.isActive == 1) 
	{
		FragColor = calcFog(mvVertexPos, FragColor, fog);
	}
}