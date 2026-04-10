#version 460 core

out vec4 FragColor;

in vec2 texture_coords_out;
in vec3 normals_out;
in vec3 frag_pos_out;

uniform sampler2D texture_sampler;

uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 view_position;



void main()
{
	float fog_maxdist = 80.0;
	float fog_mindist = 10.0;
	vec4  fog_colour = vec4(0.4, 0.4, 0.4, 1.0);
	
	float dist = length(view_position - frag_pos_out);
	float fog_factor = (fog_maxdist - dist) / (fog_maxdist - fog_mindist);
	fog_factor = clamp(fog_factor, 0.0, 1.0);


	vec3 light_dir = normalize(light_position - frag_pos_out);
	vec3 normal = normalize(normals_out);

	float diff = max(dot(normal, light_dir), 0.1);
	vec3 diffuse = diff * light_color;

	
	vec3 ambient = light_color * 0.3f; //Apply ambient light
	vec3 result = (ambient + diffuse) * texture(texture_sampler, texture_coords_out).rgb; //Apply lighting to texture color

	vec3 final_color = mix(fog_colour.rgb, result, fog_factor); //Apply fog effect
	FragColor = vec4(final_color, 1.0f);
}
