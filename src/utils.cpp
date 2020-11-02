#include "utils.h"
// ����Shader
GLuint CompileShader(GLenum shaderType, const char* shaderCode)
{
	// ����������Shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	// Shader������
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		char szLog[1024] = {0};
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log: %s \nShader code :\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}

	return shader;
}
// ����Shader�ĳ���
GLuint CreateProgram(GLuint vsShader, GLuint fsShader)
{
	// ���ɳ��򣬲������ӵ�GPU��
	GLuint program = glCreateProgram();
	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);
	glLinkProgram(program);
	glDetachShader(program, vsShader);
	glDetachShader(program, fsShader);
	// ���ɳ��������
	GLint nResult;
	glGetProgramiv(program, GL_LINK_STATUS, &nResult);
	if (nResult == GL_FALSE)
	{
		char log[1024] = { 0 };
		GLsizei writed = 0;
		glGetProgramInfoLog(program, 1024, &writed, log);
		printf("Create gpu program fail, link error : %s\n", log);
		glDeleteProgram(program);
		program = 0;
	}
	return program;
}

// ����BMP��ʽ��ͼƬ
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	// �ж�ͼƬ�Ƿ���λͼ
	if (0x4D42 == *((unsigned short*)bmpFileData))
	{
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char* pixelData = bmpFileData + pixelDataOffset;
		for (int i = 0; i < width * height * 3; i += 3)
		{
			// BGR ---> RGB
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}
		return pixelData;
	}
	return nullptr;
}
// ����2D�������
GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}