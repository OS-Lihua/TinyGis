
// Cyan_DBA_LihuaDoc.h : CCyan_DBA_LihuaDoc 类的接口
//
#ifndef	 _CYAN_DBA_LIHUADOC_
#define  _CYAN_DBA_LIHUADOC_
#pragma once

#include <AfxTempl.h>
#include "Draw.h"
#include "Circle.h"
#include "PLine.h"
#include "Text.h"
#include "ImageCenterDib.h"
#define MAXSize0fArray (4096)

struct GraphSelectStruct
{
	short int Lb;		//类别
	short int Index;	//序号
	short buff;			 //缓冲区长度
	int sumbuf;			 //缓冲区个数
};//用来存储选中图形的数据结构




class CCyan_DBA_LihuaDoc : public CDocument
{
protected: // 仅从序列化创建
	CCyan_DBA_LihuaDoc();
	DECLARE_DYNCREATE(CCyan_DBA_LihuaDoc)

	////////////过筛的工具数组///////////////////
	int* m_index;

	/////////用于图形选择的过筛工具数组///////////////////
	int* select_array;

//三个对象指针的数组
private:
	CTypedPtrArray<CObArray,CCircle*>m_CircleArray;	//管理点对象的指针数组 Lb1
	CTypedPtrArray<CObArray,CPLine*>m_PLineArray;	//管理折线和多边形对象的指针数组 Lb 2
	CTypedPtrArray<CObArray,CText*>m_TextArray;		//管理标注文字对象的指针数组 Lb 3
	

// 特性
public:
	int n_GraphSelect;				//框选数组的大小
	GraphSelectStruct *GraphSelect;	 //框选数组的指针
	ImgCenterDib m_dib;	//声明一个底图变量

// 操作
public:

	///////////////////增加图形元素///////////////////////
	//增加PLine
	CPLine* AddPLine(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
			int m_Numble,PointStruct *m_PointList,int m_Lb);
	//增加Text
	CText* AddText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
			float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text);
	//增加Circle
	CCircle* AddCircle(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,
			float CircleX,float CircleY,float CircleR,short Lb);

	//////////////////获取指针数组中的值//////////////////////
	CDraw* GetGraph(short Lb,int Index);
								    
	//////////////////获取指针数组的最大下标 size -1///////////////////
	int GetGraphUpperBound(short Lb);

	//////////////////获取指针数组的Size(容量)/////////////////////////
	int GetGraphNumb(short Lb);

	/////////////////删除指定数组的指定元素/////////////////////////////
	void DeleteGraph(short Lb,int Index);

	/////////////////清空所有数组///////////////////////////////////////
	void clearAll();

	/////////////////获取指定数组的最小可用ID///////////////////////////
	int GetGraphID(short Lb);

	///////////全图显示////////////
	BOOL GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);

	///////////////////添加到选择列表//////////////////////////
	BOOL AddSelectList(int Lb,int Index);

	///////////////////删除选择列表指定元素//////////////////////////
	void DelSelectList(int Lb,int Index); 

	////////////彻底删除///////
	void OnPack();

	/////////////返回底图变量的首地址////////////
	ImgCenterDib* GetPDib();


// 重写
public:
	virtual BOOL OnNewDocument();
	/////////////存档//////////////////
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCyan_DBA_LihuaDoc();
	////////////////DOC中的Draw///////////////////////////
	virtual void DocDraw(CDC* pDC,int m_DrawMode);
	

	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnLoadbasemap();
};


#endif

//////////////////////////////////////////////////////////
//在此声明全局内容
extern CString name;			//底图名称
extern BOOL isAdd ;				//是否已经添加底图，初始化为未添加底图



////////////////////////////////////////////////////////////////////////