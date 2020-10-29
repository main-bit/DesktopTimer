#pragma once
#ifdef VARIOUS_EXPORTS
#define DLLEXAM_API __declspec(dllexport)
#else
#define DLLEXAM_API __declspec(dllimport)
#endif

#ifndef VARIOUS_H
#define VARIOUS_H

#include "stdafx.h"
#include <Windows.h>
#include <string>


//ʵ�ַ�����
#define LIN_GET(Param, Type,FunName)\
Type Get##FunName (void) {return Param;}

#define LIN_SET(Param, Type, FunName)\
void Set##FunName (Type _type){Param = _type;}

#define LIN_GET_AND_SET(Param, Type, FunName)\
Type Get##FunName (void) {return Param;} void Set##FunName (Type _type){Param = _type;}


//����
class DLLEXAM_API Lin_Window {
private:
	WNDCLASSEX m_WndClass;		//���ڽṹ��
	std::wstring m_WndName;		//��������
	POINT m_WindowPoint;		//����λ��
	POINT m_MouseDown;			//���������ʱ��λ��
	bool m_IfLeftMouseDown;		//�������Ƿ���
	RECT m_WinSize;				//���洰�ڳߴ�
public:
	LIN_GET(&m_WndClass, PWNDCLASSEX, pWnd);
	LIN_GET_AND_SET(m_WindowPoint, POINT, WindowPoint);
	LIN_GET(m_WndName, std::wstring, WndName);
	LIN_GET_AND_SET(m_MouseDown, POINT, MouseDown);
	LIN_GET_AND_SET(m_IfLeftMouseDown, bool, IfLeftMouseDown);
	LIN_GET_AND_SET(m_WinSize, RECT, WinSize);

	Lin_Window(LPCWSTR _name) :m_WndName(_name) {}
	~Lin_Window() {}
};


//��ʱ��
class DLLEXAM_API Lin_Timer {
private:
	HANDLE m_Timer;
	HANDLE m_QueueTimer;
public:
	void init();
	void release();

	void CreateTimer(WAITORTIMERCALLBACK _CallBack, PVOID _this, int _dt);
	void ChangeTimer(int _dt);

	static Lin_Timer* create();


	Lin_Timer() {};
	~Lin_Timer() {};
};


//����
class DLLEXAM_API Lin_Font {
private:
	HFONT m_hFont;
	int m_Height;
public:
	void init(LPCWSTR, int);
	void release();

	void TextColor(HDC, COLORREF);	//�������������ɫ
	void SetStyle(LPCWSTR);			//������������


	static Lin_Font* create(LPCWSTR _Name, int _Height);

	Lin_Font() {};
	~Lin_Font() {};
};

#endif