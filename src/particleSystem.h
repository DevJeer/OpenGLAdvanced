#pragma once
#include "vertexbuffer.h"
#include "shader.h"

class ParticleSystem {
	VertexBuffer* mVertexBuffer;
	glm::mat4 mModelMatrix;
public:
	// Á£×Ó³õÊ¼»¯
	void Init(float x, float y, float z);
};