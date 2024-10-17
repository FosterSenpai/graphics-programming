#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;


uniform float time;

void main()
{
	vec4 diffuse1 = texture(texture_diffuse1, TexCoord);
	vec4 diffuse2 = texture(texture_diffuse2, TexCoord);
	vec4 diffuse3 = texture(texture_diffuse3, TexCoord);
	
	vec4 specular1 = texture(texture_specular1, TexCoord);
	vec4 specular2 = texture(texture_specular2, TexCoord);
	vec4 specular3 = texture(texture_specular3, TexCoord);
	
	vec4 diffuse_color = (diffuse1 + diffuse2 + diffuse3) / 3.0;
	vec4 specular_color = (specular1 + specular2 + specular3) / 3.0;
	
	diffuse_color = diffuse_color * 0.3; // Darken the diffuse color. Remove later
	vec4 color = diffuse_color + specular_color;
	
	FragColor = color;
}