#pragma once
#include "afxwin.h"


// Position 对话框

class Position : public CDialogEx
{
	DECLARE_DYNAMIC(Position)

public:
	Position(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Position();

// 对话框数据
	enum { IDD = IDD_SelectAddress };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 经度
	CString longitude;

	// 纬度
	CString latitude;
};
