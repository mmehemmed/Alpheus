#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coords;
layout (location = 2) in vec3 normals;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;


out vec2 texture_coords_out;
out vec3 normals_out;
out vec3 frag_pos_out;

void main()
{
	frag_pos_out = vec3(model * vec4(position, 1.0));
	normals_out = mat3(transpose(inverse(model))) * normals; //Transform normals to world space

	gl_Position = projection * view * model * vec4(position, 1.0);
	texture_coords_out = texture_coords;
}