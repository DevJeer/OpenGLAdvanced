#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"
#include "shader.h"

GLuint vbo, ebo;
GLuint program;


glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
Ground ground;

Shader* shader;
VertexBuffer* vertexbuffer;
void Init()
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

	modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);

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
	// ���Ƶ���
	ground.Draw(viewMatrix, projectionMatrix);

	// ��vbo
	vertexbuffer->Bind();
	// ��shader
	shader->Bind(glm::value_ptr(modelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vertexbuffer->Unbind();

}
