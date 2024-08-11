// GameSettings.cpp: файл реализации
//

#include "pch.h"
#include "Sapper.h"
#include "afxdialogex.h"
#include "GameSettings.h"


// Диалоговое окно GameSettings

IMPLEMENT_DYNAMIC(GameSettings, CDialogEx)

void GameSettings::MathMaxMinesCount()
{
	minesMax = width + height;
}

void GameSettings::SetSlider(int& value, int sliderId, int staticId, int sliderSize)
{
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(sliderId);
	CStatic* label = (CStatic*)GetDlgItem(staticId);

	slider->SetRange(1, sliderSize);
	value = slider->GetPos();

	CString str;
	str.Format(L"%d", value);
	label->SetWindowTextW(str);
}

void GameSettings::SetSliderPos(int value, int sliderId, int staticId, int sliderSize)
{
	CSliderCtrl* slider = (CSliderCtrl*)GetDlgItem(sliderId);
	CStatic* label = (CStatic*)GetDlgItem(staticId);

	slider->SetRange(1, sliderSize);
	slider->SetPos(value);

	CString str;
	str.Format(L"%d", value);
	label->SetWindowTextW(str);
}

GameSettings::GameSettings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent), 
	mines(10), width(10), height(10), success(false)
{
	MathMaxMinesCount();
}

GameSettings::~GameSettings()
{
}

void GameSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameSettings, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &GameSettings::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &GameSettings::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &GameSettings::OnNMCustomdrawSlider3)
	ON_BN_CLICKED(IDOK, &GameSettings::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GameSettings::OnBnClickedCancel)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// Обработчики сообщений GameSettings


void GameSettings::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(width, IDC_SLIDER1, IDC_WIDTH, widthMax);
	MathMaxMinesCount();
	*pResult = 0;
}


void GameSettings::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(height, IDC_SLIDER2, IDC_HEIGHT, heightMax);
	MathMaxMinesCount();
	*pResult = 0;
}


void GameSettings::OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetSlider(mines, IDC_SLIDER3, IDC_MINES, minesMax);
	*pResult = 0;
}


void GameSettings::OnBnClickedOk()
{
	success = true;
	CDialogEx::OnOK();
}


void GameSettings::OnBnClickedCancel()
{
	success = false;
	CDialogEx::OnCancel();
}


void GameSettings::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	SetSliderPos(width, IDC_SLIDER1, IDC_WIDTH, widthMax);
	SetSliderPos(height, IDC_SLIDER2, IDC_HEIGHT, heightMax);
	SetSliderPos(mines, IDC_SLIDER3, IDC_MINES, minesMax);
}
