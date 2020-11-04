#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D U_Texture;
uniform sampler2D U_Texture2;
varying vec4 V_color;
varying vec2 V_Texcoord;
void main()
{
	// µþ¼ÓÎÆÀí
	gl_FragColor=V_color * texture2D(U_Texture, V_Texcoord) * texture2D(U_Texture2, V_Texcoord);
}