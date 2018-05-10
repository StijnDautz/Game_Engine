#version 330

in vec4 pos;
in vec4 vertexColor;

out vec4 fragmentColor;

void main(){
	gl_Position = pos;

	fragmentColor = vertexColor;
}