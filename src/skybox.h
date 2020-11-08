#pragma once
#include "vertexbuffer.h"
#include "shader.h"
class SkyBox {
	VertexBuffer* mVertexBuffer;
	Shader* mShader;
	glm::mat4 mModelMatrix;
public:
	void Init(const char* imageDir);

	void InitFront(const char* imageDir);
	void InitBack(const char* imageDir);
	void InitLeft(const char* imageDir);
	void InitRight(const char* imageDir);
	void InitTop(const char* imageDir);
	void InitBottom(const char* imageDir);

	void Draw(glm::mat4& V, glm::mat4& P, float x, float y, float z);
};