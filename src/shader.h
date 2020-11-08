#pragma once
#include "ggl.h"

struct UniformTexture
{
	GLint mLocation;
	GLuint mTexture;
	UniformTexture()
	{
		mLocation = -1;
		mTexture = 0;
	}
};

struct UniformVector4f {
	GLint mLocation;
	float v[4];
	UniformVector4f() {
		mLocation = -1;
		memset(v, 0, sizeof(float) * 4);
	}
};

class Shader {
public:
	GLuint mProgram;
	// ����������
	std::map<std::string, UniformTexture*> mUniformTextures;
	// ������verctor4f
	std::map<std::string, UniformVector4f*> mUniformVec4s;
	GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMatrixLocation;
	GLint mPositionLocation, mColorLocation, mTexcoordLocation, mNormalLocation;
	void Init(const char* vs, const char* fs);

	void Bind(float* M, float* V, float* P);
	// ���ô��ⲿ���ص�����
	void SetTexture(const char* name, const char* imagePath);
	// ���ó�������
	void SetTexture(const char* name, GLuint texture);

	void SetVec4(const char* name, float x, float y, float z, float w);
};