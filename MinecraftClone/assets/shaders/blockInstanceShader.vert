#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 instanceModel;

out vec2 TexCoord;
out vec3 mvVertexPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 mvPos = view * instanceModel * vec4(aPos, 1.0f);
	gl_Position = projection * mvPos;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	mvVertexPos = mvPos.xyz;
}