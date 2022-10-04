#include "StdAfx.h"
#include "PLine.h"

IMPLEMENT_SERIAL (CPLine,CObject,1)

CPLine::CPLine(void)
{
}


//PointStruct *m_PointList 内指向的值均为实际坐标
 //构造函数
CPLine::CPLine(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			int m_Numble,PointStruct *m_PointList,int m_Lb) : CDraw(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,b_Delete)
{
	  this->m_Numble = m_Numble;
	  this->m_Lb = m_Lb;
	  this->m_PointList =new PointStruct[this->m_Numble];
	  if(this->m_Numble > 0)
	  {
		  for(int i =0;i<this->m_Numble;++i)
		  {
			  this->m_PointList[i]= m_PointList[i];
		  }
	  }
	  								     
}

CPLine::~CPLine(void)
{
	if(m_Numble>0)
	{
		delete m_PointList;
	}
}

////////////绘制折线，多边形////////////////
void CPLine::Draw(CDC *pDC,int Mode,int length,int index)
{
	if(this->b_Delete)
	{
		return;
	}
	float x,y;
	CPoint* point;
	point =new CPoint[this->m_Numble];
	for(int i =0;i<this->m_Numble;++i)
	{
		//point[i].x =this->m_PointList[i].x;
		//point[i].y =this->m_PointList[i].y;
		//实际坐标转逻辑坐标，并强制转换
		DPtoVP(this->m_PointList[i].x,this->m_PointList[i].y,(int *)&point[i].x,(int *)&point[i].y);
	}
	CPen pen;
	/*****************************
	CBrush( int nIndex, COLORREF crColor );
	crColor指定画刷的前景色（RGB方式）。如果画刷是阴影线型的，则指定阴影线的颜色。
	nIndex指定画刷阴影线采用的风格，取值如下：
		HS_BDIAGONAL 45度的向下影线（从左到右）
		HS_CROSS水平和垂直方向以网格线作出阴影
		HS_DIAGCROSS 45度的网格线阴影
		HS_FDIAGONAL 45度的向上阴影线（从左到右）
		HS_HORIZONTAL 水平的阴影线
		HS_VERTICAL 垂直的阴影线
	**********************/
	CBrush* oldBrush;
	CBrush brush(HS_FDIAGONAL,this->m_ColorBrush);
	oldBrush = pDC->SelectObject(&brush);//填充

	//缓冲区
	if(Mode == 3)
	{
				///////////////////
		for(int i = 0;i < index ;i++)
		{
			pen.DeleteObject();
			int r = rand()%256;
			int g = rand()%256;
			int b = rand()%256;
			pen.CreatePen(this->m_LineType,(int)(this->m_LineWide+ length*(index-i)),RGB(r,g,b));
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SelectObject(&pen);
			if(12==m_Lb)  
			{			
				pDC->Polyline(point,this->m_Numble);//画折线
			}
			if(13==m_Lb)
			{ 
				pDC->Polygon(point,this->m_Numble);	//画多边形			
			}	
		}
		//////////////////
	}

	if(Mode==2)
	{
		CRgn rgn;
		CPen penb(1,(int)length,RGB(0,255,0));
		CBrush brush(0,m_ColorBrush);
		pDC->BeginPath();
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&penb);
		if(12 == m_Lb)
		{
			pDC->Polyline(point,this->m_Numble);	//画折线
		}
		if(13 == m_Lb)
		{
			pDC->Polygon(point,this->m_Numble);		//画多边形
		}
		pDC->EndPath();
		pDC->WidenPath();
		rgn.CreateFromPath(pDC);
		pDC->FillRgn(&rgn,&brush);
		return;
	} 
	//高亮
	if(1==Mode)
	{
		pen.DeleteObject();
		pen.CreatePen(this->m_LineType,(int)(this->m_LineWide+5),RGB(0,255,255)); //水绿色
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SelectObject(&pen);
		if(12==m_Lb)  
		{			
			pDC->Polyline(point,this->m_Numble);//画折线
		}
		if(13==m_Lb)
		{ 
			pDC->Polygon(point,this->m_Numble);	//画多边形			
		}	
	}

	pen.DeleteObject();
	pen.CreatePen(this->m_LineType,(int)(this->m_LineWide),this->m_ColorPen);
	pDC->SetBkMode(TRANSPARENT); 
	pDC->SelectObject(&pen);
	//折线
	if(12==m_Lb)
	{
		 pDC->Polyline(point,this->m_Numble);//画折线
	}
	//多边形
	else if(13==m_Lb)
	{
		 pDC->Polygon(point,this->m_Numble);//画多边形
	}
	///////////////////////////////////////////////////
	//pDC->SelectObject(oldBrush);

}
//////确定所有折线(外接矩形坐标)的最值//////////
void CPLine::GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax)
{
	float x0,y0,x,y;  
	x0 = m_PointList[0].x;
	x  = m_PointList[0].x;
	y0 = m_PointList[0].y;
	y  = m_PointList[0].y;

	for(int i =1;i<this->m_Numble;++i)
	{
		//这些都是实际坐标|_   （x0,y0）为左下角坐标  （x,y）为右上角坐标
		x0 = min(x0,m_PointList[i].x);
		y0 = min(y0,m_PointList[i].y);
		x  = max(x,m_PointList[i].x);
		y  = max(y,m_PointList[i].y);
	}
	*m_Xmin = x0;
	*m_Ymin = y0;
	*m_Xmax = x;
	*m_Ymax	= y;
}


////////////存档//////////////////
void CPLine::Serialize(CArchive& ar)
{
	CDraw::Serialize( ar );
	if(ar.IsStoring())
	{
		ar << m_Numble << m_Lb	;
		for(int i = 0 ;i < m_Numble ; ++i )
		{
			 ar << m_PointList[i].x << m_PointList[i].y ;
		}
	}
	else
	{
		ar >> m_Numble >> m_Lb	;
		 m_PointList = new  PointStruct[this->m_Numble];
		for(int i =0 ; i < m_Numble ; ++i )
		{
			 ar >> m_PointList[i].x >> m_PointList[i].y ;
		}
	}
}


//////////////点选////////////////////
bool CPLine::IsPoint(CDC *pDC,float px,float py)
{
	if(b_Delete)
	{										   
		return FALSE;
	}
	CRgn rgn;
	int x,y;
	int i;
	POINT* point;
	point = new POINT[m_Numble];
	for(int i =0;i<m_Numble;++i)
	{
		DPtoVP(m_PointList[i].x,m_PointList[i].y,&x,&y);
		point[i].x = x;
		point[i].y = y;
	}
	if(12 == m_Lb)
	{
		rgn.CreatePolygonRgn(point,this->m_Numble,1);
	}
	else
	{
		pDC->BeginPath();
		pDC->Polyline(point,this->m_Numble);
		pDC->EndPath();
		pDC->WidenPath();
		pDC->WidenPath();
		pDC->WidenPath();
		rgn.CreateFromPath(pDC);
	}
	i = rgn.PtInRegion(px,py);
	rgn.DeleteObject();
	return i;
}



/////////框选////////////////
bool CPLine::IsRect(CDC *pDC,CRect rect)
{
	if(b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	int x1,y1;
	int i;
	POINT* point;
	point = new POINT[m_Numble];
	for(int i = 0;i<m_Numble;++i)
	{
		DPtoVP(m_PointList[i].x,m_PointList[i].y,&x1,&y1);
		point[i].x=x1;
		point[i].y=y1;
	}
	if(12 == m_Lb)
	{
		rgn.CreatePolygonRgn(point,m_Numble,1);
	}
	else
	{
		pDC->BeginPath();
		pDC->Polyline(point,m_Numble);
		pDC->EndPath();
		pDC->WidenPath();
		rgn.CreateFromPath(pDC);
	}
	i=rgn.RectInRegion(&rect);		
	rgn.DeleteObject();
	return i;
}

