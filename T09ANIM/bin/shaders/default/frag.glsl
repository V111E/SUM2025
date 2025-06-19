#version 460
out vec4 OutColor;
 
in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;


uniform vec3 CamLoc;
uniform vec3 Ka, Kd, Ks;
uniform float Ph, Trans;

uniform bool IsTexture0;
layout(binding = 0) uniform sampler2D Tex0;

uniform float Time;
uniform int AddonI0, AddonI1;

vec3 Shade( vec3 P, vec3 N )
{
  vec3 LPos = vec3(8, 8, 8);
  vec3 L = normalize(vec3(1, 1, 1)); // normalize(LPos - P);
  vec3 LC = vec3(1, 1, 1); // light color

  vec3 V = normalize(P - CamLoc);

  N = faceforward(N, V, N);

  vec3 color = vec3(0);

  // Ambient
  color += Ka;

  // Diffuse
  vec3 Diff = Kd;
  if (IsTexture0)
  {
    vec4 tc = texture(Tex0, DrawTexCoord);
    Diff *= tc.rgb;
  }
  color += LC * Diff * max(0, dot(N, L));

  // Specular
  vec3 R = reflect(V, N);
  color += LC * Ks * pow(max(0, dot(R, L)), Ph);

  return color;
}
 
void main( void )
{
  //if (AddonI0 <= abs(sin(Time * 0.p1)) * AddonI1)
    //discard;
  OutColor = vec4(Shade(DrawPos, normalize(DrawNormal)), Trans); 
}
