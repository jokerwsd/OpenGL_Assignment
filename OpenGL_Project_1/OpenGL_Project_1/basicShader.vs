#version 120

attribute vec3 position;
attribute vec2 texCoordIn;
attribute vec3 normalIn;

varying vec2 texCoord;
varying vec3 normal;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	texCoord = texCoordIn;
	normal = (transform * vec4(normalIn, 0.0)).xyz;
}