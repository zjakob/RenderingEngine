#version 420 core

in vec4 position;

out VS_OUT
{
	vec4 color;
} vs_out;

uniform mat4 mvp;

void main(void)
{
	gl_Position = mvp * position;
	vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}
