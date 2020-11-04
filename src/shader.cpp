#include "shader.h"
#include "utils.h"
#include "vertexbuffer.h"

// 初始化Shader
void Shader::Init(const char* vs, const char* fs)
{
	int nFileSize = 0;
	const char *vsCode = (char*)LoadFileContent(vs, nFileSize);
	const char* fsCode = (char*)LoadFileContent(fs, nFileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsCode);
	if (vsShader == 0)
		return;
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsCode);
	if (fsShader == 0)
		return;

	mProgram = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);

	if (mProgram != 0)
	{
		// 获取插槽
		mModelMatrixLocation = glGetUniformLocation(mProgram, "ModelMatrix");
		mViewMatrixLocation = glGetUniformLocation(mProgram, "ViewMatrix");
		mProjectionMatrixLocation = glGetUniformLocation(mProgram, "ProjectionMatrix");
		mPositionLocation = glGetAttribLocation(mProgram, "position");
		mColorLocation = glGetAttribLocation(mProgram, "color");
		mTexcoordLocation = glGetAttribLocation(mProgram, "texcoord");
		mNormalLocation = glGetAttribLocation(mProgram, "normal");
	}
}
// 绑定mvp矩阵
void Shader::Bind(float* M, float* V, float* P)
{
	glUseProgram(mProgram);
	// 填充uniform的值
	glUniformMatrix4fv(mModelMatrixLocation, 1, GL_FALSE, M);
	glUniformMatrix4fv(mViewMatrixLocation, 1, GL_FALSE, V);
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, P);
	// 设置纹理
	int iIndex = 0;
	for (auto iter = mUniformTextures.begin(); iter != mUniformTextures.end(); ++iter)
	{
		// 激活对应的texture unit
		glActiveTexture(GL_TEXTURE0 + iIndex);
		glBindTexture(GL_TEXTURE_2D, iter->second->mTexture);
		// 填充对应的texture unit
		glUniform1i(iter->second->mLocation, iIndex);
	}
	// 填充attrib的值
	glEnableVertexAttribArray(mPositionLocation);
	glVertexAttribPointer(mPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(mColorLocation);
	glVertexAttribPointer(mColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(mTexcoordLocation);
	glVertexAttribPointer(mTexcoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(mNormalLocation);
	glVertexAttribPointer(mNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 12));
}
// 设置纹理
void Shader::SetTexture(const char* name, const char* imagePath)
{
	auto iter = mUniformTextures.find(name);
	// 如果没有找到相同的纹理
	if (iter == mUniformTextures.end())
	{
		// 尝试获取插槽
		GLint location = glGetUniformLocation(mProgram, name);
		if (location != -1)
		{
			UniformTexture* t = new UniformTexture;
			t->mLocation = location;
			t->mTexture = CreateTexture2DFromBMP(imagePath);
			mUniformTextures.insert(std::pair<std::string, UniformTexture*>(name, t));
		}
	}
	else
	{
		// 先删除当前的纹理
		glDeleteTextures(1, &iter->second->mTexture);
		// 加载新的纹理
		iter->second->mTexture = CreateTexture2DFromBMP(imagePath);
	}
}