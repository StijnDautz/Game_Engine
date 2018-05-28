#version 330
uniform sampler2D tex;
in vec2 ftexcoord;
layout(location = 0) out vec4 FragColor;
void main() {
	FragColor = texture(tex, vec2(ftexcoord.x, 1.0f - ftexcoord.y));
}