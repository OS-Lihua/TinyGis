#include "StdAfx.h"
#include "Circle.h"


IMPLEMENT_SERIAL (CCircle,CObject,1)
CCircle::CCircle(void)
{
}

//float m_CircleX,float m_CircleY,float m_CircleR	 均为实际坐标
//构造函数 (列表初始化)
CCircle::CCircle(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_CircleX,float m_CircleY,float m_CircleR,short m_Lb):CDraw(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,b_Delete)
{
	 this->m_CircleX = m_CircleX;
	 this->m_CircleY = m_CircleY;
	 this->m_CircleR = m_CircleR;
	 this->m_Lb = m_Lb;
}

///////////////////////

CCircle::~CCircle(void)
{
}

void CCircle::Draw(CDC *pDC,int Mode,int length,int index)
{
	int x, y;
	float r;
	if(this->b_Delete) 
	{
		return;
	}
	CPen pen;
	CBrush *oldBrush;
	///////////实际转逻辑（电脑像素） 坐标/////////
	//x =this->m_CircleX;
	//y =this->m_CircleY;
	DPtoVP(this->m_CircleX,this->m_CircleY,&x,&y);
	r = DLtoVL(this->m_CircleR);
	//////三角形点坐标的代码//////////
	float sideLength =DLtoVL(6.0);
	//三角形本就是逻辑坐标，不用转换
	CPoint p[3];
	p[0].x = x;	
	p[0].y = y - sqrt(2*sideLength);
	p[1].x = x - sideLength/2; 
	p[1].y = y + sqrt(sideLength/2);
	p[2].x = x + sideLength/2; 
	p[2].y = y + sqrt(sideLength/2);
	//////////////////////////
	/*****************************
	CBrush( int nIndex, COLORREF crColor );
	crColor指定画刷的前景色（RGB方式）。如果画刷是阴影线型的，则指定阴影线的颜色。
	nIndex指定画刷阴影线采用的风格，取值如下：
	HS_BDIAGONAL45度的向下影线（从左到右）
	HS_CROSS水平和垂直方向以网格线作出阴影
	HS_DIAGCROSS 45度的网格线阴影
	HS_FDIAGONAL 45度的向上阴影线（从左到右）
	HS_HORIZONTAL 水平的阴影线
	HS_VERTICAL 垂直的阴影线
	**********************/
	CBrush brush(HS_CROSS,this->m_ColorBrush);
	CBrush brush0(this->m_ColorBrush);
	if(14==m_Lb)
	{
		oldBrush =pDC->SelectObject(&brush);//填充	
	}else
	{
		oldBrush =pDC->SelectObject(&brush0);//非填充
	}
	if(Mode == 3)
	{
		//for(int i = 0;i < index ;i++)
		//{
		//	pen.DeleteObject();
		//	int r = rand()%256;
		//	int g = rand()%256;
		//	int b = rand()%256;
		//	pen.CreatePen(this->m_LineType,(int)(this->m_LineWide+ length*(index-i)),RGB(r,g,b)); 
		//	pDC->SelectObject(&pen);
		//	pDC->SetBkMode(TRANSPARENT);
		//	pDC->Ellipse(x-r,y-r,x+r,y+r);
		//	//pDC->Ellipse(x-r-(length*(index-i)/2),y-r-(length*(index-i)/2),x+r+(length*(index-i)/2),y+r+(length*(index-i)/2));
		//}
	}
	if(Mode==2)
	{
		CRgn rgn;
		CPen penb(1,(int)length,RGB(0,255,0));
		CBrush brush(0,m_ColorBrush);
		pDC->BeginPath();
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&penb);
		if(14==m_Lb||111==m_Lb)
		{
			if(14==m_Lb) pDC->SetBkMode(TRANSPARENT); //圆
			if(111==m_Lb) pDC->SetBkMode(OPAQUE); //圆点
			//x,y,r均已经改为逻辑坐标
			pDC->Ellipse(x-r,y-r,x+r,y+r);
		}
		if(112==m_Lb) 
		{
			pDC->SetBkMode(OPAQUE);
			pDC->Polygon(p,3);	//画三角形
		}
		pDC->EndPath();
		pDC->WidenPath();
		pDC->WidenPath();
		rgn.CreateFromPath(pDC);
		pDC->FillRgn(&rgn,&brush);
		return;
	} 

	if(1==Mode)	  //高亮
	{
		pen.DeleteObject();
		//m_LineWide 实际转逻辑
		pen.CreatePen(this->m_LineType,(int)(this->m_LineWide+5),RGB(0,255,255)); //水绿色
		pDC->SelectObject(&pen);
		if(m_Lb==14||m_Lb==111)
		{ 
			if(14 == m_Lb) pDC->SetBkMode(TRANSPARENT); //圆
			if(111 == m_Lb) pDC->SetBkMode(OPAQUE); //圆点
			//x,y,r均已经改为逻辑坐标
			pDC->Ellipse(x-r,y-r,x+r,y+r);
		}//核心语句，调出圆的外接矩形
		if(112==m_Lb)  
		{
			pDC->SetBkMode(OPAQUE);
			pDC->Polygon(p,3);	//画三角形
		}
	}
	//////////////不管Mode为不为0，以下语句都执行///////////////////////////
	pen.DeleteObject();
	pen.CreatePen(this->m_LineType,(int)(this->m_LineWide),this->m_ColorPen); 
	pDC->SelectObject(&pen);
	if(m_Lb==14||m_Lb==111)
	{ 
		if(14==m_Lb) //圆 
		{
			pDC->SetBkMode(TRANSPARENT);
		}
		if(111==m_Lb) //圆点
		{
			   pDC->SetBkMode(OPAQUE);
		}
		//x,y,r均已经改为逻辑坐标
		pDC->Ellipse(x-r,y-r,x+r,y+r);
		
	}//核心语句，调出圆的外接矩形
	if(112==m_Lb)  
	{
		pDC->SetBkMode(OPAQUE);
		//pDC->SetPolyFillMode(ALTERNATE);
		pDC->Polygon(p,3);	//画三角形
	}
	///////////////////////////////////////////////////

}

/////////存档//////////////
void CCircle::Serialize(CArchive& ar)
{
	CDraw::Serialize( ar );
	if(ar.IsStoring())
	{
		ar <<this->m_CircleX<< this->m_CircleY << this->m_CircleR <<this-> m_Lb;
	}else
	{
		ar >>this->m_CircleX>> this->m_CircleY >> this->m_CircleR >>this-> m_Lb;
	}
}

/////////////////////确定外接矩形坐标的最值///////////////////////////////
void CCircle::GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax)
{
	
	*m_Xmin = this->m_CircleX - this->m_CircleR;
	*m_Ymin = this->m_CircleY - this->m_CircleR;
	*m_Xmax = this->m_CircleX + this->m_CircleR;
	*m_Ymax = this->m_CircleY + this->m_CircleR;
}

///////////点选 ///////////////////////////
bool CCircle::IsPoint(CDC *pDC,float px,float py)
{
	if(b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	int i,x,y;
	float r;
	DPtoVP(m_CircleX,m_CircleY,&x,&y);	   
	r = DLtoVL(m_CircleR);
	float sideLength =DLtoVL(6.0);
	if(14==m_Lb||111==m_Lb)
	{
		rgn.CreateEllipticRgn(x-r,y-r,x+r,x-r);
		if(112==m_Lb)
		{
			CPoint p[3];
			p[0].x = x;	
			p[0].y = y - sqrt(2*sideLength);
			p[1].x = x - sideLength/2; 
			p[1].y = y + sqrt(sideLength/2);
			p[2].x = x + sideLength/2; 
			p[2].y = y + sqrt(sideLength/2);
			rgn.CreatePolygonRgn(p,3,1);
		}
	}
	i = rgn.PtInRegion(px,py);
	rgn.DeleteObject();
	return i;
}


///////////框选///////////////////////////
bool CCircle::IsRect(CDC *pDC,CRect rect)
{
	if(this->b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	int i,x,y;
	float r;
	DPtoVP(m_CircleX,m_CircleY,&x,&y);
	r=DLtoVL(m_CircleR);
	float sideLength =DLtoVL(6.0);
	if(14==m_Lb||111==m_Lb)
	{
		rgn.CreateEllipticRgn(x-r,y-r,x+r,x-r);
		if(112==m_Lb)
		{
		    CPoint p[3];
			p[0].x = x;	
			p[0].y = y - sqrt(2*sideLength);
			p[1].x = x - sideLength/2; 
			p[1].y = y + sqrt(sideLength/2);
			p[2].x = x + sideLength/2; 
			p[2].y = y + sqrt(sideLength/2);
			rgn.CreatePolygonRgn(p,3,1);
		}
	}
	
	i=rgn.RectInRegion(&rect);
	rgn.DeleteObject();
	return i;

}
