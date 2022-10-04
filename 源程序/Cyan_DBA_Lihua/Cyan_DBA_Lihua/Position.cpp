// Position.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "Position.h"
#include "afxdialogex.h"


// Position 对话框

IMPLEMENT_DYNAMIC(Position, CDialogEx)

Position::Position(CWnd* pParent /*=NULL*/)
	: CDialogEx(Position::IDD, pParent)
	, longitude(_T(""))
	, latitude(_T(""))
{

}

Position::~Position()
{
}

void Position::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, longitude);
	DDX_Text(pDX, IDC_EDIT2, latitude);
}


BEGIN_MESSAGE_MAP(Position, CDialogEx)
END_MESSAGE_MAP()


// Position 消息处理程序
