attribute vec4 position;
attribute vec4 color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

varying vec4 V_color;
void main()
{
	V_color = color;
	gl_Position=ProjectionMatrix*ViewMatrix*ModelMatrix*position;
}