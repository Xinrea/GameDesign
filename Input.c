/* Project:		GSMPre
   File Name:	Input.c
   Author:		刘芳
   Date:		2015-9-15
   Purpose:		输入模块  */

#include "System.h"
#include "stdio.h"
extern FILE* fp;
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

LRESULT CALLBACK Input_Handle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC dc;           // 设备
	PAINTSTRUCT ps;   // 重绘结构

	// 签到
	//fprintf(fp,"Input:Handle\n");

	switch (msg)
	{
		//  窗口创建
		case WM_CREATE:
			break;

		case WM_LBUTTONDOWN:
			//GS_Running = 0;
			break;

		case WM_MOUSEMOVE:
			break;

			// 重绘
		case WM_PAINT:
			dc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

			// 窗口关闭
		case WM_DESTROY:
			break;

		case WM_KEYDOWN:
			//if(wParam == VK_ESCAPE)
			//GS_Running = 0;
			break;

			// 窗口发生移动
		case WM_MOVE:
			break;

			// 调用默认窗口过程
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
