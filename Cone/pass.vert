#version 150
uniform mat4 transform;

in vec4 vPosition;
//in vec4 vColor;
out vec4 passedColor;

void main() {
	gl_Position = transform * vPosition/vPosition.w;
	passedColor = vec4(1.0, 1.0, 1.0, 1.0);
}