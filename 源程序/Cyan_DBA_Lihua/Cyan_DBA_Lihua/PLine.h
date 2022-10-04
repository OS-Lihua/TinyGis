#ifndef _PLINE_
#define _PLINE_
#pragma once
#include "draw.h"



class CPLine :
	public CDraw
{
public:
	DECLARE_SERIAL (CPLine)
	CPLine(void);
	//构造函数
	CPLine(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			int m_Numble,PointStruct *m_PointList,int m_Lb);
	//////////////绘制折线，多边形////////////////
	void Draw(CDC *pDC,int Mode,int length = 0,int index =0);
	~CPLine(void);
	//////确定外接矩形坐标的最值//////////
	void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);
	////////////存档//////////////////
	void Serialize(CArchive& ar);
	/////////点选////////////////
	bool IsPoint(CDC *pDC,float px,float py);
	/////////框选////////////////
	bool IsRect(CDC *pDC,CRect rect);

protected:
	//连续直线或者多边形区域的顶点数目
	int m_Numble;
	//表示是否填充 类别
	int m_Lb;
	//存储顶点坐标的数组指针(数组) 
	PointStruct *m_PointList;
};
#endif

