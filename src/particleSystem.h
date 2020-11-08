#pragma once
#include "vertexbuffer.h"
#include "shader.h"

class ParticleSystem {
	VertexBuffer* mVertexBuffer;
	glm::mat4 mModelMatrix;
	Shader* mShader;
public:
	// 粒子初始化
	void Init(float x, float y, float z);
	// 绘制粒子
	void Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
	// 更新粒子的位置
	void Update(float deltaTime);
};