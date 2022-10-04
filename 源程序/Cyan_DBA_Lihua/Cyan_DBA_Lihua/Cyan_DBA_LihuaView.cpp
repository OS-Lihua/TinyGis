
// Cyan_DBA_LihuaView.cpp : CCyan_DBA_LihuaView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Cyan_DBA_Lihua.h"
#endif

#include "Cyan_DBA_LihuaDoc.h"
#include "Cyan_DBA_LihuaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////在此定义全局内容（extern）/////////////////////////
float m_originX; //原点.x
float m_originY; //原点.y
float m_originXTo;	//暂时保存原点 的 x
float m_originYTo;	//暂时保存原点 的 y 
float scale = 1.0;	 //比例尺（初始化为1）
float scaleNow = 1.0;
CCyan_DBA_LihuaView* pView;	//view的指针(构造函数中初始化为this)


//逻辑转实际（地球）  坐标
void VPtoDP(int x,int y,float *X,float *Y)
{
	*X=m_originX + x*scale;
	*Y=m_originY + scale*( pView->GetScreenH() -y);
}

//实际转逻辑（电脑像素） 坐标
void DPtoVP(float X,float Y,int *x,int *y)
{
   *x =(X-m_originX)/scale;
   *y = pView->GetScreenH() -(Y -m_originY)/scale ;
}

//逻辑转实际（地球）  长度				  
float VLtoDL(float l)
{
	return scale * l;
}

//实际转逻辑（电脑像素）  长度
float DLtoVL(float l)
{
	return l/scale;
}

//获取当前程序路径
CString GetCurrentPath()
{
	CString strPath;
	TCHAR path[_MAX_PATH];
	TCHAR drv[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];

	GetModuleFileName(NULL, path, _MAX_PATH);
	_tsplitpath(path, drv, dir, NULL, NULL);
	_tmakepath(path, drv, dir, NULL,NULL);

	strPath=path;
	return strPath;
}

///////////////////////////////////////////////



// CCyan_DBA_LihuaView

IMPLEMENT_DYNCREATE(CCyan_DBA_LihuaView, CFormView)

BEGIN_MESSAGE_MAP(CCyan_DBA_LihuaView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_Circle, &CCyan_DBA_LihuaView::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Circle, &CCyan_DBA_LihuaView::OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_Point, &CCyan_DBA_LihuaView::OnDrawPoint)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Point, &CCyan_DBA_LihuaView::OnUpdateDrawPoint)
	ON_COMMAND(ID_DRAW_Triangle, &CCyan_DBA_LihuaView::OnDrawTriangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Triangle, &CCyan_DBA_LihuaView::OnUpdateDrawTriangle)
	ON_COMMAND(ID_DRAW_Polyline, &CCyan_DBA_LihuaView::OnDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Polyline, &CCyan_DBA_LihuaView::OnUpdateDrawPolyline)
	ON_COMMAND(ID_DRAW_Polygon, &CCyan_DBA_LihuaView::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Polygon, &CCyan_DBA_LihuaView::OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_Text, &CCyan_DBA_LihuaView::OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Text, &CCyan_DBA_LihuaView::OnUpdateDrawText)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_Attributes, &CCyan_DBA_LihuaView::OnAttributes)
	ON_UPDATE_COMMAND_UI(ID_Attributes, &CCyan_DBA_LihuaView::OnUpdateAttributes)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DRAW_NORTH, &CCyan_DBA_LihuaView::OnDrawNorth)
	ON_UPDATE_COMMAND_UI(ID_DRAW_NORTH, &CCyan_DBA_LihuaView::OnUpdateDrawNorth)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_Enlarge, &CCyan_DBA_LihuaView::OnEnlarge)
	ON_UPDATE_COMMAND_UI(ID_Enlarge, &CCyan_DBA_LihuaView::OnUpdateEnlarge)
	ON_COMMAND(ID_2xZoomOut, &CCyan_DBA_LihuaView::On2xzoomout)
	ON_UPDATE_COMMAND_UI(ID_3xZoomOut, &CCyan_DBA_LihuaView::OnUpdate3xzoomout)
	ON_COMMAND(ID_3xZoomOut, &CCyan_DBA_LihuaView::On3xzoomout)
	ON_UPDATE_COMMAND_UI(ID_2xZoomOut, &CCyan_DBA_LihuaView::OnUpdate2xzoomout)
	ON_COMMAND(ID_Pan, &CCyan_DBA_LihuaView::OnPan)
	ON_UPDATE_COMMAND_UI(ID_Pan, &CCyan_DBA_LihuaView::OnUpdatePan)
	ON_COMMAND(ID_FullMap, &CCyan_DBA_LihuaView::OnFullmap)
	ON_UPDATE_COMMAND_UI(ID_FullMap, &CCyan_DBA_LihuaView::OnUpdateFullmap)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_2xEnlargement, &CCyan_DBA_LihuaView::On2xenlargement)
	ON_UPDATE_COMMAND_UI(ID_2xEnlargement, &CCyan_DBA_LihuaView::OnUpdate2xenlargement)
	ON_COMMAND(ID_3xEnlargement, &CCyan_DBA_LihuaView::On3xenlargement)
	ON_UPDATE_COMMAND_UI(ID_3xEnlargement, &CCyan_DBA_LihuaView::OnUpdate3xenlargement)
	ON_COMMAND(ID_ZoomOut, &CCyan_DBA_LihuaView::OnZoomout)
	ON_UPDATE_COMMAND_UI(ID_ZoomOut, &CCyan_DBA_LihuaView::OnUpdateZoomout)
	ON_COMMAND(ID_BeginDraw, &CCyan_DBA_LihuaView::OnBegindraw)
	ON_UPDATE_COMMAND_UI(ID_BeginDraw, &CCyan_DBA_LihuaView::OnUpdateBegindraw)
	ON_COMMAND(ID_EndDraw, &CCyan_DBA_LihuaView::OnEnddraw)
	ON_UPDATE_COMMAND_UI(ID_EndDraw, &CCyan_DBA_LihuaView::OnUpdateEnddraw)
	ON_COMMAND(ID_Select, &CCyan_DBA_LihuaView::OnSelect)
	ON_UPDATE_COMMAND_UI(ID_Select, &CCyan_DBA_LihuaView::OnUpdateSelect)
	ON_COMMAND(ID_ClickToSelect, &CCyan_DBA_LihuaView::OnClicktoselect)
	ON_UPDATE_COMMAND_UI(ID_ClickToSelect, &CCyan_DBA_LihuaView::OnUpdateClicktoselect)
	ON_COMMAND(ID_FrameSelection, &CCyan_DBA_LihuaView::OnFrameselection)
	ON_UPDATE_COMMAND_UI(ID_FrameSelection, &CCyan_DBA_LihuaView::OnUpdateFrameselection)
	ON_COMMAND(ID_SubtractSelected, &CCyan_DBA_LihuaView::OnSubtractselected)
	ON_UPDATE_COMMAND_UI(ID_SubtractSelected, &CCyan_DBA_LihuaView::OnUpdateSubtractselected)
	ON_COMMAND(ID_GraphicDeletion, &CCyan_DBA_LihuaView::OnGraphicdeletion)
	ON_UPDATE_COMMAND_UI(ID_GraphicDeletion, &CCyan_DBA_LihuaView::OnUpdateGraphicdeletion)
	ON_COMMAND(ID_UndoDelete, &CCyan_DBA_LihuaView::OnUndodelete)
	ON_UPDATE_COMMAND_UI(ID_UndoDelete, &CCyan_DBA_LihuaView::OnUpdateUndodelete)
	ON_COMMAND(ID_Uncheck, &CCyan_DBA_LihuaView::OnUncheck)
	ON_UPDATE_COMMAND_UI(ID_Uncheck, &CCyan_DBA_LihuaView::OnUpdateUncheck)
	ON_COMMAND(ID_EmptyTrash, &CCyan_DBA_LihuaView::OnEmptytrash)
	ON_UPDATE_COMMAND_UI(ID_EmptyTrash, &CCyan_DBA_LihuaView::OnUpdateEmptytrash)
	ON_COMMAND(ID_SavePlot, &CCyan_DBA_LihuaView::OnSaveplot)
	ON_COMMAND(ID_RemoveBasemap, &CCyan_DBA_LihuaView::OnRemovebasemap)
	ON_COMMAND(ID_InputBoundary, &CCyan_DBA_LihuaView::OnInputboundary)
	ON_COMMAND(ID_PointOnMap, &CCyan_DBA_LihuaView::OnPointonmap)
	ON_UPDATE_COMMAND_UI(ID_PointOnMap, &CCyan_DBA_LihuaView::OnUpdatePointonmap)
	ON_COMMAND(ID_Position, &CCyan_DBA_LihuaView::OnPosition)
	ON_COMMAND(ID_Buffer, &CCyan_DBA_LihuaView::OnBuffer)
	ON_COMMAND(ID_ReDraw, &CCyan_DBA_LihuaView::OnRedraw)
	ON_COMMAND(ID_MeaSure, &CCyan_DBA_LihuaView::OnMeasure)
	ON_UPDATE_COMMAND_UI(ID_MeaSure, &CCyan_DBA_LihuaView::OnUpdateMeasure)
	ON_COMMAND(ID_SelectAll, &CCyan_DBA_LihuaView::OnSelectall)
	ON_UPDATE_COMMAND_UI(ID_SelectAll, &CCyan_DBA_LihuaView::OnUpdateSelectall)
	ON_COMMAND(ID_ClearAll, &CCyan_DBA_LihuaView::OnClearall)
	ON_COMMAND(ID_bufferSet, &CCyan_DBA_LihuaView::Onbufferset)
	ON_COMMAND(ID_ALLbuffer, &CCyan_DBA_LihuaView::OnAllbuffer)
	ON_COMMAND(ID_PullFrame, &CCyan_DBA_LihuaView::OnPullframe)
	ON_UPDATE_COMMAND_UI(ID_PullFrame, &CCyan_DBA_LihuaView::OnUpdatePullframe)
	ON_COMMAND(ID_FillPullFrame, &CCyan_DBA_LihuaView::OnFillpullframe)
	ON_UPDATE_COMMAND_UI(ID_FillPullFrame, &CCyan_DBA_LihuaView::OnUpdateFillpullframe)
END_MESSAGE_MAP()

// CCyan_DBA_LihuaView 构造/析构
//我在这里显示的定义this指针，以区别全局变量和类变量
CCyan_DBA_LihuaView::CCyan_DBA_LihuaView(): m_pen(PS_SOLID,1 ,RGB(0,0,0)),m_brush(3,RGB(0,0,0))	//调用系统提供的构造函数，用的是列表初始化方式来构造初始化列表
	,CFormView(CCyan_DBA_LihuaView::IDD)
{
	// TODO: 在此处添加构造代码
	pView = this;  //给全局变量赋值

	this->light = TRUE ;	//初始化为TRUE，即它是亮的
	this->m_index = 0;	//路径的key
	this->hash_array = new int[ArraySize];	  //初始化 1kb 个数据空间，即4kb的内存
	memset(hash_array,0,ArraySize);	   //全部初始化为0
	//////////////
	this->PointXyz = new PointStruct[ArraySize];
	this->m_pColor = RGB(0,0,0); 
	this->m_brushColor = RGB(0,0,0);  
	this->m_LineWide= 2;
	this->m_LineType = 0;
	this->m_index = 0;
	isEmptytrash = true;

	xmove = 0;
	ymove = 0;

	this->mapSet =false;
	this->sumLength = 0;

}

CCyan_DBA_LihuaView::~CCyan_DBA_LihuaView()
{
	delete [] this->PointXyz;	//删除new 出来的数组 delete []
	delete [] this->hash_array;
}

void CCyan_DBA_LihuaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CCyan_DBA_LihuaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CCyan_DBA_LihuaView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CCyan_DBA_LihuaView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCyan_DBA_LihuaView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCyan_DBA_LihuaView 诊断

#ifdef _DEBUG
void CCyan_DBA_LihuaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCyan_DBA_LihuaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCyan_DBA_LihuaDoc* CCyan_DBA_LihuaView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCyan_DBA_LihuaDoc)));
	return (CCyan_DBA_LihuaDoc*)m_pDocument;
}
#endif //_DEBUG


// CCyan_DBA_LihuaView 消息处理程序
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PushNum为类变量
//m_DrawCurrent为类变量

///////////////////////////画圆点////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawPoint()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=111;
}

void CCyan_DBA_LihuaView::OnUpdateDrawPoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==111);
}


///////////////////////////画三角点////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawTriangle()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=112;
}

void CCyan_DBA_LihuaView::OnUpdateDrawTriangle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==112);
}


///////////////////////////画折线///////////////////////////////
void CCyan_DBA_LihuaView::OnDrawPolyline()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=12;
}

void CCyan_DBA_LihuaView::OnUpdateDrawPolyline(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==12);
}


///////////////////////////画多边形////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=13;
}

void CCyan_DBA_LihuaView::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==13);
}


///////////////////////////画圆////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawCircle()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=14;

}

void CCyan_DBA_LihuaView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==14);

}


///////////////////////////画文字////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawText()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=15;
}

void CCyan_DBA_LihuaView::OnUpdateDrawText(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==15);
}


///////////////////////////画指北针////////////////////////////////
void CCyan_DBA_LihuaView::OnDrawNorth()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=16;
}

void CCyan_DBA_LihuaView::OnUpdateDrawNorth(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==16);
}




//////////////////2倍放大///////////////////////////

void CCyan_DBA_LihuaView::On2xenlargement()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent = 411;
}


void CCyan_DBA_LihuaView::OnUpdate2xenlargement(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==411);
}
/////////////////3倍放大///////////////////////////


void CCyan_DBA_LihuaView::On3xenlargement()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent = 412;
}


void CCyan_DBA_LihuaView::OnUpdate3xenlargement(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==412);
}




///////////2倍缩小//////////////////////
void CCyan_DBA_LihuaView::On2xzoomout()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=421;
}

void CCyan_DBA_LihuaView::OnUpdate2xzoomout(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==421);
}


///////////3倍缩小//////////////////////
void CCyan_DBA_LihuaView::On3xzoomout()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=422;
}


void CCyan_DBA_LihuaView::OnUpdate3xzoomout(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==422);
}


////////////////平移//////////////////////
void CCyan_DBA_LihuaView::OnPan()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=43;
}


void CCyan_DBA_LihuaView::OnUpdatePan(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==43);
}

///////////全图显示//////////////////////
void CCyan_DBA_LihuaView::OnFullmap()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=44;
	float min_x,min_y,max_x,max_y,scale1,scale2,xmove,ymove;
	CCyan_DBA_LihuaDoc* pDoc = GetDocument();	//获取Doc的指针
	//最小值和最大值的初始值都非常离谱，以确保能更新
	min_x= FLT_MAX;	    //最小的给最大值	  
	min_y= FLT_MAX;
	max_x= FLT_MIN;	   //最大的给最小值
	max_y= FLT_MIN;	   ////系统定义的float的宏
	SetCapture();
	//捕获光标，并且将其变形态为等待状态
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	BOOL pb= pDoc->GetRect(&min_x,&min_y,&max_x,&max_y);
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	ReleaseCapture();
	if(!pb)
	{
		return;
	}
	else
	{
		scale1 = (max_x - min_x) / (m_wScreen);
		scale2 = (max_y - min_y) / (m_hScreen);
	}
	if(scale1<=scale2)
	{
		scale = scale2;
	}
	else
	{
		scale = scale1;
	}
	m_originX = min_x;
	m_originY = min_y;
	Invalidate();
}


void CCyan_DBA_LihuaView::OnUpdateFullmap(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==44);
}

//////////////////放大///////////////////////////

void CCyan_DBA_LihuaView::OnEnlarge()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=45;
	
}


void CCyan_DBA_LihuaView::OnUpdateEnlarge(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==45);

}

///////////缩小//////////////////////
void CCyan_DBA_LihuaView::OnZoomout()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=46;
}


void CCyan_DBA_LihuaView::OnUpdateZoomout(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==46);
}

///////////////////开始绘制////////////////
void CCyan_DBA_LihuaView::OnBegindraw()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=511;
	this->light = FALSE;			//具体效果
}


void CCyan_DBA_LihuaView::OnUpdateBegindraw(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(light)
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
	

	

}

///////////////结束绘制///////////////////
void CCyan_DBA_LihuaView::OnEnddraw()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=512;
	this->light = TRUE;
	this->hash_array[m_index - 1] = 0;	   //将hash数组的特定值设置为0,以实现多条路径
	Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数
}


void CCyan_DBA_LihuaView::OnUpdateEnddraw(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(light)
	{
		pCmdUI->Enable(0);
	}
	else
	{
		pCmdUI->Enable(1);
	}
}





////////////////配置属性框/////////////////
void CCyan_DBA_LihuaView::OnAttributes()
{
	// TODO: 在此添加命令处理程序代码
	//字体有关变量坐标均不转换
	PushNum=0;
	m_DrawCurrent=31;
	ColorTool colorTool;
	colorTool.m_slider=1;
	if(IDOK==colorTool. DoModal ())
	{
		m_LineType=colorTool.linetype;
		m_LineWide=colorTool.m_slider;
		m_pColor=colorTool.penCo1or;   //给背景传值
		m_brushColor=colorTool.brushCo1or;
	}
	m_pen.DeleteObject();
	m_pen.CreatePen(this->m_LineType,(int)this->m_LineWide,m_pColor);
}


void CCyan_DBA_LihuaView::OnUpdateAttributes(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==31);
}


//////////////////执行查询操作//////////////////////////
void CCyan_DBA_LihuaView::OnSelect()
{
	// TODO: 在此添加命令处理程序代码
	RouteSelect rs;
	if(IDOK==rs.DoModal ())
	{
		CString p,str;
		int selsetm_index = _ttoi(rs.m_index);		//_ttoi CString ->int
		m_StringMap.Lookup(selsetm_index,str);
		p.Format(_T("%d号位置"),_ttoi(rs.m_index));	//把位置信息存入p中
		if(!m_StringMap.IsEmpty())
		{
			if(str == "")
			{
				MessageBox(_T("No Message Found"),_T("查询失败"),MB_ICONWARNING|MB_OK);
			}
			else
			{
				MessageBox(p+_T("\n")+str,_T("查询成功"),MB_OK);
			}
		}
	}

}


void CCyan_DBA_LihuaView::OnUpdateSelect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码	
}


 ////////////////////////点选//////////////////////////
void CCyan_DBA_LihuaView::OnClicktoselect()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=61;
}


void CCyan_DBA_LihuaView::OnUpdateClicktoselect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==61);
}

///////////////////////框选////////////////////
void CCyan_DBA_LihuaView::OnFrameselection()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=62;
}






void CCyan_DBA_LihuaView::OnUpdateFrameselection(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==62);
}

//////////////////全选////////////////
 void CCyan_DBA_LihuaView::OnSelectall()
{
	// TODO: 在此添加命令处理程序代码
	
	//PushNum=0;
	//m_DrawCurrent=68;
	CCyan_DBA_LihuaDoc *pDoc=GetDocument();
	CClientDC client(this);
	if(pDoc->n_GraphSelect == 4096*3)
		{
			AfxMessageBox(_T("最多只能选择12288个元素"));
			return ;
		}
		CRect rect( INT_MIN, INT_MIN, INT_MAX, INT_MAX);
	
		for(int i=1;i<=3; ++i)
		{
			int n=pDoc->GetGraphUpperBound(i);
			for(int j=0;j<=n; ++j)
			{
				BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
				if(a)
				{
					BOOL b = pDoc->AddSelectList(i,j);
					if(b)
					{
						pDoc->GetGraph(i,j)->Draw(&client,1);
					}
				}
			}
		}
	
}

 


void CCyan_DBA_LihuaView::OnUpdateSelectall(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//pCmdUI->SetRadio(m_DrawCurrent==68);
}


////////////////////////////减选//////////////////////
void CCyan_DBA_LihuaView::OnSubtractselected()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=63;
}


void CCyan_DBA_LihuaView::OnUpdateSubtractselected(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==63);
}

////////////////////取消选择///////////////////
void CCyan_DBA_LihuaView::OnUncheck()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=64;
	auto pDoc = GetDocument();
	pDoc->n_GraphSelect = 0;		//通过n_GraphSelect来控制画图即DocDraw
	Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数	  强制触发重绘	
}


void CCyan_DBA_LihuaView::OnUpdateUncheck(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent==64);
}

///////////////////////图形删除/////////////////////
void CCyan_DBA_LihuaView::OnGraphicdeletion()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=65;
	auto pDoc = GetDocument();
	CClientDC clinet(this);
	CDraw* pDraw;
	for(int i = 0;i<pDoc->n_GraphSelect;++i)
	{
		pDraw = pDoc->GetGraph(pDoc->GraphSelect[i].Lb,pDoc->GraphSelect[i].Index);
		pDraw->Delete(true);
		this->isEmptytrash = false;
	    Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数	  强制触发重绘
	}
}


void CCyan_DBA_LihuaView::OnUpdateGraphicdeletion(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(this->isEmptytrash)
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
}


/////////////////取消删除///////////////////
void CCyan_DBA_LihuaView::OnUndodelete()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=66;
	auto pDoc = GetDocument();
	CClientDC clinet(this);
	CDraw* pDraw;
	for(int i = 0;i<pDoc->n_GraphSelect;++i)
	{
		pDraw = pDoc->GetGraph(pDoc->GraphSelect[i].Lb,pDoc->GraphSelect[i].Index);
		pDraw->Delete(false);
		this->isEmptytrash = true;
	    Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数	  强制触发重绘

	}
}


void CCyan_DBA_LihuaView::OnUpdateUndodelete(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(this->isEmptytrash)
	{
		pCmdUI->Enable(0);
	}
	else
	{
		pCmdUI->Enable(1);
	}
}

/////////////清空回收站/////////////////
void CCyan_DBA_LihuaView::OnEmptytrash()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent=67;
	auto pDoc = GetDocument();
	pDoc->OnPack();
	Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数	  强制触发重绘
	this->isEmptytrash = true;

}
 
void CCyan_DBA_LihuaView::OnUpdateEmptytrash(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(this->isEmptytrash)
	{
		pCmdUI->Enable(0);
	}
	else
	{
		pCmdUI->Enable(1);
	}
}


/////////////////////保存出图////////////////
void CCyan_DBA_LihuaView::OnSaveplot()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC   SHDC(this);
	CDC   memDC; 
	CRect   rect; 
	GetClientRect(rect); 
	memDC.CreateCompatibleDC(&SHDC); 
	CBitmap   bm; 
	int   Width   =   rect.Width();
	int   Height   =   rect.Height();
	bm.CreateCompatibleBitmap(&SHDC,Width,Height); 
	CBitmap*     pOld   =   memDC.SelectObject(&bm); 
	memDC.BitBlt(0,0,Width,Height,&SHDC,0,0,SRCCOPY); 
	memDC.SelectObject(pOld); 
	BITMAP     btm; 
	bm.GetBitmap(&btm); 
	DWORD     size   =   btm.bmWidthBytes*btm.bmHeight; 
	LPSTR   lpData   =(LPSTR)GlobalAllocPtr(GPTR,size); 
	BITMAPFILEHEADER       bfh; 
	bfh.bfReserved1   =   bfh.bfReserved2   =   0; 
	bfh.bfType   =   ((WORD)( 'M'<<8)|'B'); 
	bfh.bfSize   =   54   +   size; 
	bfh.bfOffBits   =   54; 
	BITMAPINFOHEADER     bih; 
	bih.biBitCount   =   btm.bmBitsPixel; 
	bih.biClrImportant   =   0; 
	bih.biClrUsed   =   0; 
	bih.biCompression   =   0; 
	bih.biHeight   =   btm.bmHeight; 
	bih.biPlanes   =   1; 
	bih.biSize   =   sizeof(BITMAPINFOHEADER); 
	bih.biSizeImage   =   size; 
	bih.biWidth   =   btm.bmWidth; 
	bih.biXPelsPerMeter   =   0; 
	bih.biYPelsPerMeter   =   0; 
	GetDIBits(GetDC()->GetSafeHdc(),bm,0,bih.biHeight,lpData,(BITMAPINFO*)&bih,DIB_RGB_COLORS); 
	CFileDialog  dlg(FALSE,_T(""),_T(""),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("*.bmp|*.bmp")); 
	if(dlg.DoModal()==IDOK) 
	{	CFile     bf; 
	CString   ss=dlg.GetPathName(); 
	if(bf.Open(ss,CFile::modeCreate|CFile::modeWrite)) 
	{ 
		bf.Write(&bfh,sizeof(BITMAPFILEHEADER)); 
		bf.Write(&bih,sizeof(BITMAPINFOHEADER)); 
		bf.Write(lpData,size); 
		bf.Close(); 
	} 
	GlobalFreePtr(lpData);
	}	

}



///////////////删除底图////////////////
void CCyan_DBA_LihuaView::OnRemovebasemap()
{
	// TODO: 在此添加命令处理程序代码
	CCyan_DBA_LihuaDoc* pDoc = GetDocument();
	pDoc->GetPDib()->Empty();
	isAdd = false;
	Invalidate();	//强制触发重绘
}


////////////////输入边界////////////
void CCyan_DBA_LihuaView::OnInputboundary()
{
	// TODO: 在此添加命令处理程序代码
	float x1,y1,x2,y2,scale1,scale2;
	BaseMapSet dig;
	dig.minLongitude= "经度最小坐标";
	dig.minLatitude = "纬度最小坐标";
	dig.maxLongitude= "经度最大坐标";
	dig.maxLatitude = "纬度最大坐标";
	
	if(IDOK == dig.DoModal())
	{
		x1=(_ttoi(dig.m1)/60.0+_ttoi(dig.f1))/60.0+_ttoi(dig.d1);
		y1=(_ttoi(dig.m2)/60.0+_ttoi(dig.f2))/60.0+_ttoi(dig.d2);
		x2=(_ttoi(dig.m3)/60.0+_ttoi(dig.f3))/60.0+_ttoi(dig.d3);
		y2=(_ttoi(dig.m4)/60.0+_ttoi(dig.f4))/60.0+_ttoi(dig.d4);
		m_originX=x1;
		m_originY=y1;
		scale1= (x2-x1)/(m_wScreen);
		scale2= (y2-y1)/(m_hScreen);
		if(scale1>scale2)
		{
			scale=scale1;
		}
		else
		{
			scale=scale2;
		}
	 }
	 m_originXTo=m_originX;
	 m_originYTo=m_originY;
	 scaleNow=scale;
	 mapSet = true;
}






////////////输入第一个数//////////////
void CCyan_DBA_LihuaView::OnPointonmap()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent = 232;
	MessageBox(_T("请在图上依次输入已知经纬度的两个点"),_T("操作说明"),MB_OK);
}

void CCyan_DBA_LihuaView::OnUpdatePointonmap(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_DrawCurrent == 232);
}



//////////////定位////////
void CCyan_DBA_LihuaView::OnPosition()
{
	// TODO: 在此添加命令处理程序代码
	if(mapSet)
	{
		int x, y;	
		//scale = scaleNow;
		m_originX =	  m_originXTo;
		m_originY =	  m_originYTo;
		xmove = 0;
		ymove = 0;
		Invalidate();	//强制触发重绘
		Position dlg;
		if(IDOK == dlg.DoModal())
		{
			DPtoVP(_ttof(dlg.longitude),_ttof(dlg.latitude),&x,&y);
			CClientDC client(this);
			CBrush brush1(RGB(0,0,0));
			client.SelectObject(&brush1);
			client.Ellipse(x-7,y-7,x+7,y+7);
		}
	}
	else MessageBox(_T("只查询带坐标的位置，请先设置底图在坐标参数！"),_T("注意"),MB_ICONWARNING);

}



///////////////缓冲区//////////
void CCyan_DBA_LihuaView::OnBuffer()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("请注意，当前是对您最后选择的图形元素进行缓冲区分析！"));
	CCyan_DBA_LihuaDoc* pDoc=GetDocument();
	if(pDoc->n_GraphSelect==0||pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb==3)
	{
		MessageBox(_T("请选择操作图形元素"));
		return;					
	}
	MapBuffer dlg;
	if(dlg.DoModal()==IDOK)
	{
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].buff=_ttoi(dlg.bufferLong);
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].sumbuf= 0;
		int x=DLtoVL(_ttoi(dlg.bufferLong));
		CClientDC client(this);
		pDoc->GetGraph(pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb,pDoc->GraphSelect[pDoc->n_GraphSelect-1].Index)->Draw(&client, 2, x);
	}

}





///////////////缓冲带////////自带
void CCyan_DBA_LihuaView::Onbufferset()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	MessageBox(_T("请注意，当前是对您最后选择的图形元素进行缓冲区分析！"));
	CCyan_DBA_LihuaDoc* pDoc=GetDocument();
	if(pDoc->n_GraphSelect==0||pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb==3)
	{
		MessageBox(_T("请选择操作图形元素"));
		return;					
	}
	MapBuffer dlg;
	if(dlg.DoModal()==IDOK)
	{
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].buff=_ttoi(dlg.bufferLong);
		pDoc->GraphSelect[pDoc->n_GraphSelect-1].sumbuf=_ttoi(dlg.bufferNumber);
		int x=DLtoVL(_ttoi(dlg.bufferLong));
		int y = DLtoVL(_ttoi(dlg.bufferNumber));
		CClientDC client(this);
		pDoc->GetGraph(pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb,pDoc->GraphSelect[pDoc->n_GraphSelect-1].Index)->Draw(&client, 3, x,y);
	}

}



//////批量缓冲

void CCyan_DBA_LihuaView::OnAllbuffer()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("请注意，当前是对所有选中的图形元素进行缓冲区分析！"));
	CCyan_DBA_LihuaDoc* pDoc=GetDocument();
	if(pDoc->n_GraphSelect==0||pDoc->GraphSelect[pDoc->n_GraphSelect-1].Lb==3)
	{
		MessageBox(_T("请选择操作图形元素"));
		return;					
	}
	MapBuffer dlg;
	if(dlg.DoModal()==IDOK)
	{
		for(int i =0;i<pDoc->n_GraphSelect ;++i)
		{
			pDoc->GraphSelect[i].buff=_ttoi(dlg.bufferLong);
			pDoc->GraphSelect[i].sumbuf=_ttoi(dlg.bufferNumber);
			int x=DLtoVL(_ttoi(dlg.bufferLong));
			int y = DLtoVL(_ttoi(dlg.bufferNumber));
			CClientDC client(this);
			pDoc->GetGraph(pDoc->GraphSelect[i].Lb,pDoc->GraphSelect[i].Index)->Draw(&client, 3, x,y);
		}
		
	}
}



/////////底图重绘/////////////
void CCyan_DBA_LihuaView::OnRedraw()
{
	// TODO: 在此添加命令处理程序代码
	xmove = 0;
	ymove = 0;
	Invalidate();	//强制触发重绘

}





//////////测量////////////
void CCyan_DBA_LihuaView::OnMeasure()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent = 71;
}


void CCyan_DBA_LihuaView::OnUpdateMeasure(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(71 == m_DrawCurrent);
}




///清屏///////////

void CCyan_DBA_LihuaView::OnClearall()
{
	// TODO: 在此添加命令处理程序代码
	if( IDOK == MessageBox(_T("你确定吗，不是手滑了？"),_T("警告"),MB_ICONWARNING|MB_OKCANCEL))
	{
		auto pDoc = GetDocument();
		pDoc->n_GraphSelect = 0;
		pDoc->clearAll();
		this->Invalidate();
	}
	else 
	{
		 MessageBox(_T("因为有你，世界更美丽"),_T("哈哈哈"),MB_OK);
	}

}


///////////////拉框/////////////
void CCyan_DBA_LihuaView::OnPullframe()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent = 72;

}


void CCyan_DBA_LihuaView::OnUpdatePullframe(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(72 == m_DrawCurrent);
}




void CCyan_DBA_LihuaView::OnFillpullframe()
{
	// TODO: 在此添加命令处理程序代码
	PushNum=0;
	m_DrawCurrent = 73;
}


 
void CCyan_DBA_LihuaView::OnUpdateFillpullframe(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(73 == m_DrawCurrent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/////左键按下////////
void CCyan_DBA_LihuaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CCyan_DBA_LihuaDoc *pDoc=GetDocument();
	CClientDC client(this);
	short lb,id_only;
	//////////////////绘制文字///////////////////////
	if( m_DrawCurrent==15 )
	{
		float m_FontHeight ,m_FontWide ,m_TextAngle ,m_FontWeight;
		float m_TextX,m_TextY;
		CString m_TextString;
		int TextLong;
		CTextDlg textdlg;
		//颜色传递
		textdlg.pColor = this->m_pColor;

		if(IDOK == textdlg.DoModal())
		{
			//字体距离有关的三个变量均为实际坐标传入

			//m_FontHeight = textdlg.m_high;
			//m_FontWide =  textdlg.m_width;
			//m_FontWeight = textdlg.m_weight;
			m_TextString = textdlg.m_text;
			m_TextAngle = textdlg.m_angle;
			m_FontHeight = VLtoDL(textdlg.m_high);
			m_FontWide   = VLtoDL(textdlg.m_width);
			m_FontWeight = VLtoDL(textdlg.m_weight);
			TextLong = textdlg.m_text.GetLength();


			if(TextLong>0)
			{
				///////坐标转换////////////
				float m_TextX;
				float m_TextY;
				VPtoDP(point.x,point.y,&m_TextX,&m_TextY);
			   ////////////////////////////////
				id_only=pDoc->GetGraphID(3);
				pDoc->AddText(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,m_TextX,m_TextY,
				  				m_TextAngle,VLtoDL(m_FontHeight*scaleNow/scale),VLtoDL(m_FontWide*scaleNow/scale),m_FontWeight, m_TextString)->Draw(&client,0);

			}

		}
	}
	//////////////////绘制圆，点，异型点//////////////////////
	else if( m_DrawCurrent==14||m_DrawCurrent==111||m_DrawCurrent==112)
	{
		if(0==PushNum)
		{
			mPointOrign=point;
			mPointOld=point;
			//////////坐标转化/////////////
			VPtoDP(point.x,point.y,&pstOrign.x,&pstOrign.y);	//获取圆心坐标
			PushNum++;
			SetCapture();

			if(m_DrawCurrent==111||m_DrawCurrent==112)
			{
				id_only=pDoc->GetGraphID(1);
				//mPointOrign.x是圆心的x坐标，mPointOrign.y是圆心的y坐标，5是半径的值

				pDoc->AddCircle(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,pstOrign.x,pstOrign.y,VLtoDL(3*scaleNow/scale),m_DrawCurrent)->Draw(&client,0);//当鼠标点击第一下时，画的是点
				PushNum=0;
				ReleaseCapture();
			}
		}else if(1==PushNum)
		{
			
			if(m_DrawCurrent==14) //圆
			{
				//获取ID
				id_only=pDoc->GetGraphID(1);
				//求半径 
				float r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2)+pow((float)(mPointOrign.y-mPointOld.y),2));
				//View->Doc->Circle构造函数->Circle Draw函数
				//传值时  VLtoDL(r)   x,y,r均为实际坐标
				pDoc->AddCircle(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,pstOrign.x,pstOrign.y,VLtoDL(r*scaleNow/scale),m_DrawCurrent)->Draw(&client,0);
			}
			PushNum =0;
			ReleaseCapture();
		}
      
		
	}
	////////////////////绘制折线和多边形////////////////////////////////////////
	else if(m_DrawCurrent==12||m_DrawCurrent==13)
	{

		//PointXyz[PushNum].x=point.x;
		//PointXyz[PushNum].y=point.y;
		//////////坐标转化/////////////
		VPtoDP(point.x,point.y,&PointXyz[PushNum].x,&PointXyz[PushNum].y);
		if(0==PushNum)
		{
			SetCapture();
			mPointOld = point;
		}
		mPointOrign = mPointOld;
		++PushNum;
	}





	//////////////////添加指北针//////////////////////
	else if(m_DrawCurrent==16)
	{
		if(0==PushNum)
		{
			CString path = GetCurrentPath();
			m_image.Load( path +_T("..\\Cyan_DBA_Lihua\\res\\compass.png"));
			if(m_image.IsNull())
			{
				MessageBox(_T("未找到相关资源"));
			}
			if(m_image.GetBPP()==32)
			{
				int i ,j;
				for(i=0;i<m_image.GetWidth();i++)
				{
					for(j=0;j<m_image.GetHeight();j++)
					{
						byte *pByte=(byte *) m_image.GetPixelAddress(i,j);
						pByte[0]=pByte[0]*pByte[3]/255;
						pByte[1]=pByte[1]*pByte[3]/255;
						pByte[2]=pByte[2]*pByte[3]/255;
					}
				}
			}
			m_image.Draw(client.m_hDC,point.x-10,point.y-10);
			m_image.Destroy();
			++PushNum;//一幅图层仅需一枚指北针
		}
	}

/////////////////////图形操作/////////////////////////////////////////////////////////////////////////////////////
	
	//////////2倍放大////////////
	else if(m_DrawCurrent==411)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		x=a+m_wScreen/4;
		y=b-m_hScreen/4;
		VPtoDP(x,y,&m_originX,&m_originY);
		scale=scale/2;
		Invalidate();

	}
	//////////3倍放大////////////
	else if(m_DrawCurrent==412)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		x=a+m_wScreen/3;
		y=b-m_hScreen/3;
		VPtoDP(x,y,&m_originX,&m_originY);
		scale=scale/3;
		Invalidate();
	}
	
	//////////2倍缩小////////////
	else if(m_DrawCurrent==421)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		scale=scale*2;
		x=a-m_wScreen/4;
		y=b+m_hScreen/4;
		VPtoDP(x,y,&m_originX,&m_originY);
		Invalidate();

	}

	//////////3倍缩小////////////
	else if(m_DrawCurrent==422)
	{
		int a,b;
		float x,y;
		DPtoVP(m_originX,m_originY,&a,&b);
		scale=scale*3;
		x=a-m_wScreen/3;
		y=b+m_hScreen/3;
		VPtoDP(x,y,&m_originX,&m_originY);
		Invalidate();
	}

	///////////////////////平移//////////////////////
	else if(m_DrawCurrent==43)
	{
		if(0==PushNum)	//第一次按下
		{
			mPointOrign = point;
			//mPointOld = point;			//这里用到的绘图模式是使画面更新，所以不用俩个点，一个就够了

			++PushNum;
			SetCapture();	//获取鼠标
		}
	}

	/////////////////框选放大//////////////
	else if(m_DrawCurrent== 45)
	{
		int x0,y0;
		int x, y;
		if(PushNum==0)
		{
			mPointOrign=point;
			mPointOld=point;
			SetCapture();
			++PushNum;
		}
		else if(PushNum==1)
		{
			x0=min(mPointOrign.x,point.x);
			y0=max(mPointOrign.y,point.y);
			x=max(mPointOrign.x,point.x);
			y=min(mPointOrign.y,point.y);
			//x方向放大的比例尺
			float scale1=(float)(x-x0)/(float)m_wScreen;
			//y方向放大的比例尺
			float scale2=(float)(y-y0)/(float)m_hScreen;
			VPtoDP(x0,y0,&m_originX,&m_originY);
			if(scale1>=scale2) //选择二者中更大的
			{
				scale = scale * scale1;
			}		
			else
			{
				scale = scale * scale2;
			}		
			ReleaseCapture();
			PushNum=0;
			Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数
			
		}

	}

	///////////////框选缩小//////////////
	///////////把全屏放到框中/////////////
	else if(m_DrawCurrent== 46)
	{
		int x0,y0;
		int x1,y1;
		int x ,y ;
		if(PushNum==0)
		{
			mPointOrign=point;
			mPointOld=point;
			SetCapture();
			++PushNum;
		}
		else if(PushNum==1)
		{
			x0=min(mPointOrign.x,point.x);
			y0=max(mPointOrign.y,point.y);
			x1=max(mPointOrign.x,point.x);
			y1=min(mPointOrign.y,point.y);
			//x方向缩小的比例尺
			float scale1=(float)(x1-x0)/(float)m_wScreen;
			//y方向缩小的比例尺
			float scale2=(float)(y0-y1)/(float)m_hScreen;
			if(scale1<=scale2) //选择二者中更小的
			{
				scale = scale / scale1;
			}		
			else
			{
				scale = scale / scale2;
			}

			//m_originX = m_originX - scale*x0;
			//m_originY = m_originY -	scale*(m_wScreen -y0);
			x = -x0; //x = x0-x0;
			y =	m_hScreen +(m_hScreen - y0);
			VPtoDP(x,y,&m_originX,&m_originY);

			ReleaseCapture();
			PushNum=0;
			Invalidate();	//使整个窗口客户区无效, 并进行更新显示的函数	  强制触发重绘
			
		}

	}

	//开始路径绘制
    else if(m_DrawCurrent== 511 && light == FALSE)
	{
		 CString str;
		 MapMessage message;
		 if(message.DoModal()== IDOK)
		 {
			 str = message.message;
			 CPoint p; 
			 float x, y;
			 VPtoDP(point.x,point.y,&x,&y);		//逻辑转实际
			 p.x = x;	
			 p.y = y;
			 m_PointMap[m_index] = p;
			 m_StringMap[m_index] = str;	//把字符串存入Map中
			 hash_array[m_index] = 1;	//把哈希值设置为1
			 ++m_index;
		 }
	}

	///////////////点选///////////////
	else if(m_DrawCurrent == 61)
	{
		if(pDoc->n_GraphSelect == 4096*3)
		{
			AfxMessageBox(_T("最多只能选择12288个元素"));
			return ;
		}
		for(int i = 1;i<=3;++i)
		{	
			int n = pDoc->GetGraphUpperBound(i);
			for(int j = 0;j<= n;++j)	
			{
				BOOL a = pDoc->GetGraph(i,j)->IsPoint(&client,point.x,point.y);
				if(a)
				{
					BOOL b = pDoc->AddSelectList(i,j);
					if(b)
					{
						pDoc->GetGraph(i,j)->Draw(&client,1);
					}
				}
			}
		}
	}
	

	////////////////框选/////////////////////
	else if(m_DrawCurrent==62) 
	{	
		if(pDoc->n_GraphSelect == 4096*3)
		{
			AfxMessageBox(_T("最多只能选择12288个元素"));
			return ;
		}
		int x1,y1,x2,y2;//封装边界的坐标值 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
	
		for(int i=1;i<=3; ++i)
		{
			int n=pDoc->GetGraphUpperBound(i);
			for(int j=0;j<=n; ++j)
			{
				BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
				if(a)
				{
					BOOL b = pDoc->AddSelectList(i,j);
					if(b)
					{
						pDoc->GetGraph(i,j)->Draw(&client,1);
					}
				}
			}
		}
	} 

	////////////////减选/////////////////////
	else if(m_DrawCurrent==63) 
	{	
		int x1,y1,x2,y2;//封装边界的坐标值 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
	
		for(int i=1;i<=3; ++i)
		{
			int n= pDoc->GetGraphUpperBound(i);
			for(int j=0;j<=n; ++j)
			{
				BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
				if(a)
				{
					pDoc->DelSelectList(i,j);					
				}
			}
		}
		
		Invalidate();
	} 


	//////////全选////////////	已经在点击事件实现
	//else if(m_DrawCurrent==68)
	//{
	//	
	//	if(pDoc->n_GraphSelect == 4096*3)
	//	{
	//		AfxMessageBox(_T("最多只能选择12288个元素"));
	//		return ;
	//	}
	//	CRect rect( INT_MIN, INT_MIN, INT_MAX, INT_MAX);
	//
	//	for(int i=1;i<=3; ++i)
	//	{
	//		int n=pDoc->GetGraphUpperBound(i);
	//		for(int j=0;j<=n; ++j)
	//		{
	//			BOOL a=pDoc->GetGraph(i,j)->IsRect(&client,rect);
	//			if(a)
	//			{
	//				BOOL b = pDoc->AddSelectList(i,j);
	//				if(b)
	//				{
	//					pDoc->GetGraph(i,j)->Draw(&client,1);
	//				}
	//			}
	//		}
	//	}
	//}














	///输入点确定比例尺//////////
	else if(m_DrawCurrent == 232)
	{
		if(PushNum == 0)
		{
			PushNum++;
			mPointOrign=point;
		}
		else if(PushNum == 1)
		{
			PushNum++;
			mPointOld=point;
			float x1,y1,x2,y2,scale1,scale2;
			BaseMapSet dig;
			dig.minLongitude = "一号点的经度";
			dig.minLatitude = "一号点的纬度";
			dig.maxLongitude = "二号点的经度";
			dig.maxLatitude = "二号点的纬度";
		
			if(dig.DoModal()==IDOK)
			{
				x1=(_ttoi(dig.m1)/60.0+_ttoi(dig.f1))/60.0+_ttoi(dig.d1);
				y1=(_ttoi(dig.m2)/60.0+_ttoi(dig.f2))/60.0+_ttoi(dig.d2);
				x2=(_ttoi(dig.m3)/60.0+_ttoi(dig.f3))/60.0+_ttoi(dig.d3);
				y2=(_ttoi(dig.m4)/60.0+_ttoi(dig.f4))/60.0+_ttoi(dig.d4);
				scale1 = fabs((x2-x1))/(1.0*fabs((double)(mPointOld.x-mPointOrign.x)));
				scale2 = fabs((y2-y1))/(1.0*fabs((double)(mPointOld.y-mPointOrign.y)));
				if(scale1>scale2)
				{
		    		scale=scale1;
				}
				else
				{
		    		scale=scale2;
				}
				m_originX = x1-mPointOrign.x*scale;
				m_originY = y1-scale*(m_hScreen-mPointOrign.y);
			}
			m_originXTo =m_originX;
			m_originYTo=m_originY;
			scale1=scale;
			mapSet = true; 
		}
	}
	////////////////测量//////////////
	else if(m_DrawCurrent == 71)
	{


		
		if(0==PushNum)
		{
			SetCapture();
			mPointOld = point;
		}
		if(PushNum!=0)
		{
			//if(isAdd==true)
			//{
			//	float x1,y1,x2,y2;
			//	VPtoDP(point.x,point.y,&x1,&y1);
			//	VPtoDP(mPointOrign.x,mPointOrign.y,&x2,&y2);
			//	//sumLength += GetDistance(point.x ,point.y,mPointOrign.x,mPointOrign.y);
			//	sumLength += GetDistance(x1,y1,x2,y2);
			//}
			//else
			//{  
				sumLength += (int)sqrt((float)(point.x - mPointOrign.x)*(point.x - mPointOrign.x)+(float)(point.y - mPointOrign.y)*(point.y - mPointOrign.y));	
			//}
		}
		mPointOrign = mPointOld;
		++PushNum;
	}
   /////////////////拉框///////////////////
	else if(m_DrawCurrent == 72)
	{
		int x1,y1,x2,y2;//封装边界的坐标值 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
		client.SelectStockObject(NULL_BRUSH);
		client.Rectangle(x1,y1,x2,y2);
		
	}

	else if(m_DrawCurrent == 73)
	{
		int x1,y1,x2,y2;//封装边界的坐标值 
		CRectTracker tracker;
		tracker.TrackRubberBand(this,point);
		x1=min(tracker.m_rect.left,tracker.m_rect.right);
		y1=min(tracker.m_rect.top,tracker.m_rect.bottom);
		x2=max(tracker.m_rect.right,tracker.m_rect.left);
		y2=max(tracker.m_rect.bottom,tracker.m_rect.top);
		CRect rect(x1,y1,x2,y2);
		client.SelectObject(&m_pen);
		client.Rectangle(x1,y1,x2,y2);
		
	}

/////////////////////////////////////////////////////////
	CFormView::OnLButtonDown(nFlags, point);
}



/////////////鼠标抬起/////////////////////
void CCyan_DBA_LihuaView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	////////完成平移////////////
	if(m_DrawCurrent==43&&PushNum>0)
	{
		PushNum =0;
		ReleaseCapture();	//释放鼠标
	}
	CFormView::OnLButtonUp(nFlags, point);
}


/////////////左键双击///////////
void CCyan_DBA_LihuaView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CCyan_DBA_LihuaDoc* pDoc =GetDocument(); //通过这个函数进行视图和文档的交流,获取文档的指针
	CFormView::OnLButtonDblClk(nFlags, point);
	CClientDC client(this);
	int id_only;
	/////////////完成折线和多边形////////////////////
	if((m_DrawCurrent==12||m_DrawCurrent==13)&&PushNum>0)
	{
		id_only = pDoc->GetGraphID(2);
		VPtoDP(point.x,point.y,&PointXyz[PushNum].x,&PointXyz[PushNum].y);
		++PushNum;
		//PointXyz在单击时已经全部完成坐标系转换
		pDoc->AddPLine(m_pColor,m_brushColor,m_LineWide,m_LineType,id_only,
							PushNum,PointXyz,m_DrawCurrent)->Draw(&client,0);			  
		ReleaseCapture();
		PushNum=0;
	}
	///////////测量//////////////
	else if(71 ==  m_DrawCurrent)
	{
		//VPtoDP(point.x,point.y,&PointXyz[PushNum].x,&PointXyz[PushNum].y);
		++PushNum;
		//PointXyz在单击时已经全部完成坐标系转换
		CString str;
		if(isAdd == true)
		{
			sumLength = VLtoDL(sumLength)*100;
			str.Format(_T("总长度为：%lf KM"),sumLength);
		}
		else
		{
			str.Format(_T("总长度为：%lf "),sumLength);
		}
		
		MessageBox(str,_T("测量长度"),MB_OK);
		sumLength = 0;
		ReleaseCapture();
		PushNum=0;
		Invalidate();
		
	}
}




/////////////鼠标移动事件////////////////////////////
void CCyan_DBA_LihuaView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC client(this);
	//CPen pen;
	//pen.CreatePen(this->m_LineType,(int)this->m_LineWide,m_pColor);
	//client.SelectObject(&pen);
	client.SelectObject(&m_pen);
	client.SetROP2(R2_NOTXORPEN); //选择画笔反色的绘画模式
	float x ;
	float y;
	VPtoDP(point.x,point.y,&x,&y);
	CString str; 
	str.Format(_T("逻辑坐标：x=%d,y=%d   比例尺：%f                实际坐标： x = %f y =%f"),point,scale,x,y);
	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;                                                                        // 获得主窗口指针
	CMFCStatusBar* pStatus=&pFrame->m_wndStatusBar;
	pStatus->SetPaneText(0,str);

	//////////////绘制圆形区域///////////////////////////
	if((14==m_DrawCurrent)&&PushNum>0)//如果是绘制圆或圆形区域，并且已经按下第一点
	{
		//鼠标移动事件不传值，直接用像素模式画，生成动态效果
		if(mPointOld!=point)
		{
			//动态绘图的步骤
			//把mPointOrign->mPointOld 擦除 mPointOld是前一个,所以要差出
			//重新画一个mPointOrign 到point
			float r=(float)sqrt(pow((float)(mPointOrign.x-mPointOld.x),2)+pow((float)(mPointOrign.y-mPointOld.y),2));
			client.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
			r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2)+pow((float)(mPointOrign.y-point.y),2));
			client.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);//从第二次开始，都是先擦除再画图
			mPointOld=point;
		}
	}

	////////////////////绘制折线和多边形////////////////////
	else if((12==m_DrawCurrent||13==m_DrawCurrent)&&PushNum>0)	//按下一次后
	{
		/****************************
		MoveTo:标记为线段第一个点
		LineTo:从第一个点画线到第二个点
		这里由于绘图模式设置为	R2_NOTXORPEN
		所以第一次是以白色绘制
			第二次是以笔色绘制
			看起来像动画
		****************************/
		if(mPointOrign!=point)
		{
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
			mPointOld =point;
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
		}
	}

	////////////测量////////
	else if(71==m_DrawCurrent&&PushNum>0)
	{
		if(mPointOrign!=point)
		{
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
			mPointOld =point;
			client.MoveTo(mPointOrign);
			client.LineTo(mPointOld);
		}
	}

	////////////////////平移////////////////////
	else if(43==m_DrawCurrent&&PushNum>0)
	{
		/*****************************
		  SetCursor(LoadCursor(NULL,IDC_ARROW));

		LoadCursor
		第一个参数：是要载入光标的程序的实例.
			当使用系统预定义光标的时候，要设置为空。
			当要使用自定义光标的时候，设置为AfxGetInstanceHandle()
		第二个参数：
			当第一个参数为NULL时
				DC_APPSTARTING 标准的箭头和小沙漏
				IDC_ARROW 标准的箭头
				IDC_CROSS 十字光标
				IDC_HELP 标准的箭头和问号
				IDC_IBEAM 工字光标
				IDC_NO 禁止圈
				IDC_SIZEALL 四向箭头指向东、西、南、北
				IDC_SIZENESW 双箭头指向东北和西南
				IDC_SIZENS 双箭头指向南北
				IDC_SIZENWSE 双箭头指向西北和东南
				IDC_SIZEWE 双箭头指向东西
				IDC_UPARROW 垂直箭头
				IDC_WAIT 沙漏	（等待圈）
				IDC_NULL 空
				IDC_HAND 手
				IDC_APPSTARTING 箭头加沙漏
			当第二个参数为AfxGetInstanceHandle()时，在资源中画好
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(所画光标的ID)));
		*************************/
		if(mPointOrign!=point)
		{
			SetCursor(LoadCursor(NULL,IDC_SIZEALL));
			VPtoDP(xmove,ymove,&xmoveTo,&ymoveTo);
			m_originX = m_originX - scale*(point.x - mPointOrign.x);
			m_originY = m_originY + scale*(point.y - mPointOrign.y);

			////底图平移
			
			if(isAdd)
			{
				DPtoVP(xmoveTo,ymoveTo,&xmove,&ymove);
			}
			


			mPointOrign = point;
			Invalidate();	//使图形重画
			ReleaseCapture();
		}


	}


	////////////////////框选放大////////////////////
	else if(45==m_DrawCurrent&&PushNum>0)
	{
		if(mPointOld!=point)
		{

			client.Rectangle(mPointOrign.x,mPointOrign.y,mPointOld.x,mPointOld.y);
			client.Rectangle(mPointOrign.x,mPointOrign.y,point.x,point.y);
			mPointOld=point;
		}
	}


	////////////////////框选缩小////////////////////
	else if(46==m_DrawCurrent&&PushNum>0)
	{
		if(mPointOld!=point)
		{
			client.Rectangle(mPointOrign.x,mPointOrign.y,mPointOld.x,mPointOld.y);
			client.Rectangle(mPointOrign.x,mPointOrign.y,point.x,point.y);
			mPointOld=point;
		}
	}
	/////////////////////////////////////////////////
	CFormView::OnMouseMove(nFlags, point);
}








///////////////右键按下/////////////////////////////
void CCyan_DBA_LihuaView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC client(this);
	int x,y;
	float r;
	///////////////////////////
	//CPen pen;
	////将线型改为实线，防止因为虚线擦除出错
	//pen.CreatePen( PS_SOLID,(int)this->m_LineWide,m_pColor);
	//client.SelectObject(pen);
	//////////////////////////////////////
	client.SelectObject(&m_pen);
	client.SetROP2(R2_NOTXORPEN);
	////撤销实际不传入Add函数我们用像素直接画
	////////////撤销圆/////////////////
	if((14==m_DrawCurrent)&&PushNum>0)
	{
		r=(float)sqrt(pow((float)(mPointOrign.x-point.x),2)+pow((float)(mPointOrign.y-point.y),2));
		client.Ellipse(mPointOrign.x-r,mPointOrign.y-r,mPointOrign.x+r,mPointOrign.y+r);
		////强制触发重绘////// 本质上直接重绘就可以了,以上代码都可以省略
		//Invalidate();
		PushNum=0;
		ReleaseCapture();
	}

	///////////////撤销折线多边形//////////////////////
	else if((12==m_DrawCurrent||13==m_DrawCurrent)&&PushNum>0)
	{
		//线
		CPoint *pointArray;
		pointArray = new CPoint[PushNum];
		for(int i =0;i<this->PushNum;++i)  //创建数组存储各折点的值（这些折点都在按下L鼠标后被加入PointXyz）
		{

			 DPtoVP(PointXyz[i].x,PointXyz[i].y,(int *)&pointArray[i].x,(int *)&pointArray[i].y);
		}
		client.Polyline(pointArray,this->PushNum);
		client.MoveTo(mPointOrign);
		client.LineTo(mPointOld);
		////强制触发重绘////// 本质上直接重绘就可以了 ,以上代码都可以省略
		Invalidate();
		/////////
		PushNum=0;
		//memset(PointXyz,0,ArraySize);//清空数组
		ReleaseCapture();
	}
	///////////////////////////////////
	CFormView::OnRButtonDown(nFlags, point);
}






////////////重绘//////////////////////////////
void CCyan_DBA_LihuaView::OnPaint()
{
	//原始图像重绘
	CPaintDC paintDc(this); // device context for painting
	OnDraw(&paintDc);

	//路径重绘
	CString str;
	CPoint p;
	paintDc.SetBkMode(TRANSPARENT);
	paintDc.SelectObject(m_pen);
	
	for(int i = 0; i<m_index; ++i)
	{
		m_PointMap.Lookup(i,p);
		int x,y;
		DPtoVP(p.x,p.y,&x,&y);
		if( i == 0 || ( hash_array[i-1] == 0)) //从0开始，空格为界限
		{
			paintDc.MoveTo(x,y);
		}
		else
		{
			paintDc.LineTo(x,y);
		}
		str.Format(_T("%d"),i);
		paintDc.TextOut(x,y,str);

	}
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
}

void CCyan_DBA_LihuaView::OnDraw(CDC *pDC)
{
	CCyan_DBA_LihuaDoc* pDoc =GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	{
		return;
	}
	//画底图
	ImgCenterDib *pDib = pDoc->GetPDib();
	//CSize sizeFileDib = pDib->GetDimensions();
	//imgWidth = sizeFileDib.cx;
	//imgHeight = sizeFileDib.cy;
	
	//pDib->Draw(pDC,CPoint(xmove,ymove),sizeFileDib);
	CSize size;
	size.cx = m_wScreen;
	size.cy = m_hScreen;
	pDib->Draw(pDC,CPoint(xmove,ymove),size);
	//画矢量图形
	pDoc->DocDraw(pDC,0);

	
}

/////////////(默认自动调用)取屏幕大小///////////////////
void CCyan_DBA_LihuaView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_wScreen=cx;	
	m_hScreen=cy;
}

//////////////获取屏幕高度/////////////////
int CCyan_DBA_LihuaView::GetScreenH()
{
	return this->m_hScreen;
}

//////////////获取屏幕宽度///////////////
int CCyan_DBA_LihuaView::GetScreenW()
{
	return this->m_wScreen;
}


double CCyan_DBA_LihuaView::rad(double d)	//获取弧度
{
	return d * pi * 180.0;
}

//////////传入经纬度///////////
double CCyan_DBA_LihuaView::GetDistance(double lng1,double lat1,double lng2,double lat2)	//获取长度
{
	double radLat1 = rad(lat1);
	double radLat2 = rad(lat2);
	double a = radLat1 - radLat2;
	double b = rad(lng1) - rad(lng2);
	double s = asin(sqrt(pow(sin(a/2),2) + cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
	s = s * EARTH_RADIUS;
	return s;
}







