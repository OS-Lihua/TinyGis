#pragma once


// ColorTool 对话框
#include<string.h>

class ColorTool : public CDialogEx
{
	DECLARE_DYNAMIC(ColorTool)

public:
	ColorTool(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ColorTool();

// 对话框数据
	enum { IDD = IDD_DIALOGAttr };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

private:
	//线型
	CComboBox type;
	//Slider
	CSliderCtrl slider;
	

public:
	//数字
	CString num;

	//Slider (Value)
	int m_slider;
	//线型
	short linetype;
	//笔色
	COLORREF penCo1or;
	//画刷色
	COLORREF brushCo1or;
	//画笔
	CPen pen;
	//画刷
	CBrush brush;

	afx_msg void OnBnClickedButtonpen();
	afx_msg void OnBnClickedButtonbrush();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderwide(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
