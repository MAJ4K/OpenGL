#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_normal;

uniform vec4 u_color;

void main()
{
   color = u_color * clamp(dot(-vec3(0,0,1.5),v_normal),0.4,2.0);
}