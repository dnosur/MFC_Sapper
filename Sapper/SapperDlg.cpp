
// SapperDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Sapper.h"
#include "SapperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CSapperDlg
void CSapperDlg::Start()
{
	GameSettings gameSettings;
	if (!gameSettings.DoModal() || !gameSettings.success) {
		return EndDialog(IDOK);
	}

	mines = gameSettings.mines;
	width = gameSettings.width;
	height = gameSettings.height;

	field = Field(width, height, mines);
	start = true;
	end = false;

	Invalidate();
}

void CSapperDlg::End()
{
	GameEnd gameEnd(win);
	if (!gameEnd.DoModal() || !gameEnd.retry) {
		return EndDialog(IDOK);
	}

	start = end = win = false;

	Start();
}

CSapperDlg::CSapperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAPPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	start = end = win = false;
	mines = width = height = 0;

	if (!AllocConsole()) {
		AfxMessageBox(_T("Failed to create the console!"), MB_ICONEXCLAMATION);
	}
}

void CSapperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSapperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()


// Обработчики сообщений CSapperDlg

BOOL CSapperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Start();
	SetWindowPos(NULL, 0, 0, screenWidth, screenHeight, SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CSapperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSapperDlg::OnPaint()
{
	if (!start) {
		return;
	}

	CPaintDC dc(this);
	field.Draw(dc);

	if (field.Win()) {
		end = win = true;
	}

	if (!end) {
		return;
	}

	End();
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSapperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSapperDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	if (field.Set(point, end)) {
		Invalidate();
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CSapperDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (field.SetMarker(point)) {
		Invalidate();
	}
	CDialogEx::OnRButtonDblClk(nFlags, point);
}
