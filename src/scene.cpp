#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"
#include "shader.h"

GLuint vbo, ebo;
GLuint program;

// 纹理坐标和纹理的插槽
GLuint textureLocation;
GLuint texture;

glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
Ground ground;

Shader* shader;
VertexBuffer* vertexbuffer;
void Init()
{
	// 使用Vertexbuffer来绘制
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
	// 绘制地面
	ground.Draw(viewMatrix, projectionMatrix);


	// 绑定vbo
	vertexbuffer->Bind();
	// 绑定shader
	shader->Bind(glm::value_ptr(modelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));

	// 设置当前要操作的纹理对象
	glBindTexture(GL_TEXTURE_2D, texture);
	// 告诉纹理对象资源在哪儿
	glUniform1i(textureLocation, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vertexbuffer->Unbind();

}
