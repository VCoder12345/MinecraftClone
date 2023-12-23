#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in mat4 instanceModel;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * instanceModel * vec4(pos.xy, 0.0, 1.0);
}