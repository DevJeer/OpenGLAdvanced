#pragma once
#include "utils.h"
#include "vertexbuffer.h"
#include "shader.h"

class Ground {
	VertexBuffer *mVertexBuffer;
	Shader *mShader;
	glm::mat4 mModelMatrix;
public:
	void Init();
	void Draw(glm::mat4& viewMatrix, glm::mat4& projectionMartix);
};