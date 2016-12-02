#version 120

attribute vec3 position;
attribute vec2 texCoordIn;

varying vec2 texCoord;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	texCoord = texCoordIn;
}