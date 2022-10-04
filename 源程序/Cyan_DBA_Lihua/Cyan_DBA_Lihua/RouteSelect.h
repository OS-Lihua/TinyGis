#ifndef _ROUTESELECT_
#define _ROUTESELECT_
#pragma once
#include "afxwin.h"

// RouteSelect 对话框

class RouteSelect : public CDialogEx
{
	DECLARE_DYNAMIC(RouteSelect)

public:
	RouteSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RouteSelect();
	
// 对话框数据
	enum { IDD = IDD_DIALOGSelect };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 查找的index的字符字面量
	CString m_index;
};
#endif
