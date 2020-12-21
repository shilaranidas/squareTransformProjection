#version 430 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

void main()
{
	gl_Position = vec4(vertex_position, 1.0);
	colour = vertex_colour;
}