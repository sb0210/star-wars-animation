#version 330

in vec4 vPosition;
in vec4 vColor;
out vec4 color;
uniform mat4 uRotationMatrix;

void main (void) 
{
  gl_Position = uRotationMatrix * vPosition;
  color = vColor;
}
