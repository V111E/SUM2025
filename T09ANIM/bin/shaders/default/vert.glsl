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
  /* 
  пер правая 451  
  зад правая 452
  пер левая 453
  зад левая 454
  440 зад лев диск 
  441 об зад лев
  444 зад пр диск
  445 зад пр об
  448 пер пр диск
  449 пер пр об

  447 пер пр шт
  444 пер пр шт


  426 пер лев шт
  427 пер лев диск
  428 пер лев об

  
  
  */

  //if (gl_Position.x < sin(Time)) 
   // DrawColor = vec4(abs(sin(Time)) * 0.2, abs(cos(Time)) * abs(sin(Time)) * 0.5, abs(tan(Time)) * abs(sin(Time)) * 0.9, 1);
   // if (gl_Position.x > sin(Time)) 
    //  DrawColor = vec4(abs(sin(Time)) * abs(sin(Time)), abs(cos(Time)) * 0.9, abs(cos(Time)) * 0.1, 1);
   // if (gl_Position.y < sin(Time) * 5)
  //    DrawColor = vec4(abs(cos(Time)) * 0.12, abs(sin(Time)) * 0.44, abs(sin(Time)) * 0.32, 1);

//abs(tan(Time)) * 0.2, abs(cos(Time)) * abs(sin(Time)) * abs(tan(Time)) , abs(tan(Time)) * abs(cos(Time)) * 0.9, 1); 
}


/*
#version 330
 
uniform mat4 MatrWVP;
 
layout(location = 0) in vec3 InPosition;
layout(location = 3) in vec4 InColor;
 
out vec4 DrawColor;
 
void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  DrawColor = InColor;
}
 */


