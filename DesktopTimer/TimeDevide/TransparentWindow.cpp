#include "stdafx.h"
#include "resource.h"
#include "TransparentWindow.h"
#include <string>
#include <time.h>


TransparentWindow* TransparentWindow::TW = NULL;
bool TransparentWindow::s_ifUpDate = true;
int TransparentWindow::s_TimerNum = 0;

TransparentWindow* TransparentWindow::create(HINSTANCE _hInstance, int _CmdShow) {
	TransparentWindow* TW = new TransparentWindow(_CmdShow);
	return TW;
}

bool TransparentWindow::init(HINSTANCE _hInstance) {
	initWin(_hInstance);
	initWndTimer();
	initTimer();
	CreateTimer(Timer_SleepDraw);
	initTray();
	initFont();
	initStatic();
	return true;
}

void TransparentWindow::initWin(HINSTANCE _hInstance) {
	initLin_Window();
	PWNDCLASSEX pWnd = m_pWnd->GetpWnd();

	pWnd->cbSize = sizeof(WNDCLASSEX);
	pWnd->style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	pWnd->lpfnWndProc = static_cast<WNDPROC>(&TransparentWindow::WndProc);
	pWnd->cbClsExtra = 0;
	pWnd->cbWndExtra = 0;
	pWnd->hInstance = _hInstance;
	pWnd->hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON2));	//����ͼ��
	pWnd->hCursor = LoadCursor(NULL, IDC_ARROW);
	pWnd->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	pWnd->lpszMenuName = NULL;
	pWnd->lpszClassName = WINDOW_TITLE;
	pWnd->hIconSm = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON2));

	RegisterClassExW(pWnd);
	m_Hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW, WINDOW_TITLE, L"", WS_OVERLAPPEDWINDOW,
		WINDOW_POINT_X, WINDOW_POINT_Y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, _hInstance, NULL);

	ShowWindow(m_Hwnd, m_CmdShow);

	UpdateWindow(m_Hwnd);

	//����͸��
	SetLayeredWindowAttributes(m_Hwnd, TransparentRBG, 0, LWA_COLORKEY);
}

void TransparentWindow::initLin_Window() {
	m_pWnd = new Lin_Window(L"TimeDevide");
	m_pWnd->SetIfLeftMouseDown(false);
	m_pWnd->SetWindowPoint({ WINDOW_POINT_X, WINDOW_POINT_Y });
	RECT _rc;
	GetWindowRect(GetDesktopWindow(), &_rc);
	m_pWnd->SetWinSize(_rc);
}

void TransparentWindow::initWndTimer() {
	phWait = CreateWaitableTimer(NULL, FALSE, NULL);
	liDueTime.QuadPart = -1i64;
	SetWaitableTimer(phWait, &liDueTime, 5, NULL, NULL, 0);	//ÿ5ms����һ��
	dwRet = 0;
}

void TransparentWindow::initTimer() {
	m_SleepDrawTimer = Lin_Timer::create();
	m_Timer = Lin_Timer::create();
}

VOID CALLBACK TransparentWindow::SleepDraw(PVOID _lpParameter, BOOLEAN _TimerOrWaitFired) {
	//��ʱ���ص�����
	s_ifUpDate = true;
}

VOID CALLBACK TransparentWindow::TimerRoutine(PVOID _lpParameter, BOOLEAN _TimerOrWaitFired) {
	if(s_TimerNum < 999)
		++s_TimerNum;
}

void TransparentWindow::initTray() {
	//��ʾ����
	m_Tray.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_Tray.hWnd = m_Hwnd;
	m_Tray.uID = ID_TRAY;
	m_Tray.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_Tray.uCallbackMessage = WM_MESSAGE;		//�Զ������Ϣ����
	m_Tray.hIcon = LoadIcon(m_pWnd->GetpWnd()->hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wsprintf(m_Tray.szTip, TEXT("Time"));

	Shell_NotifyIcon(NIM_ADD, &m_Tray);//�����������ͼ��
}

void TransparentWindow::initFont() {
	//��������
	m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"System");
	m_FontStyle = Font_Style_System;
}

void TransparentWindow::initStatic() {
	m_hStatic = Lin::LinCreateStatic(m_Hwnd, ID_STATIC);

	m_StaticBitmap = LoadBitmap(m_pWnd->GetpWnd()->hInstance, MAKEINTRESOURCE(IDB_Button2));	//����ͼƬ
	//���ı����͸���λͼ��Ϣ
	SendMessage(m_hStatic, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_StaticBitmap);
}

void TransparentWindow::CreateTimer(int _Prop) {
	switch (_Prop) {
		case Timer_SleepDraw:	//��Ļˢ���ʵĶ�ʱ��
			m_SleepDrawTimer->CreateTimer(WAITORTIMERCALLBACK(SleepDraw), this, Sleep_Draw_Static);
			break;
		case Timer_Timer:		//��ʱ���Ķ�ʱ��
			m_Timer->CreateTimer(WAITORTIMERCALLBACK(TimerRoutine), this, Sleep_Timer);
			break;
	}
}


void TransparentWindow::DeleteTimer(int _Prop) {
	switch (_Prop) {
	case Timer_SleepDraw:
		m_SleepDrawTimer->release();
		break;
	case Timer_Timer:
		m_Timer->release();
		break;
	}
}

void TransparentWindow::ChangeTimer(int _Prop, int _dt) {
	switch (_Prop) {
	case Timer_SleepDraw:
		m_SleepDrawTimer->ChangeTimer(_dt);
		break;
	case Timer_Timer:
		m_Timer->ChangeTimer(_dt);
		break;
	}
}

bool TransparentWindow::release() {
	UnregisterClass(WINDOW_TITLE, m_pWnd->GetpWnd()->hInstance);
	DeleteObject(m_hFont);		//�ͷ�������Դ
	DeleteTimer(Timer_SleepDraw);
	DeleteTimer(Timer_Timer);		//ɾ��2����ʱ��
	delete m_pWnd;
	return true;
}

void TransparentWindow::run(HINSTANCE _hInstance) {
	init(_hInstance);
	int isF6Down = 0;
	int isF7Down = 0;
	while (!m_Exit) {
		if (isF6Down && !KEY_DOWM(VK_F6)) {
			OnRButtonDownDouble();
			OnLButtonDownDouble();
		}
		isF6Down = KEY_DOWM(VK_F6);
		if (isF7Down && !KEY_DOWM(VK_F7))
			OnRButtonDownDouble();
		isF7Down = KEY_DOWM(VK_F7);

		dwRet = MsgWaitForMultipleObjects(1, &phWait, FALSE, INFINITE, QS_ALLINPUT);
		switch (dwRet) {
		case WAIT_OBJECT_0: {
			Draw();
			UpData();
		}
		break;
		case WAIT_OBJECT_0 + 1: {
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		break;
		}
	}
}



void TransparentWindow::Draw() {
	if (s_ifUpDate) {
		m_Hdc = GetDC(m_Hwnd);

		//��������
		SelectObject(m_Hdc, m_hFont);
		TextColor();
		SetBkColor(m_Hdc, RGB(0, 0, 0));

		DrawNowTime();		//���Ƶ�ǰʱ��
		DrawUpDateTimer();	//���Ƽ�ʱ��ʱ��

		ReleaseDC(m_Hwnd, m_Hdc);
		s_ifUpDate = false;
	}
}

void TransparentWindow::UpData() {
	MoveTransparentWindow();
}

void TransparentWindow::TextColor() {
	//����������ɫ
	if (m_FontColor == Font_ColorStyle_Green) {
		SetTextColor(m_Hdc, RGB(0, 255, 55));
		m_FontColor = Font_ColorStyle_Green;
	}
	else {
		SetTextColor(m_Hdc, RGB(255, 0, 200));
		m_FontColor = Font_ColorStyle_Purple;
	}
}

void TransparentWindow::DrawNowTime() {
	//���Ƶ�ǰʱ��
	//��ȡʱ��
	time_t time_seconds = time(0);
	tm now_time;
	localtime_s(&now_time, &time_seconds);

	std::wstring hour, min, sec;

	if (now_time.tm_hour < 10)	hour = std::to_wstring(0);
	hour += std::to_wstring(now_time.tm_hour);
	if (now_time.tm_min < 10)	min = std::to_wstring(0);
	min += std::to_wstring(now_time.tm_min);
	if (now_time.tm_sec < 10)	sec = std::to_wstring(0);
	sec += std::to_wstring(now_time.tm_sec);

	std::wstring _str = hour + std::wstring(L":") + min + std::wstring(L":") + sec;

	TextOut(m_Hdc, 0, 30, _str.c_str(), _str.length());
}

void TransparentWindow::DrawUpDateTimer() {
	//���Ƽ�ʱ��ʱ��
	std::wstring time = std::to_wstring(s_TimerNum);
	std::wstring str;
	if (s_TimerNum < 10)	str += std::wstring(L"00");
	else if (s_TimerNum < 100)	str += std::wstring(L"0");
	str += std::to_wstring(s_TimerNum);
	TextOut(m_Hdc, 0, 0, str.c_str(), str.length());
}

void TransparentWindow::MoveTransparentWindow() {
	//����϶����ڣ��޶�����
	if (m_pWnd->GetIfLeftMouseDown()) {
		POINT pt;
		POINT MouseDown = m_pWnd->GetMouseDown();	//��ȡ���������ʱ��λ��
		POINT WindowPoint = m_pWnd->GetWindowPoint();
		GetCursorPos(&pt);		//��ȡ��ǰ����ƶ���λ��
		m_pWnd->SetWindowPoint({ WindowPoint.x += pt.x - MouseDown.x, WindowPoint.y += pt.y - MouseDown.y });
		m_pWnd->SetMouseDown(pt);
		MoveWindow(GetHWND(), WindowPoint.x, WindowPoint.y, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	}
}

void TransparentWindow::ChangeFontColor() {
	//����������ɫ
	if (m_FontColor == Font_ColorStyle_Green)
		m_FontColor = Font_ColorStyle_Purple;
	else
		m_FontColor = Font_ColorStyle_Green;
}

void TransparentWindow::ChangeFont() {
	//��������
	DeleteObject(m_hFont);		//�ͷ�������Դ
	if (m_FontStyle == Font_Style_HT) {
		m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"system");
		m_FontStyle = Font_Style_System;
	}
	else {
		m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"����");
		m_FontStyle = Font_Style_HT;
	}
}

void TransparentWindow::TrayHandleMsg(LPARAM _lParam) {
	switch (_lParam) {
	case WM_LBUTTONDOWN:
		OnTrayLButtonDown();		break;
	case WM_LBUTTONUP:
		OnTrayLButtonUp();			break;
	case WM_RBUTTONDOWN:
		OnTrayRButtonDown();		break;
	case WM_RBUTTONUP:
		OnTrayRButtonUp();			break;
	}
}

void TransparentWindow::TrayHandleMenuMsg(WPARAM _wParam) {
	switch (_wParam) {
		case ID_TRAYMENU_Color:			//������ɫ
			OnTrayMenuColor();		break;
		case ID_TRAYMENU_Font:			//��������
			OnTrayMenuFont();		break;
		case ID_TRAYMENU_PauseTimer:	//��ͣ������
			OnTrayMenuPauseTimer();	break;
		case ID_TRAYMENU_StartTimer:	//��ʼ��ʱ
			OnTrayMenuStartTimer();	break;
		case ID_TRAYMENU_EXIT:			//�˳�
			OnTrayMenuExit();		break;
	}
}







//������������
TransparentWindow::TransparentWindow(int _CmdShow)
	: m_pWnd(NULL), m_CmdShow(_CmdShow), m_Exit(false), m_SleepDrawTimer(NULL), m_Timer(NULL) {

}

TransparentWindow::~TransparentWindow() {
}