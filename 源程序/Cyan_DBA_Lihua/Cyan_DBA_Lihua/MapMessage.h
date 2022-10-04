#ifndef _MAPMESSAGE_
#define _MAPMESSAGE_
#pragma once


// MapMessage 对话框

class MapMessage : public CDialogEx
{
	DECLARE_DYNAMIC(MapMessage)

public:
	MapMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MapMessage();

// 对话框数据
	enum { IDD = IDD_DIALOGMessage };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	// 输入框控件的值
	CString message;
};
#endif
