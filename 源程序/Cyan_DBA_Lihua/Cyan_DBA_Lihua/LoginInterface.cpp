// LoginInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "LoginInterface.h"
#include "afxdialogex.h"


// LoginInterface 对话框

IMPLEMENT_DYNAMIC(LoginInterface, CDialogEx)

LoginInterface::LoginInterface(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoginInterface::IDD, pParent)
	, account(_T(""))
	, password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

LoginInterface::~LoginInterface()
{
}

void LoginInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, account);
	DDX_Text(pDX, IDC_EDIT2, password);
}


BEGIN_MESSAGE_MAP(LoginInterface, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoginInterface::OnBnClickedOk)
END_MESSAGE_MAP()


// LoginInterface 消息处理程序


void LoginInterface::OnBnClickedOk()
{
	this->UpdateData();
	if(this->password==("2333")&&this->account==("9527"))
	{
		MessageBox(_T("用户9527"),_T("登录成功"),MB_OK);
		CDialogEx::OnOK();

	}
	else if(this->password==("lihua666")&&this->account==("26346"))
	{
		MessageBox(_T("用户:Lihua"),_T("登录成功"),MB_OK);
		CDialogEx::OnOK();
	}
	else if(this->password==("06010127")&&this->account==("15039"))
	{
		MessageBox(_T("用户:张柳青"),_T("登录成功"),MB_OK);
		CDialogEx::OnOK();
	}
	else if(this->password==("258080")&&this->account==("258080"))
	{
		MessageBox(_T("用户:王彤老师"),_T("老师好"),MB_OK);
		CDialogEx::OnOK();
	}
	else

	{
		MessageBox(_T("用户名或密码错误"),_T("登录失败"),MB_ICONERROR|MB_OK);
		//password= "";
		//account= "";
		//UpdateData();
		//this->DoModal();
		//CDialogEx::OnYes();
		OnNO();
		//exit(1);
	}
	// TODO: 在此添加控件通知处理程序代码
	
}

int LoginInterface::OnNO()
{
	return IDNO;
}
