#include "particleSystem.h"
#include "utils.h"

// 粒子初始化
void ParticleSystem::Init(float x, float y, float z)
{
	mModelMatrix = glm::translate(x, y, z);
	mVertexBuffer = new VertexBuffer;
	mVertexBuffer->SetSize(1);
	mVertexBuffer->SetColor(0, 0.1f, 0.4f, 0.6f);
	mShader = new Shader;
	mShader->Init("Res/particle.vs", "Res/particle.fs");
	mShader->SetTexture("U_Texture", CreateProcedureTexture(128));
}

void ParticleSystem::Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	// 开启点精灵
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	// 设置混合的方式
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	mVertexBuffer->Bind();
	mShader->Bind(glm::value_ptr(mModelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	glDrawArrays(GL_POINTS, 0, mVertexBuffer->mVertexCount);
	mVertexBuffer->Unbind();

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_PROGRAM_POINT_SIZE);
}