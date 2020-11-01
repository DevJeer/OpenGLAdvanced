#include "scene.h"
#include "ggl.h"
#include "utils.h"

GLuint vbo;
GLuint program;

GLuint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
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

	// 加载Shader为绘图做准备
	int fileSize = 0;
	unsigned char *shaderCode = LoadFileContent("Res/test.vs", fileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
	delete shaderCode; // 不使用之后就删掉

	shaderCode = LoadFileContent("Res/test.fs", fileSize);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
	delete shaderCode;

	program = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);	// 删除shader，因为已经链接到program里面了
	glDeleteShader(fsShader);

	// 获取shader中的插槽位置
	positionLocation = glGetAttribLocation(program, "position");
	modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");

}

void Draw()
{

}

void SetViewPortSize(float width, float height)
{

}