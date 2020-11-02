#pragma once
#include "ggl.h"

unsigned char* LoadFileContent(const char* path, int& filesize);

GLuint CompileShader(GLenum shaderType, const char* shaderCode);

GLuint CreateProgram(GLuint vsShader, GLuint fsShader);

float GetFrameTime();

unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height);