#pragma once


// BaseMapSet 对话框

class BaseMapSet : public CDialogEx
{
	DECLARE_DYNAMIC(BaseMapSet)

public:
	BaseMapSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BaseMapSet();

// 对话框数据
	enum { IDD = IDD_BaseMapSet };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// //最小经度名称
	CString minLongitude;

	CString d1;
	CString f1;
	CString m1;

	// 最小纬度名称
	CString minLatitude;

	CString d2;
	CString f2;
	CString m2;

	// 最大经度名称
	CString maxLongitude;

	CString d3;
	CString f3;
	CString m3;
	// 最大纬度名称 
	CString maxLatitude;

	CString d4;
	CString f4;
	CString m4;
};
