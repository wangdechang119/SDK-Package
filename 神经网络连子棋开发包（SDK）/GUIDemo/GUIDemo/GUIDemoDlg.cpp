
// GUIDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GUIDemo.h"
#include "GUIDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Inter.h"
#pragma comment(lib, "AIWZQDll.lib")


// CGUIDemoDlg 对话框



CGUIDemoDlg::CGUIDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GUIDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGUIDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOARD, m_objBoard);
}

BEGIN_MESSAGE_MAP(CGUIDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGUIDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGUIDemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_NEXT, &CGUIDemoDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_SAVE, &CGUIDemoDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CGUIDemoDlg 消息处理程序

BOOL CGUIDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Login("user", "password");
	//Login("用户", "mima");
	InitWithoutModelFile(15, 15, 5);	//初始化棋盘大小为15x15，五连子获胜（即五子棋）
	//InitWithoutModelFile(19, 19, 6);	//初始化棋盘大小为19x19，六连子获胜
	//if (!InitFromModelFile("model.mod"))	//使用模型文件初始化
		//AfxMessageBox(_T("初始化失败"));

	GetDlgItem(ID_NEXT)->EnableWindow(false);
	GetDlgItem(IDC_SAVE)->EnableWindow(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGUIDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGUIDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGUIDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	StartNewGame();
	DrawBoard(&m_objBoard);
	GetDlgItem(ID_NEXT)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(false);
	GetDlgItem(IDC_SAVE)->EnableWindow(true);
}


void CGUIDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CGUIDemoDlg::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!SetPieceByAIAndShow(&m_objBoard))
	{
		int nPoint = GetPoint();
		AfxMessageBox(_T("积分不足或网络问题，请确保网络畅通且积分充足（若是积分不足，充值后可继续本次对局）"));
	}
	if (IsGameOver())
	{
		GetDlgItem(ID_NEXT)->EnableWindow(false);
		GetDlgItem(IDOK)->EnableWindow(true);
		int nWinner = GetWinner();
		switch (nWinner)
		{
		case -1:
			AfxMessageBox(_T("黑棋获胜"));
			break;
		case 1:
			AfxMessageBox(_T("白棋获胜"));
			break;
		case 0:
			AfxMessageBox(_T("平局"));
		}
	}
}


void CGUIDemoDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveModel("model.mod");		//保存当前已经学习出的模型，供后续初始化使用，以便不断学习进化
	SaveSteps("data.txt");		//保存本次对局的棋局数据：从第一步到最后一步的落子
}
