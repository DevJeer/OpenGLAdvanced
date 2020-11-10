#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"
#include "shader.h"
#include "model.h"
#include "skybox.h"
#include "particleSystem.h"
#include "framebufferObject.h"

GLuint vbo, ebo;
GLuint program;


glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
glm::vec3 cameraPos(10.0f, 10.0f, 10.0f);

Shader* shader;
VertexBuffer* vertexbuffer;

// ����
Ground ground;
// ģ��
Model model, niutou, sphere;
// ��պ�
SkyBox skybox;
// ����ϵͳ
ParticleSystem ps;

// frame buffer object
FrameBufferObject* fbo;

VertexBuffer* fsqVertex;
Shader* fsqShader;
glm::mat4 fsqViewMatrix;

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
	viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ground.Init();
	model.Init("Res/Sphere.obj");
	model.SetTexture("Res/earth.bmp");
	model.SetPosition(0.0f, 0.0f, 0.0f);
	skybox.Init("Res/");

	niutou.Init("Res/niutou.obj");
	niutou.SetTexture("Res/niutou.bmp");
	niutou.mModelMatrix = glm::translate(-0.5f, 0.0f, 4.0f) * glm::scale(0.05f, 0.05f, 0.05f);

	// ����ϵͳ��ʼ��
	ps.Init(0.0f, 0.0f, 0.0f);
}

void CPUQuad(float width, float height)
{
	// �����ı���
	// ������������z��-0.2�������׶����ı���
	float aspect = width / height;
	float halfFOV = 60.0f / 2.0f;
	float randianHalfFOV = 3.14f * halfFOV / 180.0f;
	float tanHalfFOV = sinf(randianHalfFOV) / cosf(randianHalfFOV);
	float y = tanHalfFOV * 0.2f;
	float x = y * aspect;
	fsqVertex = new VertexBuffer;
	fsqVertex->SetSize(4);
	// 1
	fsqVertex->SetPosition(0, -x, -y, -0.2f);
	fsqVertex->SetTexcrood(0, 0.0f, 0.0f);
	// 2
	fsqVertex->SetPosition(1, x, -y, -0.2f);
	fsqVertex->SetTexcrood(1, 1.0f, 0.0f);
	// 3
	fsqVertex->SetPosition(2, -x, y, -0.2f);
	fsqVertex->SetTexcrood(2, 0.0f, 1.0f);
	// 4
	fsqVertex->SetPosition(3, x, y, -0.2f);
	fsqVertex->SetTexcrood(3, 1.0f, 1.0f);
}

// �����ӿڵĴ�С
void SetViewPortSize(float width, float height)
{
	// ����ͶӰ����
	projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
	fbo = new FrameBufferObject;
	fbo->AttachColorBuffer("color", GL_COLOR_ATTACHMENT0, (int)width, (int)height);
	fbo->AttachColorBuffer("color1", GL_COLOR_ATTACHMENT1, (int)width, (int)height);
	fbo->AttachDepthBuffer("depth", (int)width, (int)height);
	fbo->Finish();

	sphere.Init("Res/Sphere.obj");
	sphere.SetTexture(fbo->GetBuffer("color1"));
	sphere.mModelMatrix = glm::scale(4.0f, 4.0f, 4.0f) * glm::rotate(150.0f, 0.0f, 1.0f, 0.0f);

	// �����ı���  GPU��
	fsqVertex = new VertexBuffer;
	fsqVertex->SetSize(4);
	// 1
	// z����>1 ��Ϊ���ڱ߳�Ϊ1���������������
	fsqVertex->SetPosition(0, -1.0f, -1.0f, -0.2f);
	fsqVertex->SetTexcrood(0, 0.0f, 0.0f);
	// 2
	fsqVertex->SetPosition(1, 1.0f, -1.0f, -0.2f);
	fsqVertex->SetTexcrood(1, 1.0f, 0.0f);
	// 3
	fsqVertex->SetPosition(2, -1.0f, 1.0f, -0.2f);
	fsqVertex->SetTexcrood(2, 0.0f, 1.0f);
	// 4
	fsqVertex->SetPosition(3, 1.0f, 1.0f, -0.2f);
	fsqVertex->SetTexcrood(3, 1.0f, 1.0f);

	fsqShader = new Shader;
	fsqShader->Init("Res/fullscreenquad.vs", "Res/texture.fs");
	fsqShader->SetTexture("U_Texture", fbo->GetBuffer("color"));
}

void Draw()
{
	// ��ȡÿ֡��ʱ��
	float frameTime = GetFrameTime();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ����fbo���ó������ƵĶ��������Ƶ�fbo��ȥ
	fbo->Bind();
	// ������պ�
	skybox.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
	// ���Ƶ���
	//ground.Draw(viewMatrix, projectionMatrix);
	// ����ģ��
	//model.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
	// ����ţͷ
	//niutou.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);
	// �������ӵ�λ��
	ps.Update(frameTime);
	// ��������
	ps.Draw(viewMatrix, projectionMatrix);
	fbo->UnBind();
	// ������
	//sphere.Draw(viewMatrix, projectionMatrix, cameraPos.x, cameraPos.y, cameraPos.z);

	// �����ı���
	fsqVertex->Bind();
	fsqShader->Bind(glm::value_ptr(modelMatrix), glm::value_ptr(fsqViewMatrix), glm::value_ptr(projectionMatrix));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, fsqVertex->mVertexCount);
	fsqVertex->Unbind();
}
