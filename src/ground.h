#pragma once
#include "utils.h"
#include "vertexbuffer.h"

class Ground {
	VertexBuffer *mVertexBuffer;
	GLuint mVBO;
	GLuint mProgram;
	GLint mPositionLocation, mColorLocation, mNormalLocation;
	GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMartixLocation;
public:
	void Init();
};