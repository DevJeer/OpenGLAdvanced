#pragma once
#include "utils.h"
#include "vertexbuffer.h"

class Ground {
	VertexBuffer *mVertexBuffer;
	GLuint mVBO;
public:
	void Init();
};