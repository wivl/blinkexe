#version 330 core

layout (location=0) in vec3 aPosition;
layout (location=1) in vec2 aTexcoord;
layout (location=2) in vec3 aNormal;

out vec4 position;
out vec2 texcoord;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    position =  projection * view * model * vec4(aPosition, 1.0);
    texcoord = aTexcoord;
    normal = (model * vec4(aNormal, 0.0)).xyz;

    gl_Position = position;
}