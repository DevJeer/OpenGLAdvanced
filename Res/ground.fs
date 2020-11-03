#ifdef GL_ES
precision mediump float;
#endif
//uniform vec4 U_LightPos;
//uniform vec4 U_LightAmbient;
//uniform vec4 U_LightDiffuse;
//uniform vec4 U_AmbientMaterial;
//uniform vec4 U_DiffuseMaterial;
varying vec4 V_Color;
//varying vec3 V_Normal;
//varying vec3 V_WorldPos;
void main()
{
	//vec4 color=vec4(0.0,0.0,0.0,0.0);
	//float distance=0.0;
	//float constantFactor=1.0;
	//float linearFactor=0.0;
	//float quadricFactor=0.0;
	//vec4 ambientColor=U_LightAmbient*U_AmbientMaterial;
	//vec3 L=U_LightPos.xyz-V_WorldPos;
	//distance=length(L);
	//float attenuation=1.0/(constantFactor+linearFactor*distance+quadricFactor*quadricFactor*distance);
	//L=normalize(L);
	//vec3 n=normalize(V_Normal);
	//float diffuseIntensity=max(0.0,dot(L,n));
	//vec4 diffuseColor=U_LightDiffuse*U_DiffuseMaterial*diffuseIntensity*attenuation*4.0;
	//color=ambientColor+diffuseColor;
	//gl_FragColor=color*V_Color;

	gl_FragColor=V_Color;
}