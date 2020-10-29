//����������Ϣ�����̲˵���Ϣ
#include "stdafx.h"
#include "TransparentWindow.h"
#include "LinAPI.h"
USING_NS_LIN;

typedef TransparentWindow TWindow;


//������Ϣ
void TWindow::OnTrayLButtonDown() {
	//OutputDebugString(L"�������������ͼ��\n");
	EndMenu();
}
void TWindow::OnTrayLButtonUp() {
	//OutputDebugString(L"�������������ͼ��\n");
}
void TWindow::OnTrayRButtonDown() {
	//OutputDebugString(L"�Ҽ�����������ͼ��\n");
	EndMenu();//����˵�
}
void TWindow::OnTrayRButtonUp() {
	//OutputDebugString(L"�Ҽ�����������ͼ��\n");
	//�����˵�
	HMENU Menu = CreatePopupMenu();
	//Ϊ�˵����ѡ��
	LinWindowAddMenu(Menu, ID_TRAYMENU_Color, L"������ɫ");
	LinWindowAddMenu(Menu, ID_TRAYMENU_Font,  L"��������");
	LinWindowAddMenu(Menu, ID_TRAYMENU_StartTimer, L"��ʼ��ʱ");
	LinWindowAddMenu(Menu, ID_TRAYMENU_PauseTimer, L"��ͣ������");
	LinWindowAddMenu(Menu, ID_TRAYMENU_EXIT,  L"�˳�");
	POINT pt;
	GetCursorPos(&pt);
	TrackPopupMenu(Menu, TPM_LEFTBUTTON | TPM_HORNEGANIMATION, pt.x, pt.y, NULL, TW->GetHWND(), NULL);
	DestroyMenu(Menu);		//������ͷ�Menu
}



//���̲˵���Ϣ
void TWindow::OnTrayMenuColor() {
	TW->ChangeFontColor();
}

void TWindow::OnTrayMenuFont() {
	//��ˢ����Ļ�ڸ�������
	RedrawWindow(TW->GetHWND(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	TW->ChangeFont();
}

void TWindow::OnTrayMenuPauseTimer() {
	//���ò���ͣ
	OnRButtonDownDouble();	//�൱��˫���Ҽ�
}

void TWindow::OnTrayMenuStartTimer() {
	//��ʼ��ʱ
	OnLButtonDownDouble();	//�൱��˫�����
}

void TWindow::OnTrayMenuExit() {
	Shell_NotifyIcon(NIM_DELETE, GetTransparentWindow()->GetTray());	//ɾ�����̵�ͼ��
	GetTransparentWindow()->SetExit(true);
}