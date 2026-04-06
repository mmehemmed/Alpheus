#version 460 core

out vec4 FragColor;

in vec2 texture_coords_out;
in vec3 normals_out;
in vec3 frag_pos_out;

uniform sampler2D texture_sampler;

uniform vec3 light_position;
uniform vec3 light_color;



void main()
{
	vec3 light_dir = normalize(light_position - frag_pos_out);
	vec3 normal = normalize(normals_out);

	float diff = max(dot(normal, light_dir), 0.1);
	vec3 diffuse = diff * light_color;

	
	vec3 ambient = light_color * 0.3f; //Apply ambient light
	vec3 result = (ambient + diffuse) * texture(texture_sampler, texture_coords_out).rgb; //Apply lighting to texture color

	FragColor = vec4(result, 1.0f);

}
