
// GUIDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGUIDemoApp: 
// �йش����ʵ�֣������ GUIDemo.cpp
//

class CGUIDemoApp : public CWinApp
{
public:
	CGUIDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGUIDemoApp theApp;