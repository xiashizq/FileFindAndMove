
// FileFindAndMoveDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FileFindAndMove.h"
#include "FileFindAndMoveDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>
#include <windows.h>
#include <wchar.h>
#include <list>
#include "resource.h"
#include <algorithm>
using namespace std;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFileFindAndMoveDlg 对话框



CFileFindAndMoveDlg::CFileFindAndMoveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEFINDANDMOVE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CFileFindAndMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST2, m_list2);
	DDX_Control(pDX, IDC_LIST3, m_list3);
}

BEGIN_MESSAGE_MAP(CFileFindAndMoveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFileFindAndMoveDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_QUERYFILE, &CFileFindAndMoveDlg::OnBnClickedButtonQueryfile)
	ON_BN_CLICKED(IDC_BUTTON_GETLISTINFO, &CFileFindAndMoveDlg::OnBnClickedButtonGetlistinfo)
	ON_BN_CLICKED(IDC_BUTTON_SELECTALL, &CFileFindAndMoveDlg::OnBnClickedButtonSelectall)
	ON_BN_CLICKED(IDC_BUTTON_SELECTINVERT, &CFileFindAndMoveDlg::OnBnClickedButtonSelectinvert)
	ON_BN_CLICKED(IDC_BUTTON_QXSELECT, &CFileFindAndMoveDlg::OnBnClickedButtonQxselect)
	ON_BN_CLICKED(IDC_BUTTON_SELECTOUTPUT, &CFileFindAndMoveDlg::OnBnClickedButtonSelectoutput)
	ON_BN_CLICKED(IDC_BUTTON_ADDKEYWORD, &CFileFindAndMoveDlg::OnBnClickedButtonAddkeyword)
	ON_BN_CLICKED(IDC_BUTTON_DELETEKEY, &CFileFindAndMoveDlg::OnBnClickedButtonDeletekey)
END_MESSAGE_MAP()


// CFileFindAndMoveDlg 消息处理程序

BOOL CFileFindAndMoveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// TODO: 在此添加额外的初始化代码

	//初始化标题
	CString title = _T("文件筛选及复制器");
	this->SetWindowText(title);


	DWORD dwStyle = m_list.GetExtendedStyle();   //listcontrol部分  
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_CHECKBOXES;
	m_list.SetExtendedStyle(dwStyle);
	m_list.DeleteAllItems();
	m_list.InsertColumn(0, _T(""), LVCFMT_CENTER, 120);
	m_list.InsertColumn(1, _T("文件名"), LVCFMT_CENTER, 120);
	m_list.InsertColumn(2, _T("文件类型"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, _T("文件大小"), LVCFMT_CENTER, 140);
	m_list.InsertColumn(4, _T("存放路径"), LVCFMT_LEFT, 500);

	DWORD dwStyle1 = m_list2.GetExtendedStyle();
	m_list2.SetExtendedStyle(dwStyle1);
	m_list2.DeleteAllItems();
	m_list2.InsertColumn(0, _T("原文件路径"), LVCFMT_CENTER, 300);
	m_list2.InsertColumn(1, _T("迁移后文件路径"), LVCFMT_CENTER, 300);
	m_list2.InsertColumn(2, _T("迁移结果"), LVCFMT_CENTER, 120);

	DWORD dwStyle2 = m_list3.GetExtendedStyle();
	m_list3.SetExtendedStyle(dwStyle2);
	m_list3.DeleteAllItems();
	m_list3.InsertColumn(0, _T("关键词"), LVCFMT_CENTER, 100);

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileFindAndMoveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileFindAndMoveDlg::OnPaint()
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
HCURSOR CFileFindAndMoveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//判断中文字符匹配函数
std::vector<int> stringToVecInt(const std::string& str)
{
	union {
		char c[2];
		int  i;
	} convert;

	// 段位清零
	convert.i = 0;

	std::vector<int> vec;

	for (unsigned i = 0; i < str.length(); i++) {
		// GBK编码首字符大于0x80
		if ((unsigned)str[i] > 0x80) {
			// 利用union进行转化，注意是大端序
			convert.c[1] = str[i];
			convert.c[0] = str[i + 1];
			vec.push_back(convert.i);
			i++;
		}
		else
			// 小于0x80，为ASCII编码，一个字节
			vec.push_back(str[i]);
	}
	return vec;
}
bool include(const std::string& str, const std::string& msg)
{
	auto sour = stringToVecInt(str);
	auto find = stringToVecInt(msg);
	return std::search(sour.begin(), sour.end(), find.begin(), find.end()) != sour.end();
}

//文件搜索、递归搜索
void CFileFindAndMoveDlg::ScanFile(CString Dir)
{
	CFileFind finder;
	CString Add = L"\\*";
	CString DirSpec = Dir + Add;                        //补全要遍历的文件夹的目录
	BOOL bWorking = finder.FindFile(DirSpec);
	CString fontName, lastType, filepath, filename, filesize;//存储切割结果
	int i; //用于定位字符，作为下标
	int index = 0;    //用于列表索引
	CString edit2text;
	GetDlgItem(IDC_EDIT2)->GetWindowText(edit2text);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDots())              //扫描到的不是节点
		{
			if (finder.IsDirectory())           //扫描到的是文件夹
			{
				CString strDirectory = finder.GetFilePath();
				ScanFile(strDirectory);           //递归调用ScanFile（）
			}
			else                               //扫描到的是文件
			{
				//CString strFile = finder.GetFilePath();     得到文件的全路径
							   //进行一系列自定义操作
				filename = finder.GetFileName();
				
				//AfxMessageBox(edit2text);
				//AfxMessageBox(filename);
				//int flag = filename.Find(edit2text);
				//AfxMessageBox(filename.Find(edit2text));

				USES_CONVERSION;
				string filename_str(W2A(filename));
				if (m_list3.GetItemCount() == 0) {
					//假设文件夹里面全是图片，获取图片文件长度
					DWORD imageSize = finder.GetLength();
					filepath = finder.GetFilePath();
					for (i = 0;i < filename.GetLength();i++)
					{
						if (filename[i] == '.')
						{
							fontName = filename.Mid(0, i);
							lastType = filename.Mid(i + 1, filename.GetLength());

							filesize.Format(_T("%d"), imageSize / 1024);
							filesize += "k";
							//m_list.InsertItem(index, fontName);
							m_list.InsertItem(index, _T(""));
							m_list.SetItemText(index, 1, fontName);
							m_list.SetItemText(index, 2, lastType);
							m_list.SetItemText(index, 3, filesize);
							m_list.SetItemText(index, 4, filepath);
						}
					}
					index++;
				}
				else {
					for (int i = 0; i < m_list3.GetItemCount(); i++) {
						CString keywords_list = m_list3.GetItemText(i, 0);
						string keywords_list_str(W2A(keywords_list));
						//AfxMessageBox(keywords_list);
						if (include(filename_str, keywords_list_str)) {
							//假设文件夹里面全是图片，获取图片文件长度
							DWORD imageSize = finder.GetLength();
							filepath = finder.GetFilePath();
							for (i = 0;i < filename.GetLength();i++)
							{
								if (filename[i] == '.')
								{
									fontName = filename.Mid(0, i);
									lastType = filename.Mid(i + 1, filename.GetLength());

									filesize.Format(_T("%d"), imageSize / 1024);
									filesize += "k";
									//m_list.InsertItem(index, fontName);
									m_list.InsertItem(index, _T(""));
									m_list.SetItemText(index, 1, fontName);
									m_list.SetItemText(index, 2, lastType);
									m_list.SetItemText(index, 3, filesize);
									m_list.SetItemText(index, 4, filepath);
								}
							}
							index++;
						}
					}
				}
				//string edit2text_str(W2A(edit2text));



			}

		}
	}
	finder.Close();
}


//选择文件路径
void CFileFindAndMoveDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR   szPath[MAX_PATH] = { 0 };
	LPITEMIDLIST   pitem;
	BROWSEINFO   info;
	::ZeroMemory(&info, sizeof(info));
	info.hwndOwner = this->m_hWnd;
	info.lpszTitle = _T("请选择路径: ");
	info.pszDisplayName = szPath;
	if (pitem = ::SHBrowseForFolder(&info))
	{
		::SHGetPathFromIDList(pitem, szPath);
		CString m_Path = szPath;

		CString str = m_Path += "\\";
		GetDlgItem(IDC_EDIT1)->SetWindowText(str);
	}
}

//查询文件
void CFileFindAndMoveDlg::OnBnClickedButtonQueryfile()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	CString edit1text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(edit1text);
	if (edit1text == "") {
		AfxMessageBox(_T("未选择输入文件夹"));
	}
	else {
		ScanFile(edit1text);
	}

	

}


void CFileFindAndMoveDlg::OnBnClickedButtonGetlistinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString str;
	//for (int i = 0; i < m_list.GetItemCount(); i)
	//{
	//	if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
	//	{
	//		str.Format(_T("选中了第%d行"), i);

	//		AfxMessageBox(str);
	//	}
	//}

	/*CString str;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!/n");
	else
	{
		while (pos)
		{
			int nItem = m_list.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!/n", nItem);
			str.Format(_T("选中了第%d行"), nItem);
			AfxMessageBox(str);
		}
	}*/
	CString str;
	CString edit3text;
	GetDlgItem(IDC_EDIT3)->GetWindowText(edit3text);
	int i; //用于定位字符，作为下标
	int index = 0;    //用于列表索引
	if (edit3text == "") {
		AfxMessageBox(_T("未选择输出文件夹"));
	}
	else {
		for (int i = 0; i < m_list.GetItemCount(); i++)
		{
			if (m_list.GetCheck(i))
			{
				//str.Format(_T("第%d行的checkbox为选中状态"), i);
				CString filename_list = m_list.GetItemText(i, 1);
				CString filetype_list = m_list.GetItemText(i, 2);
				CString outputstring = edit3text + filename_list + "." + filetype_list;
				//AfxMessageBox(outputstring);
				CString str1 = m_list.GetItemText(i, 4);
				BOOL flat = CopyFile(str1, outputstring, false);   //复制文件

				if (flat) {
					m_list2.InsertItem(index, str1);
					m_list2.SetItemText(index, 1, outputstring);
					m_list2.SetItemText(index, 2, _T("复制成功"));
				}
				else {
					m_list2.InsertItem(index, str1);
					m_list2.SetItemText(index, 1, outputstring);
					m_list2.SetItemText(index, 2, _T("复制失败"));
				}
				//AfxMessageBox(str1);
			}
		}
	}





}


void CFileFindAndMoveDlg::OnBnClickedButtonSelectall()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0;i < m_list.GetItemCount();i++)
	{
		m_list.SetCheck(i, TRUE);
	}
}


void CFileFindAndMoveDlg::OnBnClickedButtonSelectinvert()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0;i < m_list.GetItemCount();i++)
	{
		if (m_list.GetCheck(i) == FALSE)  //未被选中的
		{
			m_list.SetCheck(i, TRUE);
		}
		else  //选中的
		{
			m_list.SetCheck(i, FALSE);
		}
	}
}


void CFileFindAndMoveDlg::OnBnClickedButtonQxselect()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0;i < m_list.GetItemCount();i++)
	{
		m_list.SetCheck(i, FALSE);
	}
}


void CFileFindAndMoveDlg::OnBnClickedButtonSelectoutput()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR   szPath[MAX_PATH] = { 0 };
	LPITEMIDLIST   pitem;
	BROWSEINFO   info;
	::ZeroMemory(&info, sizeof(info));
	info.hwndOwner = this->m_hWnd;
	info.lpszTitle = _T("请选择路径: ");
	info.pszDisplayName = szPath;
	if (pitem = ::SHBrowseForFolder(&info))
	{
		::SHGetPathFromIDList(pitem, szPath);
		CString m_Path = szPath;

		CString str = m_Path += "\\";
		GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	}
}


void CFileFindAndMoveDlg::OnBnClickedButtonAddkeyword()
{
	// TODO: 在此添加控件通知处理程序代码
	CString edit4text;
	GetDlgItem(IDC_EDIT4)->GetWindowText(edit4text);
	m_list3.InsertItem(1, edit4text, LVCFMT_LEFT);
}


void CFileFindAndMoveDlg::OnBnClickedButtonDeletekey()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list3.GetFirstSelectedItemPosition();

	while (pos)
	{
		int nSelected = m_list3.GetNextSelectedItem(pos); //获取选中行的索引
		m_list3.DeleteItem(nSelected); //根据索引删除
		pos = m_list3.GetFirstSelectedItemPosition();
	}

}
