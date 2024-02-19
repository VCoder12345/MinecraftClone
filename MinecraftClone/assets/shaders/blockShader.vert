#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float texIndex;
layout (location = 3) in float intensity;

out vec2 TexCoord;
out float TexIndex;
out vec3 mvVertexPos;
out float Intensity;

uniform vec3 offset;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 mvPos = view * vec4(aPos + offset, 1.0f);
	gl_Position = projection * mvPos;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	TexIndex = texIndex;
	mvVertexPos = mvPos.xyz;
	Intensity = intensity;
}