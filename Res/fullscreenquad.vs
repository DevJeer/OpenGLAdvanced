#ifdef GL_ES
precision mediump float;
#endif
attribute vec4 position;
attribute vec4 texcoord;
varying vec4 V_Texcoord;
void main()
{
	V_Texcoord=texcoord;
	// ������MVP�任
	gl_Position=position;
}