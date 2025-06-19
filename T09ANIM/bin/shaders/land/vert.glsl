/**/
#version 460
 
uniform mat4 MatrWVP, MatrW, MatrWInv;
 
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;
 
out vec4 DrawColor;
out vec3 DrawNormal;
out vec3 DrawPos;
out vec2 DrawTexCoord;
uniform float Time;
 
void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawColor = InColor;
  DrawNormal = mat3(MatrWInv) * InNormal;
  DrawTexCoord = InTexCoord;
}
