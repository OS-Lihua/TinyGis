#pragma once


// MapBuffer 对话框

class MapBuffer : public CDialogEx
{
	DECLARE_DYNAMIC(MapBuffer)

public:
	MapBuffer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MapBuffer();

// 对话框数据
	enum { IDD = IDD_BufferSet };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 缓冲区长度
	CString bufferLong;
	// 层数
	CString bufferNumber;
};
