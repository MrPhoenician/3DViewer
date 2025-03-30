#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
out float lineCoord;
uniform mat4 transform;
uniform float pointSize;
uniform mat4 projection;

void main() {
  gl_PointSize = pointSize;
  gl_Position = projection * transform * vec4(aPos, 1.0f);
  lineCoord = gl_Position.z;  // for stipple line
}