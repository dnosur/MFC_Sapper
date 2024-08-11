#pragma once
#include "afxdialogex.h"


// Диалоговое окно GameSettings

class GameSettings : public CDialogEx
{
	DECLARE_DYNAMIC(GameSettings)

	int mines, width, height;
	int minesMax;

	const int widthMax = 20;
	const int heightMax = 20;

	bool success;

	void MathMaxMinesCount();

	void SetSlider(int& value, int sliderId, int staticId, int sliderSize = 10);
	void SetSliderPos(int value, int sliderId, int staticId, int sliderSize = 10);
public:
	GameSettings(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~GameSettings();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
