/*******************************************************************
程序：EasyWin
文件：EasyWin.c
功能：Windows 应用程序基本框架
********************************************************************/
#include <windows.h>
#include <windowsx.h>
#include"resource.h"

//函数声明
BOOL gbShowIcon="
BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
/*******************************************************************
函数：WinMain ()
功能：Win32 应用程序入口函数。创建主窗口，处理消息循环
********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance,         //当前实例句柄
	HINSTANCE hPrevInstance,     //前一个实例句柄
	PSTR szCmdLine,              //命令行字符
	int iCmdShow)                //窗口显示方式
{
	MSG msg;
	char *p;

	//创建主窗口
	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;

	p = 0;
	//进入消息循环：从该应用程序的消息队列中检取消息，
	//送到消息处理过程，当检取到WM_QUIT消息时，退出消息循环。
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

/******************************************************************
函数：InitWindow ()
功能：创建窗口。
*******************************************************************/
static BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("EasyWin");  //应用程序名称
	HWND hwnd;                                    //窗口句柄
	WNDCLASS wcMainWnd;                           //窗口类结构
	ATOM a;

	//填充窗口类结构
	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_oldbig));
	wcMainWnd.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
	wcMainWnd.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcMainWnd.lpszClassName = szAppName;

	//注册窗口类
	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	//创建主窗口
	hwnd = CreateWindow(szAppName, 						//窗口类名称
		TEXT("Windows 应用程序基本框架"),  //窗口标题
		WS_OVERLAPPEDWINDOW,				//窗口风格
		100,								//窗口位置的x坐标
		100,								//窗口位置的y坐标
		400,								//窗口的宽度
		300,								//窗口的高度
		NULL,								//父窗口句柄
		NULL,								//菜单句柄
		hInstance,							//应用程序实例句柄
		NULL);								//窗口创建数据指针

	if (!hwnd) return FALSE;

	//显示并更新窗口
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

/******************************************************************
函数：WinProc ()
功能：处理主窗口消息
*******************************************************************/
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	switch (message)
	{
	case WM_CREATE:         //创建消息
		PlaySound(TEXT("EasyWin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;

	case WM_KEYDOWN:         //击键消息
		switch (wParam)
		{
		case VK_ESCAPE:
			MessageBox(hWnd, TEXT("ESC键按下了!"), TEXT("键盘"), MB_OK);
			break;
		}
		return 0;

	case WM_RBUTTONDOWN:        //鼠标消息
		MessageBox(hWnd, TEXT("鼠标右键按下了!"), TEXT("鼠标"), MB_OK);
		return 0;

	case WM_PAINT:              //客户区重绘消息

								//取得设备环境句柄
		hdc = BeginPaint(hWnd, &ps);

		//取得窗口客户区矩形
		GetClientRect(hWnd, &rect);

		//设置文字颜色
		SetTextColor(hdc, RGB(0, 0, 255));

		//输出文字
		DrawText(hdc, TEXT("热烈欢迎老大莅临检查指导工作"),
			-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		//释放资源
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
    case WM_COMMAND



	}

	//调用缺省消息处理过程
	return DefWindowProc(hWnd, message, wParam, lParam);

} //函数 WinProc 结束

