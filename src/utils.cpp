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

// 解码BMP格式的图片
unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	// 判断图片是否是位图
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
// 生成2D纹理对象
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
// 从BMP文件中创建纹理对象
GLuint CreateTexture2DFromBMP(const char* bmpPath)
{
	int nFileSize = 0;
	// 加载文件内容
	unsigned char* bmpFileContent = LoadFileContent(bmpPath, nFileSize);
	if (bmpFileContent == nullptr)
	{
		return 0;
	}
	// 解码BMP文件
	int bmpWidth = 0, bmpHeight = 0;
	unsigned char* pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	if (bmpWidth == 0)
	{
		delete bmpFileContent;
		return 0;
	}
	// 创建纹理对象
	GLuint texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);
	delete bmpFileContent;
	return texture;
}
// 创建vbo / ebo的方法
GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void* data /*= nullptr*/)
{
	GLuint object;
	glGenBuffers(1, &object);
	glBindBuffer(bufferType, object);
	glBufferData(bufferType, size, data, usage);
	glBindBuffer(bufferType, 0);
	return object;
}
// 创建程序纹理
GLuint CreateProcedureTexture(int size)
{
	// 存放程序纹理的数据
	unsigned char* imageData = new unsigned char[size * size * 4];
	float halfSize = (float)size / 2.0f;
	float maxDistance = sqrtf(halfSize * halfSize + halfSize * halfSize);
	float centerX = halfSize;
	float centerY = halfSize;

	for (int y = 0; y < size; ++y)
	{
		for (int x = 0; x < size; ++x)
		{
			int currentPixelOffset = (x + y * size) * 4;
			imageData[currentPixelOffset] = 255;
			imageData[currentPixelOffset + 1] = 255;
			imageData[currentPixelOffset + 2] = 255;
			float deltaX = (float)x - centerX;
			float deltaY = (float)y - centerY;
			// 获取每个点的距离 从而计算出当前纹理a值
			float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
			float alpha = powf(1.0f - (distance * maxDistance), 8.0f);
			alpha = alpha > 1.0f ? 1.0f : alpha;
			imageData[currentPixelOffset + 3] = (unsigned char)(alpha * 255.0f);
		}
	}
	GLuint texture = CreateTexture2D(imageData, size, size, GL_RGBA);
	delete imageData;
	return texture;
}