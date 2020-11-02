#pragma once
#include "ggl.h"

unsigned char* LoadFileContent(const char* path, int& filesize);

GLuint CompileShader(GLenum shaderType, const char* shaderCode);

GLuint CreateProgram(GLuint vsShader, GLuint fsShader);

float GetFrameTime();

unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height);

GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type);

GLuint CreateTexture2DFromBMP(const char* bmpPath);

GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void* data = nullptr);