#pragma once
#include "ggl.h"
#include "vertexbuffer.h"
#include "shader.h"

class Model {
	VertexBuffer* mVertexBuffer;

	Shader* mShader;
	glm::mat4 mModelMatrix;
public:
	Model();
	void Init(const char* modelPath);

	void Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);

	void SetPosition(float x, float y, float z);

	void SetAmbientMaterial(float r, float g, float b, float a);

	void SetDiffuseMaterial(float r, float g, float b, float a);

	void SetSpecularMaterial(float r, float g, float b, float a);
};