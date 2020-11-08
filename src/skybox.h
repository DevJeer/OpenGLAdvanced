#pragma once
#include "vertexbuffer.h"

class SkyBox {
	VertexBuffer* mVertexBuffer;
public:
	void Init(const char* imageDir);

	void InitFront(const char* imageDir);
	void InitBack(const char* imageDir);
	void InitLeft(const char* imageDir);
	void InitRight(const char* imageDir);
	void InitTop(const char* imageDir);
	void InitBottom(const char* imageDir);
};