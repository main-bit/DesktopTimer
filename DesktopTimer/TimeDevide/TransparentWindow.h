#pragma once
#ifndef TRANSPARENTWINDOW_H
#define TRANSPARENTWINDOW_H

#include "stdafx.h"
#include <Windows.h>
#include "LinAPI.h"
#include <dwmapi.h>
#include <shellapi.h>
#include "lib/various.h"

//#pragma comment(lib,"Dwmapi.lib")
//#pragma comment(lib,"MSIMG32.lib")

#define WINDOW_TITLE	L"TransparentWindow"	//��������
#define WINDOW_POINT_X	600
#define WINDOW_POINT_Y	300
#define WINDOW_WIDTH	170
#define WINDOW_HEIGHT	60

#define WM_MESSAGE	WM_USER + 1
#define ID_TRAY			1	//����ID
#define ID_STATIC		2	//�ı�ID

//���̲˵�
#define ID_TRAYMENU_EXIT		301		//�˳�
#define ID_TRAYMENU_Color		302		//������ɫ
#define ID_TRAYMENU_Font		303		//��������
#define ID_TRAYMENU_PauseTimer	304		//���ò���ͣ��ʱ
#define ID_TRAYMENU_StartTimer	305		//��ʼ��ʱ
#define ID_ALL_TRAYMENU(_ID)\
	_ID==ID_TRAYMENU_EXIT?1:0 || _ID==ID_TRAYMENU_Color?1:0 || _ID==ID_TRAYMENU_Font?1:0 || _ID==ID_TRAYMENU_PauseTimer?1:0\
	|| _ID==ID_TRAYMENU_StartTimer?1:0

#define TransparentRBG	RGB(0,0,0)	//��Ҫ͸����rgbֵ

#define Sleep_Draw_Move		70		//�������ʣ������˶�ʱ��
#define Sleep_Draw_Static	200		//�������ʣ����ھ�ֹʱ��
#define Sleep_Timer			1000	//��ʱ����ʱ

//��ʱ������ID
#define Timer_SleepDraw		1		//����ˢ���ʵļ�ʱ��
#define Timer_Timer			2		//��ʱ���Ķ�ʱ��

//�����ʽ
#define Font_Style_HT			1	//����
#define Font_Style_System		2	//ϵͳ����
//������ɫ��ʽ
#define Font_ColorStyle_Green	1	//��ɫ
#define Font_ColorStyle_Purple	2	//��ɫ

#define KEY_DOWM(vk_c) (GetAsyncKeyState(vk_c)&0x8000?1:0)

class TransparentWindow {
public:
	static TransparentWindow* TW;
private:
	Lin_Window* m_pWnd;
	int m_CmdShow;
	HWND m_Hwnd;
	HDC m_Hdc;
	//��ʱ��(������Ӧ����)
	HANDLE phWait;
	LARGE_INTEGER liDueTime;
	//��ʱ��(ˢ���ʻ��Ʒ���)
	Lin_Timer* m_SleepDrawTimer;
	//��ʱ��(��ʱ�����Ʒ���)
	Lin_Timer* m_Timer;
	DWORD dwRet;
	NOTIFYICONDATA m_Tray;		//���̽ṹ��
	bool m_Exit;				//�Ƿ��˳�

	//����
	HFONT m_hFont;
	int m_FontStyle;			//�����ʽ
	int m_FontColor;			//������ɫ
	//��̬�ı�
	HWND m_hStatic;
	HBITMAP m_StaticBitmap;		//ͼƬλͼ

	static bool s_ifUpDate;		//��ʱ���Ƿ����
	static int s_TimerNum;		//��ʱ������ ��000��999

private:
	void initWin(HINSTANCE);
	void initLin_Window();
	void initWndTimer();
	void initTimer();			//��ʼ��2����ʱ��
	void initTray();
	void initFont();
	void initStatic();

	void CreateTimer(int _Prop);
	void DeleteTimer(int _Prop);
	void ChangeTimer(int _Prop, int _dt);
public:
	bool init(HINSTANCE);
	bool release();

	void run(HINSTANCE);
	void Draw();
	void UpData();
	
	void TextColor();			//����������ɫ
	void DrawNowTime();			//���Ƶ�ǰʱ��
	void DrawUpDateTimer();		//���Ƽ�ʱ��

	//��������
	void MoveTransparentWindow();
	void ChangeFontColor();	//����������ɫ
	void ChangeFont();		//��������
public:
	TransparentWindow(int);
	~TransparentWindow();

	static TransparentWindow* create(HINSTANCE, int);
	static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);	//���ڹ��̺���
	static void TrayHandleMsg(LPARAM);
	static void TrayHandleMenuMsg(WPARAM);
	static VOID CALLBACK SleepDraw(PVOID, BOOLEAN);
	static VOID CALLBACK TimerRoutine(PVOID, BOOLEAN);

	//������
	static void SetTransparentWindow(TransparentWindow* _TW) { TW = _TW; }
	static TransparentWindow* GetTransparentWindow() { return TW; }
	LIN_GET(m_Hwnd, HWND, HWND);
	LIN_GET(&m_Tray, NOTIFYICONDATA*, Tray);
	LIN_GET_AND_SET(m_Exit, bool, Exit);
	LIN_GET_AND_SET(m_FontStyle, int, FontStyle);

private:
#define LIN_SV static void
	//����ΪWindows�����¼�
	LIN_SV OnLButtonDown();
	LIN_SV OnLButtonUp();
	LIN_SV OnRButtonDown();
	LIN_SV OnRButtonUp();
	LIN_SV OnMouseMove();
	LIN_SV OnLButtonDownDouble();	//���˫��
	LIN_SV OnRButtonDownDouble();	//�Ҽ�˫��
	///���/ʧȥ����
	LIN_SV OnSetFocus();
	LIN_SV OnKillFocus();


	//����Ϊ�����¼�
	LIN_SV OnTrayLButtonDown();
	LIN_SV OnTrayLButtonUp();
	LIN_SV OnTrayRButtonDown();
	LIN_SV OnTrayRButtonUp();


	//����Ϊ���̲˵��¼�
	LIN_SV OnTrayMenuColor();
	LIN_SV OnTrayMenuFont();
	LIN_SV OnTrayMenuStartTimer();
	LIN_SV OnTrayMenuPauseTimer();
	LIN_SV OnTrayMenuExit();
#undef LIN_SV
};

#endif