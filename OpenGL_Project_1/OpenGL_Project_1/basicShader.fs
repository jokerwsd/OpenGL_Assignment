#version 120

in vec2 texCoord;
uniform sampler2D diffuse;

void main() {
    gl_FragColor = texture2D(diffuse, texCoord);
}﻿