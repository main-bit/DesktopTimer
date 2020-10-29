#include "stdafx.h"
#include "LinAPI.h"



USING_NS_LIN;

void Lin::LinWindowAddMenu(HMENU& _Menu, UINT_PTR _ID, LPCWSTR _str) {
	AppendMenu(_Menu, MF_STRING, _ID, _str);
	AppendMenu(_Menu, MF_SEPARATOR, 0, NULL);

}

void Lin::LinWindowAddBitmapMenu(HMENU& _Menu, UINT_PTR _ID, LPCWSTR _str, HBITMAP& _hbmp) {
	_hbmp = (HBITMAP)LoadImage(NULL, _str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	AppendMenu(_Menu, MF_BITMAP, _ID, (PTSTR)(LONG)_hbmp);
	AppendMenu(_Menu, MF_SEPARATOR, 0, NULL);
}

HWND Lin::LinCreateStatic(HWND _f, int _ID) {
	HWND hStatic = CreateWindow(
		L"Static",
		L"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_CENTERIMAGE,
		52, 8,
		16, 16,
		_f,
		HMENU(_ID),
		(HINSTANCE)GetWindowLong(_f, GWLP_HINSTANCE),
		NULL);
	return hStatic;
}