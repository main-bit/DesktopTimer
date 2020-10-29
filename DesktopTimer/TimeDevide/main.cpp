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
		//����������Ϣ
		TrayHandleMsg(_lParam);
	}
	else if (ID_ALL_TRAYMENU(_wParam)) {	//�Ƚ����в˵���ID
		//�������̲˵���Ϣ
		TrayHandleMenuMsg(_wParam);
	}
	switch (_message) {
		case WM_LBUTTONDOWN:
			OnLButtonDown();		break;	//�������
		case WM_LBUTTONUP:
			OnLButtonUp();			break;	//�������

		case WM_RBUTTONDOWN:
			OnRButtonDown();		break;	//�Ҽ�����bb
		case WM_RBUTTONUP:
			OnRButtonUp();			break;	//�Ҽ�����

		case WM_MOUSEMOVE:
			OnMouseMove();			break;	//����ƶ�

		case WM_LBUTTONDBLCLK:
			OnRButtonDownDouble();
			OnLButtonDownDouble();	break;	//���˫��
		case WM_RBUTTONDBLCLK:
			OnRButtonDownDouble();	break;	//�Ҽ�˫��
		case WM_KEYUP:
			switch (_wParam) {
			case VK_F6:			//���㲢��ʼ��ʱ
				OnRButtonDownDouble();
				OnLButtonDownDouble();
			}
			break;

		case WM_SETFOCUS:			break;	//��ý���
		case WM_KILLFOCUS:			break;	//ʧȥ����

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