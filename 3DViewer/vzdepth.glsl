#version 400

layout (location = 0) in vec4 vPosition;
out vec4 v2fcolor;
uniform mat4 model;


void main(){
    gl_Position = model * vPosition;
    float gray = (gl_Position.z + 1) * 0.5;//por que esta conta?
    v2fcolor = vec4 (gray, gray, gray, 1);
}
