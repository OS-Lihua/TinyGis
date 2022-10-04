
// Cyan_DBA_LihuaView.h : CCyan_DBA_LihuaView 类的接口
//
#ifndef	 _CYAN_DBA_LIHUAView_
#define  _CYAN_DBA_LIHUAView_
#pragma once


#include <stdlib.h>
#include <iostream>
#include <limits>
#include "resource.h"
#include"TextDlg.h"
#include "ColorTool.h"
#include "MapMessage.h"
#include "RouteSelect.h"
#include "MainFrm.h"
#include "ImageCenterDib.h"
#include "WINDOWSX.H "
#include "BaseMapSet.h"
#include "Position.h"
#include "MapBuffer.h"
#include "math.h"
#include <windows.h>
const int EARTH_RADIUS = 6371000;	//米
#define ArraySize (1024)


class CCyan_DBA_LihuaView : public CFormView
{
protected: // 仅从序列化创建
	CCyan_DBA_LihuaView();
	DECLARE_DYNCREATE(CCyan_DBA_LihuaView)

public:
	enum{ IDD = IDD_CYAN_DBA_LIHUA_FORM };

// 特性
public:
	CCyan_DBA_LihuaDoc* GetDocument() const;

// 操作
public:
	int GetScreenH();	//获取屏幕高度
	int GetScreenW();	//获取屏幕宽度
	int imgWidth;	//底图宽度
	int imgHeight;	//底图高度
	int xmove,ymove	;	//底图初始的X ,Y 坐标
	float xmoveTo ,ymoveTo;	//用作底图的坐标转换
	double sumLength;	//测量的长度

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

	COLORREF m_pColor;	//画笔颜色
	COLORREF m_brushColor;  //画刷颜色
	short m_LineWide;	//设置线宽
	short m_LineType;	//设置线型
	CPen m_pen;		//定义画笔	构造函数初始化
	CBrush m_brush;	//定义画刷	构造函数初始化
	CPoint mPointOrign;	//获取鼠标点位置
	CPoint mPointOld; //获取鼠标点位置
	//short m_layer; //设置所属图层
	PointStruct* PointXyz; //设置数组指针
	CImage m_image;//指北针
	int m_hScreen;	//(Form)屏幕高度
	int m_wScreen;	//(Form)屏幕宽度
	PointStruct pstOrign;
	PointStruct psOld;	

	CMap<int ,int , CPoint, CPoint> m_PointMap;	//存储路径的点
	CMap<int ,int ,CString, CString&> m_StringMap; //存储路径的信息
	BOOL light ;	//菜单按钮的灰黑,开始按钮	 初始化为TRUE，即它是亮的，则结束按钮是灰色的
	int m_index;	//路径的key
	int* hash_array;
	bool mapSet;	//底图是否设置
	double rad(double d);	//获取弧度
	double GetDistance(double lng1,double lat1,double lng2,double lat2);		//获取长度




// 实现
public:
	virtual ~CCyan_DBA_LihuaView();
	virtual void OnDraw(CDC* pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//当前正在操作的序号
	int  m_DrawCurrent;
	//记录按下鼠标的次数
	int PushNum;
	//判断回收站是否为空
	bool isEmptytrash;


// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnDrawPoint();
	afx_msg void OnUpdateDrawPoint(CCmdUI *pCmdUI);
	afx_msg void OnDrawTriangle();
	afx_msg void OnUpdateDrawTriangle(CCmdUI *pCmdUI);
	afx_msg void OnDrawPolyline();
	afx_msg void OnUpdateDrawPolyline(CCmdUI *pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI *pCmdUI);
	afx_msg void OnDrawText();
	afx_msg void OnUpdateDrawText(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAttributes();
	afx_msg void OnUpdateAttributes(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawNorth();
	afx_msg void OnUpdateDrawNorth(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnlarge();
	afx_msg void OnUpdateEnlarge(CCmdUI *pCmdUI);
	afx_msg void On2xzoomout();
	afx_msg void OnUpdate3xzoomout(CCmdUI *pCmdUI);
	afx_msg void On3xzoomout();
	afx_msg void OnUpdate2xzoomout(CCmdUI *pCmdUI);
	afx_msg void OnPan();
	afx_msg void OnUpdatePan(CCmdUI *pCmdUI);
	afx_msg void OnFullmap();
	afx_msg void OnUpdateFullmap(CCmdUI *pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void On2xenlargement();
	afx_msg void OnUpdate2xenlargement(CCmdUI *pCmdUI);
	afx_msg void On3xenlargement();
	afx_msg void OnUpdate3xenlargement(CCmdUI *pCmdUI);
	afx_msg void OnZoomout();
	afx_msg void OnUpdateZoomout(CCmdUI *pCmdUI);
	afx_msg void OnBegindraw();
	afx_msg void OnUpdateBegindraw(CCmdUI *pCmdUI);
	afx_msg void OnEnddraw();
	afx_msg void OnUpdateEnddraw(CCmdUI *pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI *pCmdUI);
	afx_msg void OnClicktoselect();
	afx_msg void OnUpdateClicktoselect(CCmdUI *pCmdUI);
	afx_msg void OnFrameselection();
	afx_msg void OnUpdateFrameselection(CCmdUI *pCmdUI);
	afx_msg void OnSubtractselected();
	afx_msg void OnUpdateSubtractselected(CCmdUI *pCmdUI);
	afx_msg void OnGraphicdeletion();
	afx_msg void OnUpdateGraphicdeletion(CCmdUI *pCmdUI);
	afx_msg void OnUndodelete();
	afx_msg void OnUpdateUndodelete(CCmdUI *pCmdUI);
	afx_msg void OnUncheck();
	afx_msg void OnUpdateUncheck(CCmdUI *pCmdUI);
	afx_msg void OnEmptytrash();
	afx_msg void OnUpdateEmptytrash(CCmdUI *pCmdUI);
	afx_msg void OnSaveplot();
	afx_msg void OnRemovebasemap();
	afx_msg void OnInputboundary();
	afx_msg void OnPointonmap();
	afx_msg void OnUpdatePointonmap(CCmdUI *pCmdUI);
	afx_msg void OnPosition();
	afx_msg void OnBuffer();
	afx_msg void OnRedraw();
	afx_msg void OnMeasure();
	afx_msg void OnUpdateMeasure(CCmdUI *pCmdUI);
	afx_msg void OnSelectall();
	afx_msg void OnUpdateSelectall(CCmdUI *pCmdUI);
	afx_msg void OnClearall();
	afx_msg void Onbufferset();
	afx_msg void OnAllbuffer();
	afx_msg void OnPullframe();
	afx_msg void OnUpdatePullframe(CCmdUI *pCmdUI);
	afx_msg void Ontwinkle();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFillpullframe();
	afx_msg void OnUpdateFillpullframe(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // Cyan_DBA_LihuaView.cpp 中的调试版本
inline CCyan_DBA_LihuaDoc* CCyan_DBA_LihuaView::GetDocument() const
   { return reinterpret_cast<CCyan_DBA_LihuaDoc*>(m_pDocument); }
#endif





/////////////在此声明全局内容（extern）/////////////////////////
extern float m_originX; //原点.x
extern float m_originY; //原点.y
extern float m_originXTo;	//暂时保存原点 的 x
extern float m_originYTo;	//暂时保存原点 的 y 
extern float scale;	 //当前比例尺（初始化为1）
extern float scaleNow;	//比例尺（初始化为1） 画图时的比例尺		   
extern CCyan_DBA_LihuaView* pView;	//view的指针(构造函数中初始化为this)


//逻辑转实际（地球）  坐标
extern void VPtoDP(int x,int y,float *X,float *Y);

//实际转逻辑（电脑像素） 坐标
extern void DPtoVP(float X,float Y,int *x,int *y);

//逻辑转实际（地球）  长度
extern float VLtoDL(float l);

//实际转逻辑（电脑像素）  长度
extern float DLtoVL(float l);

//获取当前程序路径
extern CString GetCurrentPath();

///////////////////////////////////////////////
#endif