//处理托盘消息及托盘菜单消息
#include "stdafx.h"
#include "TransparentWindow.h"
#include "LinAPI.h"
USING_NS_LIN;

typedef TransparentWindow TWindow;


//托盘消息
void TWindow::OnTrayLButtonDown() {
	//OutputDebugString(L"左键按下了托盘图标\n");
	EndMenu();
}
void TWindow::OnTrayLButtonUp() {
	//OutputDebugString(L"左键弹起了托盘图标\n");
}
void TWindow::OnTrayRButtonDown() {
	//OutputDebugString(L"右键按下了托盘图标\n");
	EndMenu();//收起菜单
}
void TWindow::OnTrayRButtonUp() {
	//OutputDebugString(L"右键弹起了托盘图标\n");
	//创建菜单
	HMENU Menu = CreatePopupMenu();
	//为菜单添加选项
	LinWindowAddMenu(Menu, ID_TRAYMENU_Color, L"更换颜色");
	LinWindowAddMenu(Menu, ID_TRAYMENU_Font,  L"更换字体");
	LinWindowAddMenu(Menu, ID_TRAYMENU_StartTimer, L"开始计时");
	LinWindowAddMenu(Menu, ID_TRAYMENU_PauseTimer, L"暂停并重置");
	LinWindowAddMenu(Menu, ID_TRAYMENU_EXIT,  L"退出");
	POINT pt;
	GetCursorPos(&pt);
	TrackPopupMenu(Menu, TPM_LEFTBUTTON | TPM_HORNEGANIMATION, pt.x, pt.y, NULL, TW->GetHWND(), NULL);
	DestroyMenu(Menu);		//用完就释放Menu
}



//托盘菜单消息
void TWindow::OnTrayMenuColor() {
	TW->ChangeFontColor();
}

void TWindow::OnTrayMenuFont() {
	//先刷新屏幕在更换字体
	RedrawWindow(TW->GetHWND(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	TW->ChangeFont();
}

void TWindow::OnTrayMenuPauseTimer() {
	//重置并暂停
	OnRButtonDownDouble();	//相当于双击右键
}

void TWindow::OnTrayMenuStartTimer() {
	//开始计时
	OnLButtonDownDouble();	//相当于双击左键
}

void TWindow::OnTrayMenuExit() {
	Shell_NotifyIcon(NIM_DELETE, GetTransparentWindow()->GetTray());	//删除托盘的图标
	GetTransparentWindow()->SetExit(true);
}