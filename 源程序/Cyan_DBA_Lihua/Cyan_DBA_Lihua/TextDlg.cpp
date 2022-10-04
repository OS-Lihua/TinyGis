// TextDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "TextDlg.h"
#include "afxdialogex.h"

// CTextDlg 对话框

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDlg::IDD, pParent)
	//, SWeight(_T(""))
{

	m_text = _T("");
	m_high = 20;
	m_width = 18;
	m_angle = 0;
	m_weight = 0;
}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSign, m_text);
	DDX_Text(pDX, IDC_EDITHeight, m_high);
	DDX_Text(pDX, IDC_EDITWeight, m_width);
	DDX_Text(pDX, IDC_EDITAngle, m_angle);
	DDX_Control(pDX, IDC_SLIDERText, m_slider);
	DDX_Slider(pDX, IDC_SLIDERText, m_weight);
	DDV_MinMaxInt(pDX, m_weight, 0, 1000);
	//DDX_Text(pDX, IDC_STATICWeight, SWeight);
	DDX_Control(pDX, IDC_EDITHeight, m_EditHigh);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERText, &CTextDlg::OnNMCustomdrawSlidertext)
	ON_EN_KILLFOCUS(IDC_EDITHeight, &CTextDlg::OnEnKillfocusEditheight)
END_MESSAGE_MAP()


// CTextDlg 消息处理程序


void CTextDlg::OnNMCustomdrawSlidertext(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	///////////绑定IDC_STATICWeight////////////////////
	this->m_slider.SetRange(0,1000);//设置控件范围为1-1000
	CSliderCtrl*pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDERText);
	SetDlgItemInt(IDC_STATICWeight,pSlider->GetPos());
	///////////////////////////////
	CDC* pDC =GetDC();
	int high,width ,angleText;
	high = this->m_high;
	width =this->m_width;
	angleText =(int)this->m_angle*10;
	if(this->m_high>=30) high =30;
	if(this->m_width>=30) width =30;
	if(this->m_text.GetLength()*width>100) 
	{
		high =10;
		width =10;
	}
	CFont myFont;
	myFont.CreateFont(high,width,angleText,0,this->m_weight,0,0,0,1,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,_T("myfont"));
	CFont* font = pDC->SelectObject(&myFont);
	CRect rc(250,30,500,250);
	CBrush bkBrush(pDC->GetBkColor());	//设置笔刷颜色
	pDC->FillRect(&rc,&bkBrush);
	pDC->SetTextColor(RGB(0,0,0));	//设置文本颜色
	//pDC->SetTextColor(pColor);	   //设置文本颜色
	pDC->TextOut(375,140,this->m_text);
	/////////////////////
	*pResult = 0;
}

//在m_EditHigh失去焦点
void CTextDlg::OnEnKillfocusEditheight()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString msg;
	//msg.Format(_T("文本高度不得为 : %d"), m_high);	
    float aa = m_high;
    UpdateData(true);
    if ( 0 == m_high)
    {
        MessageBox(_T("文本高度不得为 0 "),_T("数值超出范围! "),  MB_ICONERROR|MB_OK);
        m_high = aa;
        UpdateData(false);
	}
}
