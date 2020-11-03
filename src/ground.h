#pragma once
#include "utils.h"
#include "vertexbuffer.h"
#include "shader.h"

class Ground {
	VertexBuffer *mVertexBuffer;
	GLuint mVBO;
	Shader *mShader;
public:
	void Init();
};