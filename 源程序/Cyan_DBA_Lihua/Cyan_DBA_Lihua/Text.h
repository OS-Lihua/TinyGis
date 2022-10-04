#ifndef _TEXT_
#define _TEXT_

#pragma once
#include "draw.h"
#include <math.h>
#include <limits>



#define pi (3.14159265358)
class CText :
	public CDraw
{
DECLARE_SERIAL (CText)
public:
	CText(void);
	//构造函数
	CText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text);
	~CText(void);

	/////////////////////////
	//////绘制文字///////////
	void Draw(CDC *pDC,int Mode,int length = 0,int index = 0);
	////////////存档//////////////////
	void Serialize(CArchive& ar);
	//////确定文字(外接矩形坐标)的最值//////////
	void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);
	/////////点选////////////////
	bool IsPoint(CDC *pDC,float px,float py);
	///////////框选///////////////////////////
	bool IsRect(CDC *pDC,CRect rect);

protected:

	//文本起点横坐标
	float m_StartX;
	//起点纵坐标
	float m_StartY;
	//标注角度
	float m_Angle;
	//字体高度
	float m_TextHeight;
	//字体宽度
	float m_TextWide;
	//粗细程度
	float m_FontWeight;
	//标注的文本信息
	CString m_Text;
	//标注信息的长度 文本字符个数 
	int m_TextLong;		   //用法 :  m_TextLong= m_Text.GetLength();

};

#endif

