#pragma once
#include "ggl.h"
#include "vertexbuffer.h"

class Model {
	VertexBuffer* mVertexBuffer;
public:
	Model();
	void Init(const char* modelPath);
};