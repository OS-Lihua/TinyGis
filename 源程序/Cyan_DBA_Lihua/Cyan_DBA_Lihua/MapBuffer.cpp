// MapBuffer.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "MapBuffer.h"
#include "afxdialogex.h"


// MapBuffer 对话框

IMPLEMENT_DYNAMIC(MapBuffer, CDialogEx)

MapBuffer::MapBuffer(CWnd* pParent /*=NULL*/)
	: CDialogEx(MapBuffer::IDD, pParent)
	, bufferLong(_T(""))
	, bufferNumber(_T(""))
{

}

MapBuffer::~MapBuffer()
{
}

void MapBuffer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, bufferLong);
	DDX_Text(pDX, IDC_EDIT2, bufferNumber);
}


BEGIN_MESSAGE_MAP(MapBuffer, CDialogEx)
END_MESSAGE_MAP()


// MapBuffer 消息处理程序
