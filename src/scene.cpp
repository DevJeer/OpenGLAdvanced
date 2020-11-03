#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"

GLuint vbo, ebo;
GLuint program;

GLuint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, colorLocation;
// 纹理坐标和纹理的插槽
GLuint texcoordLocation, textureLocation;
GLuint texture;

glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
Ground ground;
void Init()
{
	float data[] = {
		-0.2f, -0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.2f, -0.2f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.2f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
	};
	glGenBuffers(1, &vbo);
	// 设置当前的gl_array_buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 使用索引绘制
	unsigned short indexes[] = { 0, 1, 2 };
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	colorLocation = glGetAttribLocation(program, "color");
	texcoordLocation = glGetAttribLocation(program, "texcoord");
	modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
	// 获取纹理的插槽
	textureLocation = glGetUniformLocation(program, "U_Texture");


	modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);
	// 创建纹理对象
	texture = CreateTexture2DFromBMP("Res/test.bmp");

	ground.Init();
}

// 设置视口的大小
void SetViewPortSize(float width, float height)
{
	// 设置投影矩阵
	projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void Draw()
{
	// 获取每帧的时间
	float frameTime = GetFrameTime();
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ground.Draw(viewMatrix, projectionMatrix);
	// 设置MVP矩阵的值
	glUseProgram(program);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// 设置当前要操作的纹理对象
	glBindTexture(GL_TEXTURE_2D, texture);
	// 告诉纹理对象资源在哪儿
	glUniform1i(textureLocation, 0);

	// 当前程序的绘制集
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// 开启哪个插槽
	glEnableVertexAttribArray(positionLocation);
	// 填充插槽的值 第一个position所在的位置与下一个position所在位置的间隔
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	// 分配给gpu中的core
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));

	glEnableVertexAttribArray(texcoordLocation);
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	

	// 用索引来绘制
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
