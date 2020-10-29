//����Window������Ϣ
#include "stdafx.h"
#include "TransparentWindow.h"

typedef TransparentWindow TWindow;

//���������Ϣ
void TWindow::OnLButtonDown() {
	TW->ChangeTimer(Timer_SleepDraw, Sleep_Draw_Move);
	TW->m_pWnd->SetIfLeftMouseDown(true);
	POINT pt, WinPt = TW->m_pWnd->GetWindowPoint();
	GetCursorPos(&pt);	//��ȡ��ǰ������������
	TW->m_pWnd->SetMouseDown(pt);
}

//���������Ϣ
void TWindow::OnLButtonUp() {
	TW->m_pWnd->SetIfLeftMouseDown(false);
	TW->m_pWnd->SetMouseDown({ 0 });
	POINT pt;
	GetCursorPos(&pt);	//��ȡ���λ��
	//TW->ChangeSleepDrawTimer(Sleep_Draw_Static);
	TW->ChangeTimer(Timer_SleepDraw, Sleep_Draw_Static);
}

//�Ҽ�������Ϣ
void TWindow::OnRButtonDown() {
}

//�Ҽ�������Ϣ
void TWindow::OnRButtonUp() {
}

//����ƶ�
void TWindow::OnMouseMove() {
}

//���˫��
void TWindow::OnLButtonDownDouble(){
	TW->CreateTimer(Timer_Timer);
}

void TWindow::OnRButtonDownDouble() {
	//��������	��ͣ
	s_TimerNum = 0;
	TW->DeleteTimer(Timer_Timer);
}

//��ý���
void TWindow::OnSetFocus() {
	OutputDebugString(L"��ý���\n");
}

//ʧȥ����
void TWindow::OnKillFocus() {
	OutputDebugString(L"ʧȥ����\n");
}
