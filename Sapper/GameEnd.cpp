// GameEnd.cpp: файл реализации
//

#include "pch.h"
#include "Sapper.h"
#include "afxdialogex.h"
#include "GameEnd.h"


// Диалоговое окно GameEnd

IMPLEMENT_DYNAMIC(GameEnd, CDialogEx)

GameEnd::GameEnd(bool win, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent), retry(false), win(win)
{

}

GameEnd::~GameEnd()
{
}

void GameEnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameEnd, CDialogEx)
	ON_BN_CLICKED(IDOK, &GameEnd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GameEnd::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Обработчики сообщений GameEnd


void GameEnd::OnBnClickedOk()
{
	retry = true;
	CDialogEx::OnOK();
}


void GameEnd::OnBnClickedCancel()
{
	retry = false;
	CDialogEx::OnCancel();
}


void GameEnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	m_fontGameOver.CreatePointFont(300, _T("Arial"));
	COLORREF m_colorGameOver = !win ? RGB(255, 0, 0) : RGB(0, 255, 0);

	CFont* pOldFont = dc.SelectObject(&m_fontGameOver);
	dc.SetTextColor(m_colorGameOver);
	dc.SetBkMode(TRANSPARENT);

	CRect rectGameOver;
	GetClientRect(&rectGameOver);
	rectGameOver.top = 20;
	rectGameOver.bottom = 100;
	dc.DrawText(!win ? _T("Вы проиграли!") : _T("Поле успешно разминировано!"), &rectGameOver, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.SelectObject(pOldFont);
}
