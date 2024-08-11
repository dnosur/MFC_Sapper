
// SapperDlg.h: файл заголовка
//

#pragma once
#include "GameSettings.h"
#include "GameEnd.h"
#include "Field.h"

// Диалоговое окно CSapperDlg
class CSapperDlg : public CDialogEx
{
	const int screenWidth = 1280;
	const int screenHeight = 720;

	bool start, end, win;

	int mines, width, height;

	Field field;

	void Start(), End();
// Создание
public:
	CSapperDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAPPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};
