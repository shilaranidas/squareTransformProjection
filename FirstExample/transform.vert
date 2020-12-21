#version 430 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

// Values that stay constant for the whole mesh.
uniform mat4 model;

void main()
{
	gl_Position = model * vec4(vertex_position, 1.0);
	colour = vertex_colour;
}