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

#define WINDOW_TITLE	L"TransparentWindow"	//窗口类名
#define WINDOW_POINT_X	600
#define WINDOW_POINT_Y	300
#define WINDOW_WIDTH	170
#define WINDOW_HEIGHT	60

#define WM_MESSAGE	WM_USER + 1
#define ID_TRAY			1	//托盘ID
#define ID_STATIC		2	//文本ID

//托盘菜单
#define ID_TRAYMENU_EXIT		301		//退出
#define ID_TRAYMENU_Color		302		//更换颜色
#define ID_TRAYMENU_Font		303		//更换字体
#define ID_TRAYMENU_PauseTimer	304		//重置并暂停计时
#define ID_TRAYMENU_StartTimer	305		//开始计时
#define ID_ALL_TRAYMENU(_ID)\
	_ID==ID_TRAYMENU_EXIT?1:0 || _ID==ID_TRAYMENU_Color?1:0 || _ID==ID_TRAYMENU_Font?1:0 || _ID==ID_TRAYMENU_PauseTimer?1:0\
	|| _ID==ID_TRAYMENU_StartTimer?1:0

#define TransparentRBG	RGB(0,0,0)	//需要透明的rgb值

#define Sleep_Draw_Move		70		//绘制速率（窗口运动时）
#define Sleep_Draw_Static	200		//绘制速率（窗口静止时）
#define Sleep_Timer			1000	//计时器定时

//定时器区分ID
#define Timer_SleepDraw		1		//窗口刷新率的计时器
#define Timer_Timer			2		//计时器的定时器

//字体款式
#define Font_Style_HT			1	//黑体
#define Font_Style_System		2	//系统字体
//字体颜色款式
#define Font_ColorStyle_Green	1	//绿色
#define Font_ColorStyle_Purple	2	//紫色

#define KEY_DOWM(vk_c) (GetAsyncKeyState(vk_c)&0x8000?1:0)

class TransparentWindow {
public:
	static TransparentWindow* TW;
private:
	Lin_Window* m_pWnd;
	int m_CmdShow;
	HWND m_Hwnd;
	HDC m_Hdc;
	//定时器(窗口响应方面)
	HANDLE phWait;
	LARGE_INTEGER liDueTime;
	//定时器(刷新率绘制方面)
	Lin_Timer* m_SleepDrawTimer;
	//定时器(计时器绘制方面)
	Lin_Timer* m_Timer;
	DWORD dwRet;
	NOTIFYICONDATA m_Tray;		//托盘结构体
	bool m_Exit;				//是否退出

	//字体
	HFONT m_hFont;
	int m_FontStyle;			//字体款式
	int m_FontColor;			//字体颜色
	//静态文本
	HWND m_hStatic;
	HBITMAP m_StaticBitmap;		//图片位图

	static bool s_ifUpDate;		//定时器是否更新
	static int s_TimerNum;		//计时器计数 从000到999

private:
	void initWin(HINSTANCE);
	void initLin_Window();
	void initWndTimer();
	void initTimer();			//初始化2个定时器
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
	
	void TextColor();			//设置字体颜色
	void DrawNowTime();			//绘制当前时间
	void DrawUpDateTimer();		//绘制计时器

	//辅助函数
	void MoveTransparentWindow();
	void ChangeFontColor();	//更换字体颜色
	void ChangeFont();		//更换字体
public:
	TransparentWindow(int);
	~TransparentWindow();

	static TransparentWindow* create(HINSTANCE, int);
	static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);	//窗口过程函数
	static void TrayHandleMsg(LPARAM);
	static void TrayHandleMenuMsg(WPARAM);
	static VOID CALLBACK SleepDraw(PVOID, BOOLEAN);
	static VOID CALLBACK TimerRoutine(PVOID, BOOLEAN);

	//访问器
	static void SetTransparentWindow(TransparentWindow* _TW) { TW = _TW; }
	static TransparentWindow* GetTransparentWindow() { return TW; }
	LIN_GET(m_Hwnd, HWND, HWND);
	LIN_GET(&m_Tray, NOTIFYICONDATA*, Tray);
	LIN_GET_AND_SET(m_Exit, bool, Exit);
	LIN_GET_AND_SET(m_FontStyle, int, FontStyle);

private:
#define LIN_SV static void
	//以下为Windows窗口事件
	LIN_SV OnLButtonDown();
	LIN_SV OnLButtonUp();
	LIN_SV OnRButtonDown();
	LIN_SV OnRButtonUp();
	LIN_SV OnMouseMove();
	LIN_SV OnLButtonDownDouble();	//左键双击
	LIN_SV OnRButtonDownDouble();	//右键双击
	///获得/失去焦点
	LIN_SV OnSetFocus();
	LIN_SV OnKillFocus();


	//以下为托盘事件
	LIN_SV OnTrayLButtonDown();
	LIN_SV OnTrayLButtonUp();
	LIN_SV OnTrayRButtonDown();
	LIN_SV OnTrayRButtonUp();


	//以下为托盘菜单事件
	LIN_SV OnTrayMenuColor();
	LIN_SV OnTrayMenuFont();
	LIN_SV OnTrayMenuStartTimer();
	LIN_SV OnTrayMenuPauseTimer();
	LIN_SV OnTrayMenuExit();
#undef LIN_SV
};

#endif