#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"

GLuint vbo, ebo;
GLuint program;

GLuint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, colorLocation;
// �������������Ĳ��
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
	// ���õ�ǰ��gl_array_buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ʹ����������
	unsigned short indexes[] = { 0, 1, 2 };
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ����ShaderΪ��ͼ��׼��
	int fileSize = 0;
	unsigned char *shaderCode = LoadFileContent("Res/test.vs", fileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
	delete shaderCode; // ��ʹ��֮���ɾ��

	shaderCode = LoadFileContent("Res/test.fs", fileSize);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
	delete shaderCode;

	program = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);	// ɾ��shader����Ϊ�Ѿ����ӵ�program������
	glDeleteShader(fsShader);

	// ��ȡshader�еĲ��λ��
	positionLocation = glGetAttribLocation(program, "position");
	colorLocation = glGetAttribLocation(program, "color");
	texcoordLocation = glGetAttribLocation(program, "texcoord");
	modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
	// ��ȡ����Ĳ��
	textureLocation = glGetUniformLocation(program, "U_Texture");


	modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);
	// �����������
	texture = CreateTexture2DFromBMP("Res/test.bmp");

	ground.Init();
}

// �����ӿڵĴ�С
void SetViewPortSize(float width, float height)
{
	// ����ͶӰ����
	projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void Draw()
{
	// ��ȡÿ֡��ʱ��
	float frameTime = GetFrameTime();
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ground.Draw(viewMatrix, projectionMatrix);
	// ����MVP�����ֵ
	glUseProgram(program);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// ���õ�ǰҪ�������������
	glBindTexture(GL_TEXTURE_2D, texture);
	// �������������Դ���Ķ�
	glUniform1i(textureLocation, 0);

	// ��ǰ����Ļ��Ƽ�
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// �����ĸ����
	glEnableVertexAttribArray(positionLocation);
	// ����۵�ֵ ��һ��position���ڵ�λ������һ��position����λ�õļ��
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	// �����gpu�е�core
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));

	glEnableVertexAttribArray(texcoordLocation);
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 8));
	

	// ������������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
