#include "ggl.h"
#include "scene.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

// �����û��Ĳ���
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ���崰�ڵ���
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = GLWindowProc;
	wndClass.lpszClassName = L"GLWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	// ע�ᴰ��
	ATOM atom = RegisterClassEx(&wndClass);
	if (!atom)
	{
		MessageBox(NULL, L"Notice", L"Error", MB_OK);
		return 0;
	}

	// �����ӿڵĴ�С
	RECT rect;
	rect.left = 0;
	rect.right = 1280;
	rect.top = 0;
	rect.bottom = 720;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	// ��������
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW, 100, 100, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
	
	// �OpenGL����Ⱦ���
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);
	
	//����������  ��������������
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	// ��ʼ��������OPENGL�ĸ߼�����
	glewInit();
	Init();
	SetViewPortSize(1280, 720);

	ShowWindow(hwnd, SW_SHOW);
	// ���´���
	UpdateWindow(hwnd);

	// ��ʾ���� ���ó���һֱ���У� 
	MSG msg;
	while (true)
	{
		// ��ȡ��Ϣ �� ��ȡ����Ϣ֮�󣬰ѵ�ǰ��Ϣ����Ϣ�������Ƴ���
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			// ����ϢΪ�Ƴ���Ϣ��ʱ�򣬾��˳�ѭ��
			if (msg.message == WM_QUIT)
			{
				break;
			}
			// ת��ΪӦ�ó������ʶ�����Ϣ
			TranslateMessage(&msg);
			// �ַ���Ϣ
			DispatchMessage(&msg);
		}
		Draw();
		SwapBuffers(dc);
	}
	return 0;
}