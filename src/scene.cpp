#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"
#include "shader.h"
#include "model.h"

GLuint vbo, ebo;
GLuint program;


glm::mat4 modelMatrix, viewMatrix, projectionMatrix;


Shader* shader;
VertexBuffer* vertexbuffer;

// ����
Ground ground;
// ģ��
Model model;
void InitTriangle()
{
	// ʹ��Vertexbuffer������
	vertexbuffer = new VertexBuffer;
	vertexbuffer->SetSize(3);
	vertexbuffer->SetPosition(0, -0.2f, -0.2f, 0.0f);
	vertexbuffer->SetTexcrood(0, 0.0f, 0.0f);
	vertexbuffer->SetColor(0, 1.0f, 1.0f, 1.0f);

	vertexbuffer->SetPosition(1, 0.2f, -0.2f, 0.0f);
	vertexbuffer->SetTexcrood(1, 1.0f, 0.0f);
	vertexbuffer->SetColor(1, 1.0f, 0.0f, 0.0f);

	vertexbuffer->SetPosition(2, 0.0f, 0.2f, 0.0f);
	vertexbuffer->SetTexcrood(2, 0.5f, 1.0f);
	vertexbuffer->SetColor(2, 0.0f, 1.0f, 0.0f);

	shader = new Shader;
	shader->Init("Res/test.vs", "Res/test.fs");
	// ʹ���������
	shader->SetTexture("U_Texture", "Res/test.bmp");
	shader->SetTexture("U_Texture", "Res/test2.bmp");
	modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);
}

void DrawTriangle()
{
	// ��vbo
	vertexbuffer->Bind();
	// ��shader
	shader->Bind(glm::value_ptr(modelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));

	glDrawArrays(GL_TRIANGLES, 0, 3);
	vertexbuffer->Unbind();
}

void Init()
{
	ground.Init();
	model.Init("Res/Sphere.obj");
	model.SetTexture("Res/earth.bmp");
	model.SetPosition(0.0f, 0.0f, -5.0f);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ���Ƶ���
	ground.Draw(viewMatrix, projectionMatrix);
	// ����ģ��
	model.Draw(viewMatrix, projectionMatrix);
}
