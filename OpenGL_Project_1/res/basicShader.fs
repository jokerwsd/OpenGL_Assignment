#version 120

varying vec2 texCoord;
varying vec3 normal;

uniform sampler2D diffuse;

void main() {
    gl_FragColor = texture2D(diffuse, texCoord) * clamp(dot(-vec3(0,0,1), normal), 0.0, 1.0);
}﻿