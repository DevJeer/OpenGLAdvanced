#include "skybox.h"

void SkyBox::Init(const char* imageDir)
{
	InitFront(imageDir);
	InitBack(imageDir);
	InitRight(imageDir);
	InitLeft(imageDir);
	InitTop(imageDir);
	InitBottom(imageDir);
}
// 前面
void SkyBox::InitFront(const char* imageDir)
{
	mVertexBuffer[0].SetSize(4);
	// 1 point
	mVertexBuffer[0].SetPosition(0, -0.5f, -0.5f, -0.5f);
	mVertexBuffer[0].SetTexcrood(0, 0.0f, 0.0f);
	// 2 point
	mVertexBuffer[0].SetPosition(1, 0.5f, -0.5f, -0.5f);
	mVertexBuffer[0].SetTexcrood(1, 1.0f, 0.0f);
	// 3 point
	mVertexBuffer[0].SetPosition(2, -0.5f, 0.5f, -0.5f);
	mVertexBuffer[0].SetTexcrood(2, 0.0f, 1.0f);
	// 4 point
	mVertexBuffer[0].SetPosition(3, 0.5f, 0.5f, -0.5f);
	mVertexBuffer[0].SetTexcrood(3, 1.0f, 1.0f);
}
// 后面
void SkyBox::InitBack(const char* imageDir)
{
	mVertexBuffer[1].SetSize(4);
	// 1 point
	mVertexBuffer[1].SetPosition(0, 0.5f, -0.5f, 0.5f);
	mVertexBuffer[1].SetTexcrood(0, 0.0f, 0.0f);
	// 2 point
	mVertexBuffer[1].SetPosition(1, -0.5f, -0.5f, 0.5f);
	mVertexBuffer[1].SetTexcrood(1, 1.0f, 0.0f);
	// 3 point
	mVertexBuffer[1].SetPosition(2, 0.5f, 0.5f, 0.5f);
	mVertexBuffer[1].SetTexcrood(2, 0.0f, 1.0f);
	// 4 point
	mVertexBuffer[1].SetPosition(3, -0.5f, 0.5f, 0.5f);
	mVertexBuffer[1].SetTexcrood(3, 1.0f, 1.0f);
}
// 左面
void SkyBox::InitLeft(const char* imageDir)
{
	mVertexBuffer[2].SetSize(4);
	// 1 point
	mVertexBuffer[2].SetPosition(0, -0.5f, -0.5f, 0.5f);
	mVertexBuffer[2].SetTexcrood(0, 0.0f, 0.0f);
	// 2 point
	mVertexBuffer[2].SetPosition(1, -0.5f, -0.5f, -0.5f);
	mVertexBuffer[2].SetTexcrood(1, 1.0f, 0.0f);
	// 3 point
	mVertexBuffer[2].SetPosition(2, -0.5f, 0.5f, 0.5f);
	mVertexBuffer[2].SetTexcrood(2, 0.0f, 1.0f);
	// 4 point
	mVertexBuffer[2].SetPosition(3, -0.5f, 0.5f, -0.5f);
	mVertexBuffer[2].SetTexcrood(3, 1.0f, 1.0f);
}
// 右面
void SkyBox::InitRight(const char* imageDir)
{
	mVertexBuffer[3].SetSize(4);
	// 1 point
	mVertexBuffer[3].SetPosition(0, 0.5f, -0.5f, -0.5f);
	mVertexBuffer[3].SetTexcrood(0, 0.0f, 0.0f);
	// 2 point
	mVertexBuffer[3].SetPosition(1, 0.5f, -0.5f, 0.5f);
	mVertexBuffer[3].SetTexcrood(1, 1.0f, 0.0f);
	// 3 point
	mVertexBuffer[3].SetPosition(2, 0.5f, 0.5f, -0.5f);
	mVertexBuffer[3].SetTexcrood(2, 0.0f, 1.0f);
	// 4 point
	mVertexBuffer[3].SetPosition(3, 0.5f, 0.5f, 0.5f);
	mVertexBuffer[3].SetTexcrood(3, 1.0f, 1.0f);
}
// 上面
void SkyBox::InitTop(const char* imageDir)
{
	mVertexBuffer[4].SetSize(4);
	// 1 point
	mVertexBuffer[4].SetPosition(0, -0.5f, 0.5f, -0.5f);
	mVertexBuffer[4].SetTexcrood(0, 0.0f, 0.0f);
	// 2 point
	mVertexBuffer[4].SetPosition(1, 0.5f, 0.5f, -0.5f);
	mVertexBuffer[4].SetTexcrood(1, 1.0f, 0.0f);
	// 3 point
	mVertexBuffer[4].SetPosition(2, -0.5f, 0.5f, 0.5f);
	mVertexBuffer[4].SetTexcrood(2, 0.0f, 1.0f);
	// 4 point
	mVertexBuffer[4].SetPosition(3, 0.5f, 0.5f, 0.5f);
	mVertexBuffer[4].SetTexcrood(3, 1.0f, 1.0f);
}
// 下面
void SkyBox::InitBottom(const char* imageDir)
{
	mVertexBuffer[5].SetSize(4);
	// 1 point
	mVertexBuffer[5].SetPosition(0, -0.5f, -0.5f, 0.5f);
	mVertexBuffer[5].SetTexcrood(0, 0.0f, 0.0f);
	// 2 point
	mVertexBuffer[5].SetPosition(1, 0.5f, -0.5f, 0.5f);
	mVertexBuffer[5].SetTexcrood(1, 1.0f, 0.0f);
	// 3 point
	mVertexBuffer[5].SetPosition(2, -0.5f, -0.5f, -0.5f);
	mVertexBuffer[5].SetTexcrood(2, 0.0f, 1.0f);
	// 4 point
	mVertexBuffer[5].SetPosition(3, 0.5f, -0.5f, -0.5f);
	mVertexBuffer[5].SetTexcrood(3, 1.0f, 1.0f);
}