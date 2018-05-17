#version 330
in vec4 vposition;
in vec2 vtexcoord;
out vec2 ftexcoord;
void main() {
	ftexcoord = vtexcoord;
	gl_Position = vposition;
}