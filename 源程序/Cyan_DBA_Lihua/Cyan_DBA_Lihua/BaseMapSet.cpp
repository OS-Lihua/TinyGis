// BaseMapSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "BaseMapSet.h"
#include "afxdialogex.h"


// BaseMapSet 对话框

IMPLEMENT_DYNAMIC(BaseMapSet, CDialogEx)

BaseMapSet::BaseMapSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(BaseMapSet::IDD, pParent)
	, minLongitude(_T(""))
	, maxLongitude(_T(""))
	, minLatitude(_T(""))
	, maxLatitude(_T(""))
	, d1(_T(""))
	, f1(_T(""))
	, m1(_T(""))
	, d2(_T(""))
	, f2(_T(""))
	, m2(_T(""))
	, d3(_T(""))
	, f3(_T(""))
	, m3(_T(""))
	, d4(_T(""))
	, f4(_T(""))
	, m4(_T(""))
{

}

BaseMapSet::~BaseMapSet()
{
}

void BaseMapSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MinLongitude, minLongitude);
	DDX_Text(pDX, IDC_MinLatitude, minLatitude);
	DDX_Text(pDX, IDC_MaxLongitude, maxLongitude);
	DDX_Text(pDX, IDC_MaxLatitude, maxLatitude);
	DDX_Text(pDX, IDC_EDIT1, d1);
	DDX_Text(pDX, IDC_EDIT5, f1);
	DDX_Text(pDX, IDC_EDIT9, m1);
	DDX_Text(pDX, IDC_EDIT2, d2);
	DDX_Text(pDX, IDC_EDIT6, f2);
	DDX_Text(pDX, IDC_EDIT10, m2);
	DDX_Text(pDX, IDC_EDIT3, d3);
	DDX_Text(pDX, IDC_EDIT7, f3);
	DDX_Text(pDX, IDC_EDIT11, m3);
	DDX_Text(pDX, IDC_EDIT4, d4);
	DDX_Text(pDX, IDC_EDIT8, f4);
	DDX_Text(pDX, IDC_EDIT12, m4);
}


BEGIN_MESSAGE_MAP(BaseMapSet, CDialogEx)
END_MESSAGE_MAP()


// BaseMapSet 消息处理程序
