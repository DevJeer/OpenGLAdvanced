#include "shader.h"
#include "utils.h"
#include "vertexbuffer.h"

// ��ʼ��Shader
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
		// ��ȡ���
		mModelMatrixLocation = glGetUniformLocation(mProgram, "ModelMatrix");
		mViewMatrixLocation = glGetUniformLocation(mProgram, "ViewMatrix");
		mProjectionMatrixLocation = glGetUniformLocation(mProgram, "ProjectionMatrix");
		mPositionLocation = glGetAttribLocation(mProgram, "position");
		mColorLocation = glGetAttribLocation(mProgram, "color");
		mTexcoordLocation = glGetAttribLocation(mProgram, "texcoord");
		mNormalLocation = glGetAttribLocation(mProgram, "normal");
	}
}
// ��mvp����
void Shader::Bind(float* M, float* V, float* P)
{
	glUseProgram(mProgram);
	// ���uniform��ֵ
	glUniformMatrix4fv(mModelMatrixLocation, 1, GL_FALSE, M);
	glUniformMatrix4fv(mViewMatrixLocation, 1, GL_FALSE, V);
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, P);
	// ��������
	int iIndex = 0;
	for (auto iter = mUniformTextures.begin(); iter != mUniformTextures.end(); ++iter)
	{
		// �����Ӧ��texture unit
		glActiveTexture(GL_TEXTURE0 + iIndex);
		glBindTexture(GL_TEXTURE_2D, iter->second->mTexture);
		// ����Ӧ��texture unit
		glUniform1i(iter->second->mLocation, iIndex);
	}
	// ����Vec4��ֵ
	for (auto iter = mUniformVec4s.begin(); iter != mUniformVec4s.end(); ++iter)
	{
		glUniform4fv(iter->second->mLocation, 1, iter->second->v);
	}
	// ���attrib��ֵ
	glEnableVertexAttribArray(mPositionLocation);
	glVertexAttribPointer(mPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(mColorLocation);
	glVertexAttribPointer(mColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(mTexcoordLocation);
	glVertexAttribPointer(mTexcoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(mNormalLocation);
	glVertexAttribPointer(mNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 12));
}
// ��������
void Shader::SetTexture(const char* name, const char* imagePath)
{
	auto iter = mUniformTextures.find(name);
	// ���û���ҵ���ͬ������
	if (iter == mUniformTextures.end())
	{
		// ���Ի�ȡ���
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
		// ��ɾ����ǰ������
		glDeleteTextures(1, &iter->second->mTexture);
		// �����µ�����
		iter->second->mTexture = CreateTexture2DFromBMP(imagePath);
	}
}

void Shader::SetTexture(const char* name, GLuint texture)
{
	auto iter = mUniformTextures.find(name);
	// ������Ҳ���
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
		// ���ҵ��ˣ���ô�����滻��ǰ���������
		glDeleteTextures(1, &iter->second->mTexture);
		iter->second->mTexture = texture;
	}
}

// ����uniform4fֵ
void Shader::SetVec4(const char* name, float x, float y, float z, float w)
{
	auto iter = mUniformVec4s.find(name);
	if (iter == mUniformVec4s.end())
	{
		GLint location = glGetUniformLocation(mProgram, name);
		// �ҵ�λ��
		if (location != -1)
		{
			UniformVector4f* v = new UniformVector4f;
			v->v[0] = x;
			v->v[1] = y;
			v->v[2] = z;
			v->v[3] = w;
			v->mLocation = location;
			// ���pair (��ֵ��)
			mUniformVec4s.insert(std::pair<std::string, UniformVector4f*>(name, v));
		}
	}
	else
	{
		// ���¶�Ӧ�Ĳ��
		iter->second->v[0] = x;
		iter->second->v[1] = y;
		iter->second->v[2] = z;
		iter->second->v[3] = w;
	}
}