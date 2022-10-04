
// Cyan_DBA_Lihua.h : Cyan_DBA_Lihua 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "LoginInterface.h"


// CCyan_DBA_LihuaApp:
// 有关此类的实现，请参阅 Cyan_DBA_Lihua.cpp
//

class CCyan_DBA_LihuaApp : public CWinAppEx
{
public:
	CCyan_DBA_LihuaApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCyan_DBA_LihuaApp theApp;
