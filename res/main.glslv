#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 color;

out vec4 a_color;

uniform mat4 model;
uniform mat4 projview;

void main(){
    a_color = vec4(color, 1.0);
    gl_Position = projview *   model * vec4(v_position, 1.0);
}