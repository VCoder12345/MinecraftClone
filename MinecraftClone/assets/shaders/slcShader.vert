#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 offset;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(aPos + offset, 1.0f);
}