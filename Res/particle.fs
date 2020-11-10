#version 120
#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D U_Texture;
varying vec4 V_Color;
void main()
{
	vec4 color = texture2D(U_Texture,gl_PointCoord.xy)*V_Color;
	gl_FragData[0] = color;
	gl_FragData[1] = color;
}