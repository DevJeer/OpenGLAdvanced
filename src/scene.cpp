#include "scene.h"
#include "ggl.h"

GLuint vbo;
void Init()
{
	float data[] = {
		-0.2f, -0.2f, -0.6f, 1.0f,
		0.2f, -0.2f, -0.6f, 1.0f,
		0.0f, 0.2f, -0.6f, 1.0f
	};
	glGenBuffers(1, &vbo);
	// 设置当前的gl_array_buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Draw()
{

}

void SetViewPortSize(float width, float height)
{

}