#ifndef _LOGININTERFACE_
#define _LOGININTERFACE_
#pragma once


// LoginInterface 对话框

class LoginInterface : public CDialogEx
{
	DECLARE_DYNAMIC(LoginInterface)

public:
	LoginInterface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginInterface();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 账号
	CString account;
	// 密码
	CString password;
	afx_msg void OnBnClickedOk();
	HICON m_hIcon;
	int OnNO();

};


#endif