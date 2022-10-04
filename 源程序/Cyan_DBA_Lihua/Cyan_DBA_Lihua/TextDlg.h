#ifndef _TEXTDLG_
#define _TEXTDLG_
#pragma once
#include <iostream>
#include "afxwin.h"

// CTextDlg 对话框

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGText };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//Eidt文本框的文本
	CString m_text;
	//字体高度
	CEdit m_EditHigh;
	UINT m_high;
	//宽度
	UINT m_width;
	//角度
	UINT m_angle;
	//滑块
	CSliderCtrl m_slider;
	int m_weight;	 //粗细
	//画笔颜色		
	COLORREF pColor;
	//滑动滑块事件函数
	afx_msg void OnNMCustomdrawSlidertext(NMHDR *pNMHDR, LRESULT *pResult);
	//在m_EditHigh失去焦点
	afx_msg void OnEnKillfocusEditheight();
};
#endif
