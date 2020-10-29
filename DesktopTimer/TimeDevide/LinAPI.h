#pragma once
#ifndef LINAPI_H
#define LINAPI_H
#include <string>
#include <Windows.h>

#define USING_NS_LIN	using namespace Lin

//实现访问器
#define LIN_GET(Param, Type,FunName)\
Type Get##FunName (void) {return Param;}

#define LIN_SET(Param, Type, FunName)\
void Set##FunName (Type _type){Param = _type;}

#define LIN_GET_AND_SET(Param, Type, FunName)\
Type Get##FunName (void) {return Param;} void Set##FunName (Type _type){Param = _type;}


namespace Lin {
	struct LinSize {
		int m_Width;
		int m_Height;
		LinSize(int _W, int _H) : m_Width(_W), m_Height(_H) { }
	};
	void LinWindowAddMenu(HMENU&, UINT_PTR, LPCWSTR);
	void LinWindowAddBitmapMenu(HMENU&, UINT_PTR, LPCWSTR, HBITMAP&);
	HWND LinCreateStatic(HWND _f, int _ID);	//创建静态文本
}


#endif