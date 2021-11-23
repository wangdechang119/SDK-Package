
// GUIDemoDlg.cpp : ʵ���ļ�
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


// CGUIDemoDlg �Ի���



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


// CGUIDemoDlg ��Ϣ�������

BOOL CGUIDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Login("user", "password");
	//Login("�û�", "mima");
	InitWithoutModelFile(15, 15, 5);	//��ʼ�����̴�СΪ15x15�������ӻ�ʤ���������壩
	//InitWithoutModelFile(19, 19, 6);	//��ʼ�����̴�СΪ19x19�������ӻ�ʤ
	//if (!InitFromModelFile("model.mod"))	//ʹ��ģ���ļ���ʼ��
		//AfxMessageBox(_T("��ʼ��ʧ��"));

	GetDlgItem(ID_NEXT)->EnableWindow(false);
	GetDlgItem(IDC_SAVE)->EnableWindow(false);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGUIDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGUIDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGUIDemoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	StartNewGame();
	DrawBoard(&m_objBoard);
	GetDlgItem(ID_NEXT)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(false);
	GetDlgItem(IDC_SAVE)->EnableWindow(true);
}


void CGUIDemoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CGUIDemoDlg::OnBnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!SetPieceByAIAndShow(&m_objBoard))
	{
		int nPoint = GetPoint();
		AfxMessageBox(_T("���ֲ�����������⣬��ȷ�����糩ͨ�һ��ֳ��㣨���ǻ��ֲ��㣬��ֵ��ɼ������ζԾ֣�"));
	}
	if (IsGameOver())
	{
		GetDlgItem(ID_NEXT)->EnableWindow(false);
		GetDlgItem(IDOK)->EnableWindow(true);
		int nWinner = GetWinner();
		switch (nWinner)
		{
		case -1:
			AfxMessageBox(_T("�����ʤ"));
			break;
		case 1:
			AfxMessageBox(_T("�����ʤ"));
			break;
		case 0:
			AfxMessageBox(_T("ƽ��"));
		}
	}
}


void CGUIDemoDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveModel("model.mod");		//���浱ǰ�Ѿ�ѧϰ����ģ�ͣ���������ʼ��ʹ�ã��Ա㲻��ѧϰ����
	SaveSteps("data.txt");		//���汾�ζԾֵ�������ݣ��ӵ�һ�������һ��������
}
