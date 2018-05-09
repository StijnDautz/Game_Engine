#version 330

in vec2 pos;

void main(){
	gl_Position.xy = pos * 0.5f;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
}