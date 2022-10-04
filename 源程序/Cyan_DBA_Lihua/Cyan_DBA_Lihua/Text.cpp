#include "StdAfx.h"
#include "Text.h"
#include "Draw.h"
IMPLEMENT_SERIAL (CText,CObject,1)
CText::CText(void)
{
}
 //	float m_StartX,float m_StartY ,m_TextHeight,m_TextWide,m_FontWeight  传入时为实际(地球)坐标
CText::CText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text): CDraw(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,b_Delete)
{
	this->m_StartX = m_StartX;
	this->m_StartY = m_StartY;
	this->m_Angle = m_Angle;
	this->m_TextHeight = m_TextHeight;
	this->m_TextWide = m_TextWide;
	this->m_FontWeight = m_FontWeight;
	this->m_TextLong = m_Text.GetLength();			//获取标注信息的长度
	this->m_Text = m_Text;
	
}


CText::~CText(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////绘制文字///////////
void CText::Draw(CDC *pDC,int Mode,int length,int index)
{
	if(this->b_Delete)
	{
		return ;
	}
	//设定覆盖的绘制模式
	pDC->SetROP2(R2_COPYPEN);
	//设置文字的背景为空	/不透明
	pDC->SetBkMode(TRANSPARENT);
	CFont myFont; //定义一个字体模板
	int high,wide,weight,x,y,angleText;	//转化成10被角度方便传参
	float x1,y1,angleLine;
	//if(high<3||high>200) return;	//字体太大或太小则不显示
	high = DLtoVL(this->m_TextHeight);
	wide = DLtoVL(this->m_TextWide)/2;
	weight = DLtoVL(this->m_FontWeight);
	angleLine = (float)(this->m_Angle*pi/180);	//转化成弧度
	////点击位置为左下角实际坐标//////////////
	//先变成左上角，然后进行实际转逻辑
	x1 = this->m_StartX - this->m_TextHeight*(float)sin(angleLine);
	y1 = this->m_StartY + this->m_TextHeight*(float)cos(angleLine);
	/////////////逻辑（像素坐标内部进行转换,倾斜转换）/////
	angleText = (int)(this->m_Angle*10);
	//wide =this->m_TextWide;
	//x0 =x1;
	//y0 =y1;
	/////////文字坐标转换，实际转逻辑///////////	
	DPtoVP(x1,y1,&x,&y);			  //坐标转换
	///////////////////////////////


	myFont.CreateFont(high,wide,angleText,0,weight,0,0,0,1,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,_T("myfont"));
	CFont* font = pDC->SelectObject(&myFont);
	if(Mode ==1)
	{
		pDC->SetBkMode(OPAQUE);		//高亮
		pDC->SetBkColor(RGB(0,191,255));	//天蓝色     //天蓝色RGB(0,191,255)
	}
	pDC->SetTextColor(this->m_ColorPen);
	pDC->TextOutW(x,y,this->m_Text);	//x,y是文字左上角的点
	pDC->SelectObject(font);	//恢复字体模板


}

//////确定文字(外接矩形坐标)的最值//////////
void CText::GetRect(float* m_Xmin,float* m_Ymin,float* m_Xmax,float* m_Ymax)
{
	 float x[4],y[4];
	 double angle = this->m_Angle* pi /180;
	 x[0] = this->m_StartX;
	 y[0] = this->m_StartY;
	 x[1] = this->m_StartX + this->m_TextWide*this->m_TextLong*(float)cos(angle);
	 y[1] = this->m_StartY + this->m_TextWide*this->m_TextLong*(float)sin(angle);
	 x[2] =	x[1] - this->m_TextHeight*(float)sin(angle); 
	 y[2] =	y[1] + this->m_TextHeight*(float)cos(angle);
	 x[3] = this->m_StartX - this->m_TextHeight*(float)sin(angle);
	 y[3] =	this->m_StartY + this->m_TextHeight*(float)cos(angle);
	 *m_Xmin = FLT_MAX;		//最小的给最大值
	 *m_Ymin = FLT_MAX;
	 *m_Xmax = FLT_MIN;		//最大的给最小值
	 *m_Ymax = FLT_MIN;
	 for(int i =0;i<4;++i)
	 {
		//获取最小坐标
		*m_Xmin =min(*m_Xmin,x[i]);
		*m_Ymin =min(*m_Ymin,y[i]);
		//获取最大坐标
		*m_Xmax =max(*m_Xmax,x[i]);
		*m_Ymax =max(*m_Ymax,y[i]);

	 }
}



////////////存档//////////////////
void CText::Serialize(CArchive& ar)
{
	CDraw::Serialize( ar );
	if(ar.IsStoring())
	{
		ar << m_StartX << m_StartY << m_Angle << m_TextHeight << m_TextWide<< m_FontWeight << m_Text;
	}else
	{
		ar >> m_StartX >> m_StartY >> m_Angle >> m_TextHeight >> m_TextWide>> m_FontWeight >> m_Text;
	}
}



//////////点选////////////////
bool CText::IsPoint(CDC *pDC,float px,float py)
{
	if(this->b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	float x1,y1,x2,y2;
	int x3,y3,x4,y4;
	int i ;
	GetRect(&x1,&y1,&x2,&y2);
	DPtoVP(x1,y1,&x3,&y3);
	DPtoVP(x2,y2,&x4,&y4);
	rgn.CreateRectRgn(x3,y3,x4,y4);
	i = rgn.PtInRegion(px,py);
	rgn.DeleteObject();
	return i;
}


///////////框选///////////////////////////
bool CText::IsRect(CDC *pDC,CRect rect)
{
   if(this->b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	float x1,y1,x2,y2;
	int x3,y3,x4,y4;
	int i ;
	GetRect(&x1,&y1,&x2,&y2);
	DPtoVP(x1,y1,&x3,&y3);
	DPtoVP(x2,y2,&x4,&y4);
	rgn.CreateRectRgn(x3,y3,x4,y4);
	i=rgn.RectInRegion(&rect);	
	rgn.DeleteObject();
	return i;
}



