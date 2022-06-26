
// FileFindAndMoveDlg.h: 头文件
//

#pragma once


// CFileFindAndMoveDlg 对话框
class CFileFindAndMoveDlg : public CDialogEx
{
// 构造
public:
	CFileFindAndMoveDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEFINDANDMOVE_DIALOG };
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
	void ScanFile(CString Dir);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	CListCtrl m_list;
	afx_msg void OnBnClickedButtonQueryfile();
	afx_msg void OnBnClickedButtonGetlistinfo();
	afx_msg void OnBnClickedButtonSelectall();
	afx_msg void OnBnClickedButtonSelectinvert();
	afx_msg void OnBnClickedButtonQxselect();
	afx_msg void OnBnClickedButtonSelectoutput();
	CListCtrl m_list2;
	CListCtrl m_list3;
	afx_msg void OnBnClickedButtonAddkeyword();
	afx_msg void OnBnClickedButtonDeletekey();
};
