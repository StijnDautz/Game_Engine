#version 330
uniform sampler2D tex; // texture uniform
in vec2 ftexcoord;
out vec4 FragColor;
void main() {
	FragColor = texture(tex, vec2(ftexcoord.x, 1.0f -ftexcoord.y));
}