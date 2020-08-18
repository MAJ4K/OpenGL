#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_normal;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
   vec4 texColor = texture(u_texture, v_TexCoord);
   color = texColor * clamp(dot(-vec3(0,0,1.5),v_normal),0.4,2.0);
   color = vec4((color).xyz,1.0);
}