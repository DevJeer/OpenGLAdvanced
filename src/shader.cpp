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
	// 设置Vec4的值
	for (auto iter = mUniformVec4s.begin(); iter != mUniformVec4s.end(); ++iter)
	{
		glUniform4fv(iter->second->mLocation, 1, iter->second->v);
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

void Shader::SetTexture(const char* name, GLuint texture)
{
	auto iter = mUniformTextures.find(name);
	// 如果查找不到
	if (iter == mUniformTextures.end())
	{
		GLint location = glGetUniformLocation(mProgram, name);
		if (location != -1)
		{
			UniformTexture* t = new UniformTexture;
			t->mLocation = location;
			t->mTexture = texture;
			mUniformTextures.insert(std::pair<std::string, UniformTexture*>(name, t));
		}
	}
	else
	{
		// 查找到了，那么就是替换当前的纹理对象
		glDeleteTextures(1, &iter->second->mTexture);
		iter->second->mTexture = texture;
	}
}

// 设置uniform4f值
void Shader::SetVec4(const char* name, float x, float y, float z, float w)
{
	auto iter = mUniformVec4s.find(name);
	if (iter == mUniformVec4s.end())
	{
		GLint location = glGetUniformLocation(mProgram, name);
		// 找到位置
		if (location != -1)
		{
			UniformVector4f* v = new UniformVector4f;
			v->v[0] = x;
			v->v[1] = y;
			v->v[2] = z;
			v->v[3] = w;
			v->mLocation = location;
			// 添加pair (键值对)
			mUniformVec4s.insert(std::pair<std::string, UniformVector4f*>(name, v));
		}
	}
	else
	{
		// 更新对应的插槽
		iter->second->v[0] = x;
		iter->second->v[1] = y;
		iter->second->v[2] = z;
		iter->second->v[3] = w;
	}
}