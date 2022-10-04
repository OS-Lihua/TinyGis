#include "StdAfx.h"
#include "Draw.h"


CDraw::CDraw(void)
{
}

//带6个参数的构造函数
CDraw::CDraw(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete)
{
	this->m_ColorPen = m_ColorPen;
	this->m_ColorBrush = m_ColorBrush;
	this->m_LineWide = m_LineWide;
	this->m_LineType = m_LineType;
	this->m_id_only = m_id_only;
	this->b_Delete =b_Delete;
}
////////////////////////

CDraw::~CDraw(void)
{
}

 ///////获取ID//////
int CDraw::GetID()
{
	return this->m_id_only;	//因为编号是私有的，只有这样才能调用出来
}


 ////////////存档//////////////////
void CDraw::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar << this->b_Delete << this->m_ColorPen << this->m_ColorBrush << this->m_LineWide << this->m_LineType << this->m_id_only;
	}
	else
	{
		ar >> this->b_Delete >> this->m_ColorPen >> this->m_ColorBrush >> this->m_LineWide >> this->m_LineType >> this->m_id_only;
	}
}



///////////删除图形///////////////////
void CDraw::Delete(BOOL Is)
{
	if(Is)
	{
		this->b_Delete = TRUE;
	}
	else
	{
		this->b_Delete = FALSE;
	}
}
////////////查看是否删除/////////////
BOOL CDraw::IsDelete()
{
	return this->b_Delete;
}
