#pragma once
#include "afxdialogex.h"


// Диалоговое окно GameEnd

class GameEnd : public CDialogEx
{
	DECLARE_DYNAMIC(GameEnd)

	CFont m_fontGameOver;
	bool retry, win;
public:
	GameEnd(bool win = false, CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~GameEnd();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
};
