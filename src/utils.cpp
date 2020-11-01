#include "utils.h"
// 编译Shader
GLuint CompileShader(GLenum shaderType, const char* shaderCode)
{
	// 创建并编译Shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	// Shader错误检查
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
// 生成Shader的程序
GLuint CreateProgram(GLuint vsShader, GLuint fsShader)
{
	// 生成程序，并且链接到GPU中
	GLuint program = glCreateProgram();
	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);
	glLinkProgram(program);
	glDetachShader(program, vsShader);
	glDetachShader(program, fsShader);
	// 生成程序错误检查
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