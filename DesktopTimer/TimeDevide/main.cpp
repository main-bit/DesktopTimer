#include "stdafx.h"
#include "TransparentWindow.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	TransparentWindow::SetTransparentWindow(TransparentWindow::create(hInstance, nCmdShow));
	TransparentWindow* TW = TransparentWindow::GetTransparentWindow();
	TW->run(hInstance);
	return 0;
}



LRESULT CALLBACK TransparentWindow::WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
	if (_wParam == ID_TRAY) {
		//处理托盘消息
		TrayHandleMsg(_lParam);
	}
	else if (ID_ALL_TRAYMENU(_wParam)) {	//比较所有菜单的ID
		//处理托盘菜单消息
		TrayHandleMenuMsg(_wParam);
	}
	switch (_message) {
		case WM_LBUTTONDOWN:
			OnLButtonDown();		break;	//左键按下
		case WM_LBUTTONUP:
			OnLButtonUp();			break;	//左键弹起

		case WM_RBUTTONDOWN:
			OnRButtonDown();		break;	//右键按下bb
		case WM_RBUTTONUP:
			OnRButtonUp();			break;	//右键弹起

		case WM_MOUSEMOVE:
			OnMouseMove();			break;	//鼠标移动

		case WM_LBUTTONDBLCLK:
			OnRButtonDownDouble();
			OnLButtonDownDouble();	break;	//左键双击
		case WM_RBUTTONDBLCLK:
			OnRButtonDownDouble();	break;	//右键双击
		case WM_KEYUP:
			switch (_wParam) {
			case VK_F6:			//清零并开始计时
				OnRButtonDownDouble();
				OnLButtonDownDouble();
			}
			break;

		case WM_SETFOCUS:			break;	//获得焦点
		case WM_KILLFOCUS:			break;	//失去焦点

		case WM_SIZE: {
			LONG_PTR Style = ::GetWindowLongPtr(_hwnd, GWL_STYLE);
			Style = Style & ~WS_CAPTION &~WS_SYSMENU &~WS_SIZEBOX;
			::SetWindowLongPtr(_hwnd, GWL_STYLE, Style);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}