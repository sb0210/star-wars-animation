#version 330

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;
in vec2 vTex;

out vec3 normal;
out vec4 eye;
out vec4 COLOR;
out vec2 tex;
out vec4 spotlight_point_Dir;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform float b;
void main (void) 

{

  vec4 spotlightPos = vec4(0.0, 30.0, 0.0, 1.0);
  spotlight_point_Dir = spotlightPos - vPosition;

  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = - ( gl_Position); 
  COLOR = vColor;
  tex=vTex; 

 }



