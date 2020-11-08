#include "particleSystem.h"
#include "utils.h"

// Á£×Ó³õÊ¼»¯
void ParticleSystem::Init(float x, float y, float z)
{
	mModelMatrix = glm::translate(x, y, z);
	mVertexBuffer = new VertexBuffer;
	mVertexBuffer->SetSize(1);
	mVertexBuffer->SetColor(0, 0.1f, 0.4f, 0.6f);
}