	// ColorTool.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "ColorTool.h"
#include "afxdialogex.h"


// ColorTool 对话框

IMPLEMENT_DYNAMIC(ColorTool, CDialogEx)

ColorTool::ColorTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(ColorTool::IDD, pParent)
	, num(_T(""))
{

	m_slider = 0;
}

ColorTool::~ColorTool()
{
}

void ColorTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOLineType, type);
	DDX_Control(pDX, IDC_SLIDERWide, slider);
	DDX_Slider(pDX, IDC_SLIDERWide, m_slider);
	DDX_Text(pDX, IDC_STATICNum, num);
}


BEGIN_MESSAGE_MAP(ColorTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONPen, &ColorTool::OnBnClickedButtonpen)
	ON_BN_CLICKED(IDC_BUTTONBrush, &ColorTool::OnBnClickedButtonbrush)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERWide, &ColorTool::OnNMCustomdrawSliderwide)
	ON_BN_CLICKED(IDOK, &ColorTool::OnBnClickedOk)
END_MESSAGE_MAP()


// ColorTool 消息处理程序

//画笔颜色
void ColorTool::OnBnClickedButtonpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//画笔颜色
	CDC* pDC =GetDC();
	CColorDialog dlgColor;

	//调色板
	dlgColor.m_cc.Flags|=CC_RGBINIT|CC_FULLOPEN;

	if(IDOK == dlgColor.DoModal())
	{
		pen.DeleteObject();
		penCo1or =dlgColor.GetColor();
		pen.CreatePen(linetype,2,penCo1or);
	}
	//预览颜色
	CRect rc(330,100,360,130);
	CBrush bkBrush(this->penCo1or);
	pDC->FillRect(&rc,&bkBrush);
}

//画刷颜色
void ColorTool::OnBnClickedButtonbrush()
{
	// TODO: 在此添加控件通知处理程序代码
	//画刷颜色
	CDC* pDC =GetDC();
	CColorDialog dlgColor;

	dlgColor.m_cc.Flags|=CC_RGBINIT|CC_FULLOPEN;

	if(IDOK == dlgColor.DoModal())
	{
		brush.DeleteObject();
		brushCo1or =dlgColor.GetColor();
	}
	//预览颜色
	CRect rc(330,160,360,190);
	CBrush bkBrush(this->brushCo1or);
	pDC->FillRect(&rc,&bkBrush);
}

////线型///////////
BOOL ColorTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  
	CSliderCtrl*pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDERWide);
	pSlider->SetRange(0,100);
	pSlider->SetRange(m_slider,100,TRUE);
	pSlider->SetPos(1);
	num ="1";
	type.AddString(_T("实线_____________________"));
	type.AddString(_T("虚线 _ _ _ _ _ _ _ _ _ _ "));
	type.AddString(_T("双点划线 _ _ __ _ _ ___ _"));
	//type.AddString(_T("内框线_ __ __ __ __  __ _"));	
	type.AddString(_T("        空  笔           "));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ColorTool::OnNMCustomdrawSliderwide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int n =(unsigned char)type.GetCurSel();
	UpdateData(true);
	if((n!=0)&& this->slider.GetPos()!=1)
	{
		this->slider.SetPos(1);
		MessageBox(_T(" 已将宽度强制设置为 1 "),_T(" 非实线的宽度不得超过1 "), MB_ICONWARNING|MB_OK);
		UpdateData(false);
	}
	
	CSliderCtrl*pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDERWide);
	SetDlgItemInt(IDC_STATICNum,pSlider->GetPos());
	*pResult = 0;
}


void ColorTool::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/**************
	CPen(int nPenStyle,int nWidth,COLORREF crColor)：
	参数（Parameter）	注释（Annotation）
	PS_SOLID		创建一个实线画笔
	PS_DASH			创建一个虚线画笔，该值只有当画笔宽度小于1个设备单位或更小时才有效
	PS_DOT			同上
	PS_DASHDOT		同上
	PS_DASHDOTDOT	创建一个双点线画笔，该值只有当画笔宽度小于1个设备单位或更小时才有效
	PS_NULL			创建一个空线画笔
	PS_INSIDEFRAME	创建一个内框线画笔，该画笔可以在Windows GDI输出函数定义的矩形边界所生成的封闭状的边框内绘制直线
	***********/
	int n =(unsigned char)type.GetCurSel();
	switch(n)
	{
	case 0:
		linetype =PS_SOLID;
		break;
	case 1:
		linetype = PS_DASH;	
		break;
	case 2:
		linetype =	PS_DASHDOTDOT;	
		break;
	//case 3:
	//	linetype=PS_INSIDEFRAME;
	//	break;
	case 3:
		linetype=PS_NULL;
		break;
	default:
		linetype = PS_SOLID;
		break;
	}
	CDialogEx::OnOK();
}
