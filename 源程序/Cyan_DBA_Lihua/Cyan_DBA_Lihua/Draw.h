#ifndef _DRAW_
#define _DRAW_

#pragma once
#include "afx.h"




//逻辑转实际（地球）  坐标
extern void VPtoDP(int x,int y,float *X,float *Y);

//实际转逻辑（电脑像素） 坐标
extern void DPtoVP(float X,float Y,int *x,int *y);

//逻辑转实际（地球）  长度
extern float VLtoDL(float l);

//实际转逻辑（电脑像素）  长度
extern float DLtoVL(float l);

//存储直线或者多边形顶点坐标的结构体
typedef struct
{
	//顶点X坐标
	float x; 
	//顶点Y坐标
	float y;
	//顶点Z坐标(高程，预留)
	float z;

}PointStruct;
/////////////////////////////////


class CDraw :
	public CObject
{
public:
	//DECLARE_SERIAL (CDraw)
	CDraw(void);
	//构造函数
	CDraw(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete);
	///////////////////
	~CDraw(void);
	virtual void Draw(CDC *pDC,int Mode ,int length = 0,int index =0) = 0;
	
	///////////存档//////////////////
	void Serialize( CArchive& ar ); //这个函数在Object中已经被定义
	//////获取指定数组指定秩的ID////////
	int GetID();
	//////确定外接矩形坐标的最值//////////
	virtual void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax) = 0 ;
	/////////点选////////////////
	virtual bool IsPoint(CDC *pDC,float px,float py) =0;
	//////////框选////////////////
	virtual bool IsRect(CDC *pDC,CRect rect) = 0;
	///////////删除图形///////////////////
	void Delete(BOOL Is);
	////////////查看是否删除/////////////
	BOOL IsDelete();


protected:

	// 笔色
	COLORREF m_ColorPen;
	// 填充刷颜色
	COLORREF m_ColorBrush;
	// 线宽(像素)
	short m_LineWide;
	// 线型(像素)
	short m_LineType;
	// 图形元素唯一的标识号
	int m_id_only;
	// 是否处于删除状态
	BOOL b_Delete;


};

#endif

