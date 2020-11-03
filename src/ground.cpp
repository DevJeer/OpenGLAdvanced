#include "ground.h"

// 初始化地面数据
void Ground::Init()
{
	mVertexBuffer = new VertexBuffer();
	mVertexBuffer->SetSize(1600);
	for (int z = 0; z < 20; ++z)
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; ++x)
		{
			int offset = (x + z * 20) * 4;
			float xStart = x * 10.0f - 100.0f;
			mVertexBuffer->SetPosition(offset, xStart, -1.0f, zStart);
			mVertexBuffer->SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
			mVertexBuffer->SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
			mVertexBuffer->SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);

			mVertexBuffer->SetNormal(offset, 0.0f, 1.0f, 0.0f);
			mVertexBuffer->SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
			mVertexBuffer->SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
			mVertexBuffer->SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);
			if ((z % 2) ^ (x % 2))
			{
				mVertexBuffer->SetColor(offset, 0.1f, 0.1f, 0.1f);
				mVertexBuffer->SetColor(offset + 1, 0.1f, 0.1f, 0.1f);
				mVertexBuffer->SetColor(offset + 2, 0.1f, 0.1f, 0.1f);
				mVertexBuffer->SetColor(offset + 3, 0.1f, 0.1f, 0.1f);
			}
			else
			{
				mVertexBuffer->SetColor(offset, 0.8f, 0.8f, 0.8f);
				mVertexBuffer->SetColor(offset + 1, 0.8f, 0.8f, 0.8f);
				mVertexBuffer->SetColor(offset + 2, 0.8f, 0.8f, 0.8f);
				mVertexBuffer->SetColor(offset + 3, 0.8f, 0.8f, 0.8f);
			}
		}
	}
	// 创建vbo对象
	mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * 1600, GL_STATIC_DRAW, mVertexBuffer->mVertexes);

	// 加载shader
	int fileSize = 0;
	unsigned char* shaderCode = LoadFileContent("Res/ground.vs", fileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
	delete shaderCode;

	shaderCode = LoadFileContent("Res/ground.fs", fileSize);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
	delete shaderCode;
	// 创建shader程序
	mProgram = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);

	// 获取插槽的位置
	mPositionLocation = glGetAttribLocation(mProgram, "position");
	mColorLocation = glGetAttribLocation(mProgram, "color");
	mNormalLocation = glGetAttribLocation(mProgram, "normal");
	mModelMatrixLocation = glGetUniformLocation(mProgram, "ModelMatrix");
	mViewMatrixLocation = glGetUniformLocation(mProgram, "ViewMatrix");
	mProjectionMartixLocation = glGetUniformLocation(mProgram, "ProjectionMatrix");
}