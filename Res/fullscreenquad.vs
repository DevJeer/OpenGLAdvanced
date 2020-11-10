#ifdef GL_ES
precision mediump float;
#endif
attribute vec4 position;
attribute vec4 texcoord;
varying vec4 V_Texcoord;
void main()
{
	V_Texcoord=texcoord;
	// 不进行MVP变换
	gl_Position=position;
}