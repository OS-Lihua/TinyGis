// MapMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "MapMessage.h"
#include "afxdialogex.h"


// MapMessage 对话框

IMPLEMENT_DYNAMIC(MapMessage, CDialogEx)

MapMessage::MapMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(MapMessage::IDD, pParent)
	, message(_T(""))
{

}

MapMessage::~MapMessage()
{
}

void MapMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITText, message);
}


BEGIN_MESSAGE_MAP(MapMessage, CDialogEx)
	
END_MESSAGE_MAP()


// MapMessage 消息处理程序


