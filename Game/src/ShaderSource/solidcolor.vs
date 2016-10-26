#version 430 core

in vec3 VertexPosition;

out VS_OUT
{
	vec4 color;
} vs_out;

uniform vec4 Color;
uniform mat4 MVP;

void main(void)
{
	gl_Position = MVP * vec4(VertexPosition,1.0);
	vs_out.color = Color;
}
