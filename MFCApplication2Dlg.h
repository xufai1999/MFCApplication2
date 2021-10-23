// MFCApplication2Dlg.h: 头文件
//

#pragma once


// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonGraying();
	afx_msg void OnBnClickedButtonGraylevel();
	afx_msg void OnBnClickedButtonGrayEqualization();
	afx_msg void OnBnClickedButtonGrad();
	afx_msg void OnBnClickedButtonLaplace();
	afx_msg void OnBnClickedButtonRoberts();
	afx_msg void OnBnClickedButtonSobel();
	afx_msg void OnBnClickedButtonLap();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonPrewitt();
	afx_msg void OnBnClickedButtonCanny();
	afx_msg void OnBnClickedButtonAve();
	afx_msg void OnBnClickedButtonMid();
	afx_msg void OnBnClickedButtonWin();
	afx_msg void OnBnClickedButtonAffine();
	afx_msg void OnBnClickedButtonQuad();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};
