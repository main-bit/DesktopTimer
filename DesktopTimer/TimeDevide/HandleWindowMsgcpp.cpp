//处理Window窗口消息
#include "stdafx.h"
#include "TransparentWindow.h"

typedef TransparentWindow TWindow;

//左键按下消息
void TWindow::OnLButtonDown() {
	TW->ChangeTimer(Timer_SleepDraw, Sleep_Draw_Move);
	TW->m_pWnd->SetIfLeftMouseDown(true);
	POINT pt, WinPt = TW->m_pWnd->GetWindowPoint();
	GetCursorPos(&pt);	//获取当前左键点击的坐标
	TW->m_pWnd->SetMouseDown(pt);
}

//左键弹起消息
void TWindow::OnLButtonUp() {
	TW->m_pWnd->SetIfLeftMouseDown(false);
	TW->m_pWnd->SetMouseDown({ 0 });
	POINT pt;
	GetCursorPos(&pt);	//获取鼠标位置
	//TW->ChangeSleepDrawTimer(Sleep_Draw_Static);
	TW->ChangeTimer(Timer_SleepDraw, Sleep_Draw_Static);
}

//右键按下消息
void TWindow::OnRButtonDown() {
}

//右键弹起消息
void TWindow::OnRButtonUp() {
}

//鼠标移动
void TWindow::OnMouseMove() {
}

//左键双击
void TWindow::OnLButtonDownDouble(){
	TW->CreateTimer(Timer_Timer);
}

void TWindow::OnRButtonDownDouble() {
	//计数清零	暂停
	s_TimerNum = 0;
	TW->DeleteTimer(Timer_Timer);
}

//获得焦点
void TWindow::OnSetFocus() {
	OutputDebugString(L"获得焦点\n");
}

//失去焦点
void TWindow::OnKillFocus() {
	OutputDebugString(L"失去焦点\n");
}
