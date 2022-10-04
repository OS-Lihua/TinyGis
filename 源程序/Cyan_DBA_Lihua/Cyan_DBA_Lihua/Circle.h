#pragma once
#include "draw.h"
#include <math.h>




class CCircle :
	public CDraw
{
public:
	DECLARE_SERIAL (CCircle)
	CCircle(void);

	//构造函数
	CCircle(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_CircleX,float m_CircleY,float m_CircleR,short m_Lb);
	/////////////绘制圆/////////////////////
	void Draw(CDC *pDC,int Mode,int length = 0,int index =0);
	~CCircle(void);
	////////////存档//////////////////
	void Serialize(CArchive& ar);
	//////确定外接矩形坐标的最值//////////
	void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);
	///////////点选 ///////////////////////////
	bool IsPoint(CDC *pDC,float px,float py);
	///////////框选///////////////////////////
	bool IsRect(CDC *pDC,CRect rect);
protected:
	//圆心坐标(X,Y)
	float m_CircleX ,m_CircleY;
	//半径
	float m_CircleR;
	//类别
	short m_Lb;
};

