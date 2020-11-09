#pragma once
#include "ggl.h"
class FrameBufferObject {
public:
	GLuint mFrameBufferObject;
	GLint mPrevFrameBuffer;
	std::map<std::string, GLuint> mBuffers;
	std::vector<GLenum> mDrawBuffers;

public:
	FrameBufferObject();
	void AttachColorBuffer(const char* bufferName, GLenum attachment, int width, int height);
	void AttachDepthBuffer(const char* bufferName, int width, int height);
	void Finish();
	void Bind();
	void UnBind();
	GLuint GetBuffer(const char* bufferName);
};