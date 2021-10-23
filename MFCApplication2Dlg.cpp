
// MFCApplication2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include "noise.h"
#include "camera.h"

#include <algorithm>
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace cv;
using namespace std;

CString strFilePath;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication2Dlg::OnBnClickedCancel)

	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCApplication2Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_GRAYING, &CMFCApplication2Dlg::OnBnClickedButtonGraying)
	ON_BN_CLICKED(IDC_BUTTON_GRAYLEVEL, &CMFCApplication2Dlg::OnBnClickedButtonGraylevel)
	ON_BN_CLICKED(IDC_BUTTON_GRAY_EQUALIZATION, &CMFCApplication2Dlg::OnBnClickedButtonGrayEqualization)
	ON_BN_CLICKED(IDC_BUTTON_GRAD, &CMFCApplication2Dlg::OnBnClickedButtonGrad)
	ON_BN_CLICKED(IDC_BUTTON_LAPLACE, &CMFCApplication2Dlg::OnBnClickedButtonLaplace)
	ON_BN_CLICKED(IDC_BUTTON_ROBERTS, &CMFCApplication2Dlg::OnBnClickedButtonRoberts)
	ON_BN_CLICKED(IDC_BUTTON_SOBEL, &CMFCApplication2Dlg::OnBnClickedButtonSobel)
	ON_BN_CLICKED(IDC_BUTTON_LAP, &CMFCApplication2Dlg::OnBnClickedButtonLap)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMFCApplication2Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_PREWITT, &CMFCApplication2Dlg::OnBnClickedButtonPrewitt)
	ON_BN_CLICKED(IDC_BUTTON_CANNY, &CMFCApplication2Dlg::OnBnClickedButtonCanny)
	ON_BN_CLICKED(IDC_BUTTON_AVE, &CMFCApplication2Dlg::OnBnClickedButtonAve)
	ON_BN_CLICKED(IDC_BUTTON_MID, &CMFCApplication2Dlg::OnBnClickedButtonMid)
	ON_BN_CLICKED(IDC_BUTTON_WIN, &CMFCApplication2Dlg::OnBnClickedButtonWin)
	ON_BN_CLICKED(IDC_BUTTON_AFFINE, &CMFCApplication2Dlg::OnBnClickedButtonAffine)
	ON_BN_CLICKED(IDC_BUTTON_QUAD, &CMFCApplication2Dlg::OnBnClickedButtonQuad)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication2Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication2Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication2Dlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

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

	/*CWnd* pWnd1 = GetDlgItem(IDC_PIC);//CWnd是MFC窗口类的基类,提供了微软基础类库中所有窗口类的基本功能。
	//GetDlgItem获得某个控件的句柄
	pWnd1->GetClientRect(&rect);//GetClientRect为获得控件相自身的坐标大小
	namedWindow("src1", WINDOW_AUTOSIZE);//设置窗口名
	HWND hWndl = (HWND)cvGetWindowHandle("src1");//hWnd 表示窗口句柄,获取窗口句柄
	HWND hParent1 = ::GetParent(hWndl);//GetParent函数一个指定子窗口的父窗口句柄
	::SetParent(hWndl, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);
	Mat srcImg = imread("C:/Users/Lenovo/Desktop/123.png");
	resize(srcImg, srcImg, Size(rect.Width(), rect.Height()));
	imshow("src1", srcImg);*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}




void CMFCApplication2Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("图片文件 (*.jpg)|*.jpg|图片文件 (*.png)|*.png|All Files (*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		//CString strFilePath;
		strFilePath = fileDlg.GetPathName();
		USES_CONVERSION;
		char * s = T2A(strFilePath);
		Mat srcImg = imread(s);
		imshow("src1", srcImg);
	}
}



void CMFCApplication2Dlg::OnBnClickedButtonGraying()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);
}


void CMFCApplication2Dlg::OnBnClickedButtonGraylevel()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	//绘制直方图
	Mat hist = Mat::zeros(600, 800, CV_8UC1);
	int a[256] = {0};
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++) {
			a[img.at<uchar>(i, j)]++;
		}
	}
	int max = 0;
	for (int i = 0; i < 256; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	double bin_width = ((double)hist.cols / 256);
	double bin_unit = ((double)hist.rows / max);
	for (int i = 0; i < 256; i++) {
		CvPoint p0 = cvPoint((i * bin_width), hist.rows);
		CvPoint p1 = cvPoint((i * bin_width), hist.rows - a[i] * bin_unit);
		line(hist, p0, p1,Scalar(255,255,255));
	}
	imshow("灰度直方图", hist);

	

}


void CMFCApplication2Dlg::OnBnClickedButtonGrayEqualization()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);
	int a[256] = { 0 };
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++) {
			a[img.at<uchar>(i, j)]++;
		}
	}
	Mat img1 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++) {
			//double n1 = srcImg.rows * srcImg.cols;
			long n2 = 0;
			for (int k = 0; img.at<uchar>(i, j) >= k; k++) {
				n2 += a[k];
			}
			img1.at<uchar>(i, j) = (int)(255 * n2 / (srcImg.rows * srcImg.cols));
		}
	}
	imshow("灰度直方图均衡化图像", img1);

	//Mat hist1 = Mat::zeros(600, 800, CV_8UC1);
	//int a1[256] = { 0 };
	//for (int i = 0; i < srcImg.rows; i++)
	//{
	//	for (int j = 0; j < srcImg.cols; j++) {
	//		a1[img1.at<uchar>(i, j)]++;
	//	}
	//}
	//int max = 0;
	//for (int i = 0; i < 256; i++) {
	//	if (a1[i] > max) {
	//		max = a1[i];
	//	}
	//}
	//double bin_width = ((double)hist1.cols / 256);
	//double bin_unit = ((double)hist1.rows / max);
	//for (int i = 0; i < 256; i++) {
	//	CvPoint p0 = cvPoint((i * bin_width), hist1.rows);
	//	CvPoint p1 = cvPoint((i * bin_width), hist1.rows - a1[i] * bin_unit);
	//	line(hist1, p0, p1, Scalar(255, 255, 255));
	//}
	//imshow("灰度直方图2", hist1);
}

void CMFCApplication2Dlg::OnBnClickedButtonGrad()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat grad = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i =0; i< srcImg.rows-1; i++){
		for (int j = 0; j < srcImg.cols-1; j++) {
			/*grad.at<uchar>(i, j) = abs(img.at<uchar>(i, j) - img.at<uchar>(i + 1, j))
				+ abs(img.at<uchar>(i, j) - img.at<uchar>(i, j + 1));
		/	if ((abs(img.at<uchar>(i, j) - img.at<uchar>(i + 1, j))
				+ abs(img.at<uchar>(i, j) - img.at<uchar>(i, j + 1))) > 20) {
				grad.at<uchar>(i, j) = 0;
			}
			else {
				grad.at<uchar>(i, j) = img.at<uchar>(i, j);
			}*/
			grad.at<uchar>(i, j) = saturate_cast <uchar>(img.at<uchar>(i, j)
				+ fabs(img.at<uchar>(i, j) - img.at<uchar>(i + 1, j))
				+ fabs(img.at<uchar>(i, j) - img.at<uchar>(i, j + 1)));
		}
	}
	imshow("梯度锐化图像", grad);
}


void CMFCApplication2Dlg::OnBnClickedButtonLaplace()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat lap =  Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			//int a =(5*img.at<uchar>(i, j) - img.at<uchar>(i + 1, j)
			//	- img.at<uchar>(i-1, j) - img.at<uchar>(i, j + 1) - img.at<uchar>(i, j - 1));
			//if(a>255){
			//	lap.at<uchar>(i, j) = 255;
			//}
			//else if (a < 0){
			//	a = 0;
			//}
			//lap.at<uchar>(i, j) = a;
			lap.at<uchar>(i, j) = saturate_cast <uchar>(5 * img.at<uchar>(i, j) - img.at<uchar>(i + 1, j)
				- img.at<uchar>(i-1, j) - img.at<uchar>(i, j + 1) - img.at<uchar>(i, j - 1));
		}
	}
	imshow("拉普拉斯增强图像", lap);
}


void CMFCApplication2Dlg::OnBnClickedButtonRoberts()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat grad = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i = 0; i < srcImg.rows - 1; i++) {
		for (int j = 0; j < srcImg.cols - 1; j++) {
			grad.at<uchar>(i, j) = saturate_cast <uchar>(fabs(img.at<uchar>(i, j) - img.at<uchar>(i + 1, j + 1))
				+ fabs(img.at<uchar>(i + 1, j) - img.at<uchar>(i, j + 1)));
		}
	}
	imshow("Roberts算子边缘检测", grad);
}


void CMFCApplication2Dlg::OnBnClickedButtonSobel()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat gradx = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	Mat grady = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			gradx.at<uchar>(i, j) = saturate_cast<uchar>(fabs(img.at<uchar>(i + 1, j - 1) 
				+ 2 * img.at<uchar>(i + 1, j)
				+ img.at<uchar>(i + 1, j + 1) 
				- img.at<uchar>(i - 1, j - 1) 
				- 2 * img.at<uchar>(i - 1, j) 
				- img.at<uchar>(i - 1, j + 1)));
			grady.at<uchar>(i, j) = saturate_cast<uchar>(fabs(img.at<uchar>(i - 1, j + 1)
				+ 2 * img.at<uchar>(i, j + 1)
				+ img.at<uchar>(i + 1, j + 1)
				- img.at<uchar>(i - 1, j - 1)
				- 2 * img.at<uchar>(i, j - 1)
				- img.at<uchar>(i + 1, j - 1)));
		}
	}
	imshow("Sobelx", gradx);
	imshow("Sobely", grady);
}


void CMFCApplication2Dlg::OnBnClickedButtonLap()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat lap = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			lap.at<uchar>(i, j) = saturate_cast <uchar>(img.at<uchar>(i + 1, j)
				+ img.at<uchar>(i - 1, j) 
				+ img.at<uchar>(i, j + 1) 
				+ img.at<uchar>(i, j - 1)
				- 4 * img.at<uchar>(i, j));
		}
	}
	imshow("拉普拉斯边缘检测图像", lap);
}


void CMFCApplication2Dlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	destroyAllWindows();
}


void CMFCApplication2Dlg::OnBnClickedButtonPrewitt()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat pre = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			pre.at<uchar>(i, j) = saturate_cast <uchar>(fmax(fabs(img.at<uchar>(i - 1, j - 1) 
				+ img.at<uchar>(i - 1, j)
				+ img.at<uchar>(i - 1, j + 1)
				- img.at<uchar>(i + 1, j - 1)
				- img.at<uchar>(i + 1, j)
				- img.at<uchar>(i + 1, j + 1)),
				fabs(img.at<uchar>(i - 1, j + 1)
					+ img.at<uchar>(i, j + 1)
					+ img.at<uchar>(i + 1, j + 1)
					- img.at<uchar>(i - 1, j - 1)
					- img.at<uchar>(i, j - 1)
					- img.at<uchar>(i + 1, j - 1))));
		}
	}
	imshow("Prewitt边缘检测", pre);
}


void CMFCApplication2Dlg::OnBnClickedButtonCanny()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	int t1_value = 50;
	int max_value = 255;

	Mat out = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	Canny(img, out, t1_value, t1_value * 2 );

	imshow("Canny边缘检测", out);
}


void CMFCApplication2Dlg::OnBnClickedButtonAve()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);

	Mat gaussiannoise = addGaussianNoise(srcImg);

	Mat saltnoise = addSaltNoise(srcImg, 10000);

	imshow("高斯噪声", gaussiannoise);
	imshow("椒盐噪声", saltnoise);

	Mat ave1 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				ave1.at<Vec3b>(i, j)[k] = ((
					gaussiannoise.at<Vec3b>(i - 1, j - 1)[k] +
					gaussiannoise.at<Vec3b>(i - 1, j)[k] +
					gaussiannoise.at<Vec3b>(i - 1, j + 1)[k] +
					gaussiannoise.at<Vec3b>(i, j - 1)[k] +
					gaussiannoise.at<Vec3b>(i, j)[k] +
					gaussiannoise.at<Vec3b>(i, j + 1)[k] +
					gaussiannoise.at<Vec3b>(i + 1, j - 1)[k] +
					gaussiannoise.at<Vec3b>(i + 1, j)[k] +
					gaussiannoise.at<Vec3b>(i + 1, j + 1)[k]) / 9);
			}

		}
	}
	imshow("高斯噪声均值滤波", ave1);

	Mat ave2 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				ave2.at<Vec3b>(i, j)[k] = ((
					saltnoise.at<Vec3b>(i - 1, j - 1)[k] +
					saltnoise.at<Vec3b>(i - 1, j)[k] +
					saltnoise.at<Vec3b>(i - 1, j + 1)[k] +
					saltnoise.at<Vec3b>(i, j - 1)[k] +
					saltnoise.at<Vec3b>(i, j)[k] +
					saltnoise.at<Vec3b>(i, j + 1)[k] +
					saltnoise.at<Vec3b>(i + 1, j - 1)[k] +
					saltnoise.at<Vec3b>(i + 1, j)[k] +
					saltnoise.at<Vec3b>(i + 1, j + 1)[k]) / 9);
			}

		}
	}
	imshow("椒盐噪声均值滤波", ave2);
}


void CMFCApplication2Dlg::OnBnClickedButtonMid()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);

	Mat gaussiannoise = addGaussianNoise(srcImg);

	Mat saltnoise = addSaltNoise(srcImg, 10000);

	imshow("高斯噪声", gaussiannoise);
	imshow("椒盐噪声", saltnoise);

	Mat ave1 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				int a[9];
				a[0] = gaussiannoise.at<Vec3b>(i - 1, j - 1)[k];
				a[1] = gaussiannoise.at<Vec3b>(i - 1, j)[k];
				a[2] = gaussiannoise.at<Vec3b>(i - 1, j + 1)[k];
				a[3] = gaussiannoise.at<Vec3b>(i, j - 1)[k];
				a[4] = gaussiannoise.at<Vec3b>(i, j)[k];
				a[5] = gaussiannoise.at<Vec3b>(i, j + 1)[k];
				a[6] = gaussiannoise.at<Vec3b>(i + 1, j - 1)[k];
				a[7] = gaussiannoise.at<Vec3b>(i + 1, j)[k];
				a[8] = gaussiannoise.at<Vec3b>(i + 1, j + 1)[k];
				sort(a, a+9);
					ave1.at<Vec3b>(i, j)[k] = a[4];
			}

		}
	}
	imshow("高斯噪声中值滤波", ave1);

	Mat ave2 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				int a[9];
				a[0] = saltnoise.at<Vec3b>(i - 1, j - 1)[k];
				a[1] = saltnoise.at<Vec3b>(i - 1, j)[k];
				a[2] = saltnoise.at<Vec3b>(i - 1, j + 1)[k];
				a[3] = saltnoise.at<Vec3b>(i, j - 1)[k];
				a[4] = saltnoise.at<Vec3b>(i, j)[k];
				a[5] = saltnoise.at<Vec3b>(i, j + 1)[k];
				a[6] = saltnoise.at<Vec3b>(i + 1, j - 1)[k];
				a[7] = saltnoise.at<Vec3b>(i + 1, j)[k];
				a[8] = saltnoise.at<Vec3b>(i + 1, j + 1)[k];
				sort(a, a + 9);
				ave2.at<Vec3b>(i, j)[k] = a[4];
			}

		}
	}
	imshow("椒盐噪声中值滤波", ave2);
}



void CMFCApplication2Dlg::OnBnClickedButtonWin()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);

	Mat gaussiannoise = addGaussianNoise(srcImg);

	Mat saltnoise = addSaltNoise(srcImg, 1000);

	imshow("高斯噪声", gaussiannoise);
	imshow("椒盐噪声", saltnoise);


	Mat ave1 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			int a[8][3] = { 0 };
			for (int k = 0; k < 3; k++) {
				a[0][k] = (saltnoise.at<Vec3b>(i - 1, j - 1)[k]
					+ saltnoise.at<Vec3b>(i, j - 1)[k]
					+ saltnoise.at<Vec3b>(i - 1, j)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]) / 4;
				a[1][k] = (saltnoise.at<Vec3b>(i - 1, j)[k]
					+ saltnoise.at<Vec3b>(i - 1, j + 1)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i, j + 1)[k]) / 4;
				a[2][k] = (saltnoise.at<Vec3b>(i, j - 1)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i + 1, j - 1)[k]
					+ saltnoise.at<Vec3b>(i + 1, j)[k]) / 4;
				a[3][k] = (saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i, j + 1)[k]
					+ saltnoise.at<Vec3b>(i + 1, j)[k]
					+ saltnoise.at<Vec3b>(i + 1, j + 1)[k]) / 4;
				a[4][k] = (saltnoise.at<Vec3b>(i - 1, j - 1)[k]
					+ saltnoise.at<Vec3b>(i - 1, j)[k]
					+ saltnoise.at<Vec3b>(i - 1, j + 1)[k]
					+ saltnoise.at<Vec3b>(i, j - 1)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i, j + 1)[k]) / 6;
				a[5][k] = (saltnoise.at<Vec3b>(i, j - 1)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i, j + 1)[k]
					+ saltnoise.at<Vec3b>(i + 1, j - 1)[k]
					+ saltnoise.at<Vec3b>(i + 1, j)[k]
					+ saltnoise.at<Vec3b>(i + 1, j + 1)[k]) / 6;
				a[6][k] = (saltnoise.at<Vec3b>(i - 1, j)[k]
					+ saltnoise.at<Vec3b>(i - 1, j + 1)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i, j + 1)[k]
					+ saltnoise.at<Vec3b>(i + 1, j)[k]
					+ saltnoise.at<Vec3b>(i + 1, j + 1)[k]) / 6;
				a[7][k] = (saltnoise.at<Vec3b>(i - 1, j - 1)[k]
					+ saltnoise.at<Vec3b>(i - 1, j)[k]
					+ saltnoise.at<Vec3b>(i, j - 1)[k]
					+ saltnoise.at<Vec3b>(i, j)[k]
					+ saltnoise.at<Vec3b>(i + 1, j - 1)[k]
					+ saltnoise.at<Vec3b>(i + 1, j)[k]) / 6;
				
			}
			int num[8] = {0};
			int flag1 = 0;
			int flag2 = 0;
			for (int l = 0; l < 8; l++) {
				for (int k = 0; k < 3; k++) {
					num[l] += pow((a[l][k] - saltnoise.at<Vec3b>(i, j)[k]), 2);
				}
				if (l == 0) {
					flag1 = num[l];
				}
				else if (flag1 > num[l]) {
					flag1 = num[l];
					flag2 = l;
				}
			}
			for (int k = 0; k < 3; k++) {
				ave1.at<Vec3b>(i, j)[k] = a[flag2][k];
			}
		}
	}
	imshow("高斯噪声边窗滤波", ave1);


	Mat ave2 = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);
	for (int i = 1; i < srcImg.rows - 1; i++) {
		for (int j = 1; j < srcImg.cols - 1; j++) {
			int a[8][3] = { 0 };
			for (int k = 0; k < 3; k++) {
				a[0][k] = (gaussiannoise.at<Vec3b>(i - 1, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i - 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]) / 4;
				a[1][k] = (gaussiannoise.at<Vec3b>(i - 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i - 1, j + 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j + 1)[k]) / 4;
				a[2][k] = (gaussiannoise.at<Vec3b>(i, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j)[k]) / 4;
				a[3][k] = (gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j + 1)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j + 1)[k]) / 4;
				a[4][k] = (gaussiannoise.at<Vec3b>(i - 1, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i - 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i - 1, j + 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j + 1)[k]) / 6;
				a[5][k] = (gaussiannoise.at<Vec3b>(i, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j + 1)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j + 1)[k]) / 6;
				a[6][k] = (gaussiannoise.at<Vec3b>(i - 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i - 1, j + 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j + 1)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j + 1)[k]) / 6;
				a[7][k] = (gaussiannoise.at<Vec3b>(i - 1, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i - 1, j)[k]
					+ gaussiannoise.at<Vec3b>(i, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i, j)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j - 1)[k]
					+ gaussiannoise.at<Vec3b>(i + 1, j)[k]) / 6;

			}
			int num[8] = { 0 };
			int flag1 = 0;
			int flag2 = 0;
			for (int l = 0; l < 8; l++) {
				for (int k = 0; k < 3; k++) {
					num[l] += pow((a[l][k] - gaussiannoise.at<Vec3b>(i, j)[k]), 2);
				}
				if (l == 0) {
					flag1 = num[l];
				}
				else if (flag1 > num[l]) {
					flag1 = num[l];
					flag2 = l;
				}
			}
			for (int k = 0; k < 3; k++) {
				ave2.at<Vec3b>(i, j)[k] = a[flag2][k];
			}
		}
	}
	imshow("椒盐噪声边窗滤波", ave2);

}


void CMFCApplication2Dlg::OnBnClickedButtonAffine()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, srcImg.type());
	//imshow("src1", srcImg);
	Point2f srcTri[3], dstTri[3];
	Mat warp_mat(2, 3, CV_32FC1);
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(srcImg.cols - 1, 0);
	srcTri[2] = Point2f(0, srcImg.rows - 1);

	dstTri[0] = Point2f(srcImg.cols * 0, srcImg.rows * 0.33);
	dstTri[1] = Point2f(srcImg.cols * 0.85, srcImg.rows * 0.25);
	dstTri[2] = Point2f(srcImg.cols * 0.15, srcImg.rows * 0.7);

	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(srcImg, img, warp_mat,srcImg.size());
	imshow("仿射变换", img);

}


void CMFCApplication2Dlg::OnBnClickedButtonQuad()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, srcImg.type());
	//imshow("src1", srcImg);
	Point2f srcQuad[4], dstQuad[4];
	Mat warp_matrix(3, 3, CV_32FC1);
	srcQuad[0] = Point2f(0, 0);
	srcQuad[1] = Point2f(srcImg.cols - 1, 0);
	srcQuad[2] = Point2f(0, srcImg.rows - 1);
	srcQuad[3] = Point2f(srcImg.cols - 1, srcImg.rows - 1);

	dstQuad[0] = Point2f(srcImg.cols * 0.05, srcImg.rows * 0.33);
	dstQuad[1] = Point2f(srcImg.cols * 0.9, srcImg.rows * 0.35);
	dstQuad[2] = Point2f(srcImg.cols * 0.2, srcImg.rows * 0.7);
	dstQuad[3] = Point2f(srcImg.cols * 0.8, srcImg.rows * 0.9);

	warp_matrix = getPerspectiveTransform(srcQuad, dstQuad);
	warpPerspective(srcImg, img, warp_matrix, srcImg.size());
	imshow("透视变换", img);
}


void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ifstream fin("G://BaiduNetdiskDownload//camer_cab//imageDatalist_right.txt"); /* 标定所用图像文件的路径 */
	ofstream fout("G://BaiduNetdiskDownload//camer_cab//caliberation_result_right.txt");  /* 保存标定结果的文件 */
	//读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化	
	_cprintf("start to find corners………………\n");
	int image_count = 0;  /* 图像数量 */
	Size image_size;  /* 图像的尺寸 */
	Size board_size = Size(9, 6);    /* 标定板上每行、列的角点数 */
	vector<Point2f> image_points_buf;  /* 缓存每幅图像上检测到的角点 */
	vector<vector<Point2f>> image_points_seq; /* 保存检测到的所有角点 */
	string filename;
	int count = -1;//用于存储角点个数。
	while (getline(fin, filename))
	{
		image_count++;
		// 用于观察检验输出
		_cprintf("image_count = %d\n", image_count);

		Mat imageInput = imread(filename);
		if (image_count == 1)  //读入第一张图片时获取图像宽高信息
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			_cprintf("image_size.width = %d\n", image_size.width);
			_cprintf("image_size.height = %d\n", image_size.height);
		}

		/* 提取角点 */
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf))
		{
			_cprintf("can not find chessboard corners!\n"); //找不到角点
			waitKey(0);
			exit(1);
		}
		else
		{
			Mat view_gray;
			cvtColor(imageInput, view_gray, CV_RGB2GRAY);
			/* 亚像素精确化 */
			find4QuadCornerSubpix(view_gray, image_points_buf, Size(5, 5)); //对粗提取的角点进行精确化
																			//cornerSubPix(view_gray,image_points_buf,Size(5,5),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
			image_points_seq.push_back(image_points_buf);  //保存亚像素角点
														   /* 在图像上显示角点位置 */
			drawChessboardCorners(view_gray, board_size, image_points_buf, false); //用于在图片中标记角点
			imshow("Camera Calibration", view_gray);//显示图片
			waitKey(50);//暂停0.5S		
		}
	}
	int total = image_points_seq.size();
	_cprintf("total = %d\n", total);
	int CornerNum = board_size.width * board_size.height;  //每张图片上总的角点数
	for (int ii = 0; ii < total; ii++)
	{
		if (0 == ii % CornerNum)// 24 是每幅图片的角点个数。此判断语句是为了输出 图片号，便于控制台观看 
		{
			int i = -1;
			i = ii / CornerNum;
			int j = i + 1;
			_cprintf("--> the %d image's data --> :", j);
		}
		if (0 == ii % 3)	// 此判断语句，格式化输出，便于控制台查看
		{
			_cprintf("\n");
		}
		else
		{
			cout.width(10);
		}
		//输出所有的角点
		_cprintf(" -->%f", image_points_seq[ii][0].x);
		_cprintf(" -->%f", image_points_seq[ii][0].y);
	}
	_cprintf("find corner successfully！\n");

	//以下是摄像机标定
	_cprintf("start calibration………………");
	/*棋盘三维信息*/
	Size square_size = Size(10, 10);  /* 实际测量得到的标定板上每个棋盘格的大小 */
	vector<vector<Point3f>> object_points; /* 保存标定板上角点的三维坐标 */
										   /*内外参数*/
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 摄像机内参数矩阵 */
	vector<int> point_counts;  // 每幅图像中角点的数量
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
	vector<Mat> tvecsMat;  /* 每幅图像的旋转向量 */
	vector<Mat> rvecsMat; /* 每幅图像的平移向量 */
						  /* 初始化标定板上角点的三维坐标 */
	int i, j, t;
	for (t = 0; t < image_count; t++)
	{
		vector<Point3f> tempPointSet;
		for (i = 0; i < board_size.height; i++)
		{
			for (j = 0; j < board_size.width; j++)
			{
				Point3f realPoint;
				/* 假设标定板放在世界坐标系中z=0的平面上 */
				realPoint.x = i * square_size.width;
				realPoint.y = j * square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}
	/* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
	for (i = 0; i < image_count; i++)
	{
		point_counts.push_back(board_size.width * board_size.height);
	}
	/* 开始标定 */
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);
	_cprintf("calibrate successfully！\n");
	//对标定结果进行评价
	_cprintf("start evaluate the calibration results………………\n");
	double total_err = 0.0; /* 所有图像的平均误差的总和 */
	double err = 0.0; /* 每幅图像的平均误差 */
	vector<Point2f> image_points2; /* 保存重新计算得到的投影点 */
	_cprintf("\t each image's calibration error：\n");
	_cprintf("each image's calibration error：\n");
	for (i = 0; i < image_count; i++)
	{
		vector<Point3f> tempPointSet = object_points[i];
		/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);
		/* 计算新的投影点和旧的投影点之间的误差*/
		vector<Point2f> tempImagePoint = image_points_seq[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		total_err += err /= point_counts[i];
		_cprintf("the %d th image's average err: %f pixels\n", i + 1, err);
		fout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
	}
	_cprintf(" the total average err：%f \n", total_err / image_count);
	fout << "总体平均误差：" << total_err / image_count << "像素" << endl << endl;
	_cprintf("evaluate successfully！\n");
	//保存定标结果  	
	_cprintf("start save calibration results………………\n");
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
	fout << "相机内参数矩阵：" << endl;
	fout << cameraMatrix << endl << endl;
	fout << "畸变系数：\n";
	fout << distCoeffs << endl << endl << endl;
	for (int i = 0; i < image_count; i++)
	{
		fout << "第" << i + 1 << "幅图像的旋转向量：" << endl;
		fout << tvecsMat[i] << endl;
		/* 将旋转向量转换为相对应的旋转矩阵 */
		Rodrigues(tvecsMat[i], rotation_matrix);
		fout << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
		fout << rotation_matrix << endl;
		fout << "第" << i + 1 << "幅图像的平移向量：" << endl;
		fout << rvecsMat[i] << endl << endl;
	}
	_cprintf("save successfully\n");
	fout << endl;
	/************************************************************************
	显示定标结果
	*************************************************************************/
	Mat mapx = Mat(image_size, CV_32FC1);
	Mat mapy = Mat(image_size, CV_32FC1);
	Mat R = Mat::eye(3, 3, CV_32F);
	_cprintf("save rectified image\n");
	string imageFileName;
	std::stringstream StrStm;
	for (int i = 0; i != image_count; i++)
	{
		_cprintf("Frame # %d ...\n", i + 1);
		initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, image_size, CV_32FC1, mapx, mapy);
		StrStm.clear();
		imageFileName.clear();
		string filePath = "G://BaiduNetdiskDownload//camer_cab//chess";
		StrStm << i + 1;
		StrStm >> imageFileName;
		filePath += imageFileName;
		filePath += ".jpg";
		Mat imageSource = imread("G://BaiduNetdiskDownload//camer_cab//left01.jpg");
		Mat newimage = imageSource.clone();
		//另一种不需要转换矩阵的方式
		//undistort(imageSource,newimage,cameraMatrix,distCoeffs);
		remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
		StrStm.clear();
		filePath.clear();
		filePath = "G://BaiduNetdiskDownload//camer_cab//chess";
		StrStm << i + 1;
		StrStm >> imageFileName;
		filePath += imageFileName;
		filePath += "_d.jpg";
		imwrite(filePath, newimage);
	}
	_cprintf(" save successfully\n");
	waitKey(0);
}


void CMFCApplication2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//摄像头的分辨率
	const int imageWidth = 640;
	const int imageHeight = 480;
	//横向的角点数目
	const int boardWidth = 9;
	//纵向的角点数目
	const int boardHeight = 6;
	//总的角点数目
	const int boardCorner = boardWidth * boardHeight;
	//相机标定时需要采用的图像帧数
	const int frameNumber = 14;
	//标定板黑白格子的大小 单位是mm
	const int squareSize = 10;
	//标定板的总内角点
	const Size boardSize = Size(boardWidth, boardHeight);
	Size imageSize = Size(imageWidth, imageHeight);


	//R旋转矢量 T平移矢量 E本征矩阵 F基础矩阵
	vector<Mat> rvecs; //R
	vector<Mat> tvecs; //T
					   //左边摄像机所有照片角点的坐标集合
	vector<vector<Point2f>> imagePointL;
	//右边摄像机所有照片角点的坐标集合
	vector<vector<Point2f>> imagePointR;
	//各图像的角点的实际的物理坐标集合
	vector<vector<Point3f>> objRealPoint;
	//左边摄像机某一照片角点坐标集合
	vector<Point2f> cornerL;
	//右边摄像机某一照片角点坐标集合
	vector<Point2f> cornerR;

	Mat rgbImageL, grayImageL;
	Mat rgbImageR, grayImageR;
	Mat intrinsic;
	Mat distortion_coeff;
	//校正旋转矩阵R，投影矩阵P，重投影矩阵Q
	//映射表
	Mat mapLx, mapLy, mapRx, mapRy;
	Rect validROIL, validROIR;
	//图像校正之后，会对图像进行裁剪，其中，validROI裁剪之后的区域

	Mat img;
	int goodFrameCount = 1;
	while (goodFrameCount <= frameNumber)
	{
		char filename[100];
		//读取左边的图像
		sprintf_s(filename, "G://BaiduNetdiskDownload//camer_cab//left%02d.jpg", goodFrameCount);
		rgbImageL = imread(filename, 1);
		imshow("chessboardL", rgbImageL);
		cvtColor(rgbImageL, grayImageL, CV_BGR2GRAY);
		//读取右边的图像
		sprintf_s(filename, "G://BaiduNetdiskDownload//camer_cab//right%02d.jpg", goodFrameCount);
		rgbImageR = imread(filename, 1);
		cvtColor(rgbImageR, grayImageR, CV_BGR2GRAY);

		bool isFindL, isFindR;
		isFindL = findChessboardCorners(rgbImageL, boardSize, cornerL);
		isFindR = findChessboardCorners(rgbImageR, boardSize, cornerR);
		if (isFindL == true && isFindR == true)
		{
			cornerSubPix(grayImageL, cornerL, Size(5, 5), Size(-1, 1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 0.1));
			drawChessboardCorners(rgbImageL, boardSize, cornerL, isFindL);
			imshow("chessboardL", rgbImageL);
			imagePointL.push_back(cornerL);

			cornerSubPix(grayImageR, cornerR, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 0.1));
			drawChessboardCorners(rgbImageR, boardSize, cornerR, isFindR);
			imshow("chessboardR", rgbImageR);
			imagePointR.push_back(cornerR);

			_cprintf("the image %d is good\n", goodFrameCount);
			goodFrameCount++;
		}
		else
		{
			_cprintf("the image is bad please try again\n");
		}

		if (waitKey(10) == 'q')
		{
			break;
		}
	}

	//计算实际的校正点的三维坐标，根据实际标定格子的大小来设置

	calRealPoint(objRealPoint, boardWidth, boardHeight, frameNumber, squareSize);
	_cprintf("cal real successful\n");

	//标定摄像头
	double rms = stereoCalibrate(objRealPoint, imagePointL, imagePointR,
		cameraMatrixL, distCoeffL,
		cameraMatrixR, distCoeffR,
		Size(imageWidth, imageHeight), R, T, E, F, CALIB_USE_INTRINSIC_GUESS,
		TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 100, 1e-5));

	_cprintf("Stereo Calibration done with RMS error = %f\n", rms);

	stereoRectify(cameraMatrixL, distCoeffL, cameraMatrixR, distCoeffR, imageSize, R, T, Rl,
		Rr, Pl, Pr, Q, CALIB_ZERO_DISPARITY, -1, imageSize, &validROIL, &validROIR);

	//摄像机校正映射
	initUndistortRectifyMap(cameraMatrixL, distCoeffL, Rl, Pl, imageSize, CV_32FC1, mapLx, mapLy);
	initUndistortRectifyMap(cameraMatrixR, distCoeffR, Rr, Pr, imageSize, CV_32FC1, mapRx, mapRy);

	Mat rectifyImageL, rectifyImageR;
	cvtColor(grayImageL, rectifyImageL, CV_GRAY2BGR);
	cvtColor(grayImageR, rectifyImageR, CV_GRAY2BGR);

	imshow("RecitifyL Before", rectifyImageL);
	imshow("RecitifyR Before", rectifyImageR);

	//经过remap之后，左右相机的图像已经共面并且行对准了
	Mat rectifyImageL2, rectifyImageR2;
	remap(rectifyImageL, rectifyImageL2, mapLx, mapLy, INTER_LINEAR);
	remap(rectifyImageR, rectifyImageR2, mapRx, mapRy, INTER_LINEAR);


	imshow("rectifyImageL", rectifyImageL2);
	imshow("rectifyImageR", rectifyImageR2);

	outputCameraParam();
	//显示校正结果
	Mat canvas;
	double sf;
	int w, h;
	sf = 600. / MAX(imageSize.width, imageSize.height);
	w = cvRound(imageSize.width * sf);
	h = cvRound(imageSize.height * sf);
	canvas.create(h, w * 2, CV_8UC3);

	//左图像画到画布上
	Mat canvasPart = canvas(Rect(0, 0, w, h));
	resize(rectifyImageL2, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
	Rect vroiL(cvRound(validROIL.x * sf), cvRound(validROIL.y * sf),
		cvRound(validROIL.width * sf), cvRound(validROIL.height * sf));
	rectangle(canvasPart, vroiL, Scalar(0, 0, 255), 3, 8);

	_cprintf("Painted ImageL\n");

	//右图像画到画布上
	canvasPart = canvas(Rect(w, 0, w, h));
	resize(rectifyImageR2, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);
	Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y * sf),
		cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
	rectangle(canvasPart, vroiR, Scalar(0, 255, 0), 3, 8);

	_cprintf("Painted ImageR\n");

	//画上对应的线条
	for (int i = 0; i < canvas.rows; i += 16)
		line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);

	imshow("rectified", canvas);
	_cprintf("wait key\n");
	waitKey(0);
}


int getDisparityImage(cv::Mat& disparity, cv::Mat& disparityImage, bool isColor)
{
	cv::Mat disp8u;
	disp8u = disparity;
	// 转换为伪彩色图像 或 灰度图像
	if (isColor)
	{
		if (disparityImage.empty() || disparityImage.type() != CV_8UC3 || disparityImage.size() != disparity.size())
		{
			disparityImage = cv::Mat::zeros(disparity.rows, disparity.cols, CV_8UC3);
		}
		for (int y = 0; y < disparity.rows; y++)
		{
			for (int x = 0; x < disparity.cols; x++)
			{
				uchar val = disp8u.at<uchar>(y, x);
				uchar r, g, b;

				if (val == 0)
					r = g = b = 0;
				else
				{
					r = 255 - val;
					g = val < 128 ? val * 2 : (uchar)((255 - val) * 2);
					b = val;
				}
				disparityImage.at<cv::Vec3b>(y, x) = cv::Vec3b(b, g, r);
			}
		}
	}
	else
	{
		disp8u.copyTo(disparityImage);
	}
	return 1;
}
const int imageWidth = 640;                             //摄像头的分辨率  
const int imageHeight = 480;
Size imageSize = Size(imageWidth, imageHeight);

Mat rgbImageL, grayImageL;
Mat rgbImageR, grayImageR;
Mat rectifyImageL, rectifyImageR;

Rect validROIL;//图像校正之后，会对图像进行裁剪，这里的validROI就是指裁剪之后的区域  
Rect validROIR;

Mat xyz;              //三维坐标
int blockSize = 0, uniquenessRatio = 0, numDisparities = 0;
Ptr<StereoBM> bm = StereoBM::create(16, 9);

Mat T_new = (Mat_<double>(3, 1) << -3.3269653179960471e+01, 3.7375231026230421e-01, -1.2058042444883227e-02);//T平移向量
//Mat rec = (Mat_<double>(3, 1) << -0.00306, -0.03207, 0.00206);//rec旋转向量
Mat R_new = (Mat_<double>(3, 3) << 9.9998505024526163e-01, 3.5253250461816949e-03,
	4.1798767087380161e-03, -3.4957471578341281e-03,
	9.9996894942320580e-01, -7.0625732745616225e-03,
	-4.2046447876106169e-03, 7.0478558986986593e-03,
	9.9996632377767658e-01);//R 旋转矩阵

/*****立体匹配*****/
void stereo_match(int, void*)
{
	bm->setBlockSize(2 * blockSize + 5);     //SAD窗口大小，5~21之间为宜
	bm->setROI1(validROIL);
	bm->setROI2(validROIR);
	bm->setPreFilterCap(31);
	bm->setMinDisparity(0);  //最小视差，默认值为0, 可以是负值，int型
	bm->setNumDisparities(numDisparities * 16 + 16);//视差窗口，即最大视差值与最小视差值之差,窗口大小必须是16的整数倍，int型
	bm->setTextureThreshold(10);
	bm->setUniquenessRatio(uniquenessRatio);//uniquenessRatio主要可以防止误匹配
	bm->setSpeckleWindowSize(100);
	bm->setSpeckleRange(32);
	bm->setDisp12MaxDiff(-1);
	Mat disp, disp8, disparityImage;
	bm->compute(rectifyImageL, rectifyImageR, disp);//输入图像必须为灰度图
	disp.convertTo(disp8, CV_8U, 255 / ((numDisparities * 16 + 16) * 16.));//计算出的视差是CV_16S格式
	reprojectImageTo3D(disp, xyz, Q, true); //在实际求距离时，ReprojectTo3D出来的X / W, Y / W, Z / W都要乘以16(也就是W除以16)，才能得到正确的三维坐标信息。
	xyz = xyz * 16;
	getDisparityImage(disp8, disparityImage, true);
	imshow("disparity", disparityImage);
}

//立体匹配


void CMFCApplication2Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
		//立体校正
	stereoRectify(cameraMatrixL, distCoeffL, cameraMatrixR, distCoeffR, imageSize, R_new, T_new, Rl, Rr, Pl, Pr, Q, CALIB_ZERO_DISPARITY,
		0, imageSize, &validROIL, &validROIR);
	initUndistortRectifyMap(cameraMatrixL, distCoeffL, Rl, Pr, imageSize, CV_32FC1, mapLx, mapLy);
	initUndistortRectifyMap(cameraMatrixR, distCoeffR, Rr, Pr, imageSize, CV_32FC1, mapRx, mapRy);

	rgbImageL = imread("G://BaiduNetdiskDownload//camer_cab//left01.jpg", CV_LOAD_IMAGE_COLOR);
	cvtColor(rgbImageL, grayImageL, CV_BGR2GRAY);
	rgbImageR = imread("G://BaiduNetdiskDownload//camer_cab//right01.jpg", CV_LOAD_IMAGE_COLOR);
	cvtColor(rgbImageR, grayImageR, CV_BGR2GRAY);

	imshow("ImageL Before Rectify", grayImageL);
	imshow("ImageR Before Rectify", grayImageR);

	/*
	经过remap之后，左右相机的图像已经共面并且行对准了
	*/
	remap(grayImageL, rectifyImageL, mapLx, mapLy, INTER_LINEAR);
	remap(grayImageR, rectifyImageR, mapRx, mapRy, INTER_LINEAR);

	/*
	把校正结果显示出来
	*/
	Mat rgbRectifyImageL, rgbRectifyImageR;
	cvtColor(rectifyImageL, rgbRectifyImageL, CV_GRAY2BGR);  //伪彩色图
	cvtColor(rectifyImageR, rgbRectifyImageR, CV_GRAY2BGR);
	//单独显示
	//rectangle(rgbRectifyImageL, validROIL, Scalar(0, 0, 255), 3, 8);
	//rectangle(rgbRectifyImageR, validROIR, Scalar(0, 0, 255), 3, 8);
	imshow("ImageL After Rectify", rgbRectifyImageL);
	imshow("ImageR After Rectify", rgbRectifyImageR);

	//显示在同一张图上
	Mat canvas;
	double sf;
	int w, h;
	sf = 600. / MAX(imageSize.width, imageSize.height);
	w = cvRound(imageSize.width * sf);
	h = cvRound(imageSize.height * sf);
	canvas.create(h, w * 2, CV_8UC3);   //注意通道

										//左图像画到画布上
	Mat canvasPart = canvas(Rect(w * 0, 0, w, h));                                //得到画布的一部分  
	resize(rgbRectifyImageL, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);     //把图像缩放到跟canvasPart一样大小  
	Rect vroiL(cvRound(validROIL.x * sf), cvRound(validROIL.y * sf),                //获得被截取的区域    
		cvRound(validROIL.width * sf), cvRound(validROIL.height * sf));
	//rectangle(canvasPart, vroiL, Scalar(0, 0, 255), 3, 8);                      //画上一个矩形  
	cout << "Painted ImageL" << endl;

	//右图像画到画布上
	canvasPart = canvas(Rect(w, 0, w, h));                                      //获得画布的另一部分  
	resize(rgbRectifyImageR, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);
	Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y * sf),
		cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
	//rectangle(canvasPart, vroiR, Scalar(0, 0, 255), 3, 8);
	cout << "Painted ImageR" << endl;

	//画上对应的线条
	for (int i = 0; i < canvas.rows; i += 16)
		line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);
	imshow("rectified", canvas);

	/*
	立体匹配
	*/
	namedWindow("disparity", CV_WINDOW_AUTOSIZE);
	// 创建SAD窗口 Trackbar
	createTrackbar("BlockSize:\n", "disparity", &blockSize, 8, stereo_match);
	// 创建视差唯一性百分比窗口 Trackbar
	createTrackbar("UniquenessRatio:\n", "disparity", &uniquenessRatio, 50, stereo_match);
	// 创建视差窗口 Trackbar
	createTrackbar("NumDisparities:\n", "disparity", &numDisparities, 16, stereo_match);
	stereo_match(0, 0);

	waitKey(0);

}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码USES_CONVERSION;
	USES_CONVERSION; 
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat img1 = Mat::zeros(srcImg.rows, srcImg.cols, img.type());
	threshold(img, img1, 100, 255, CV_THRESH_BINARY);
	imshow("固定阈值分割", img1);

}


void CMFCApplication2Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);

	Mat img1 = Mat::zeros(srcImg.rows, srcImg.cols, img.type());
	threshold(img, img1, 100, 255, CV_THRESH_OTSU);
	imshow("OTSU自适应阈值分割", img1);
}


void CMFCApplication2Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	char* s = T2A(strFilePath);
	Mat srcImg = imread(s);
	Mat img = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
	//imshow("src1", srcImg);
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			img.at<uchar>(i, j) = 0.3 * srcImg.at<Vec3b>(i, j)[0]
				+ 0.59 * srcImg.at<Vec3b>(i, j)[1]
				+ 0.11 * srcImg.at<Vec3b>(i, j)[2];
		}
	}
	imshow("灰度图像", img);
	Mat grad = Mat::zeros(srcImg.rows, srcImg.cols, img.type());
	double sumu = 0;
	double sumGrad = 0;
	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			int gradx = img.at<uchar>(i + 1, j) - img.at<uchar>(i - 1, j);
			int grady = img.at<uchar>(i, j + 1) - img.at<uchar>(i, j - 1);
			grad.at<uchar>(i, j) = fmax(fabs(gradx), fabs(grady));
			sumGrad += grad.at<uchar>(i, j);
			
			sumu += grad.at<uchar>(i, j) * img.at<uchar>(i, j);
		}
	}
	double kt = sumu / sumGrad;
	Mat img1 = Mat::zeros(img.rows, img.cols, img.type());
	threshold(img, img1, kt, 255, CV_THRESH_BINARY);
	imshow("kittle自适应阈值分割", img1);
}


void CMFCApplication2Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat pFrame1, pFrame2, pFrame3;  //当前帧

	VideoCapture pCapture;

	int nFrmNum;

	Mat pframe;
	pCapture = VideoCapture("G://BaiduNetdiskDownload//cat.avi");
	pCapture >> pframe;

	Mat pFrImg1, pFrImg2, pFrImg3;   //当前帧

	pFrImg1.create(pframe.size(), CV_8UC1);
	pFrImg2.create(pframe.size(), CV_8UC1);
	pFrImg3.create(pframe.size(), CV_8UC1);

	Mat pFrMat1, pFrMat2, pFrMat3;

	nFrmNum = 0;
	while (1)
	{
		nFrmNum++;

		pCapture >> pFrame1;
		if (pFrame1.data == NULL)
			return;
		pCapture >> pFrame2;
		pCapture >> pFrame3;

		cvtColor(pFrame1, pFrImg1, CV_BGR2GRAY);
		cvtColor(pFrame2, pFrImg2, CV_BGR2GRAY);
		cvtColor(pFrame3, pFrImg3, CV_BGR2GRAY);

		absdiff(pFrImg1, pFrImg2, pFrMat1);//当前帧跟前面帧相减
		absdiff(pFrImg2, pFrImg3, pFrMat2);//当前帧与后面帧相减
													  //二值化前景图
		threshold(pFrMat1, pFrMat1, 10, 255.0, CV_THRESH_BINARY);
		threshold(pFrMat2, pFrMat2, 10, 255.0, CV_THRESH_BINARY);

		Mat element = getStructuringElement(0, cv::Size(3, 3));
		Mat element1 = getStructuringElement(0, cv::Size(5, 5));
		//膨胀化前景图
		erode(pFrMat1, pFrMat1, element);
		erode(pFrMat2, pFrMat2, element);

		dilate(pFrMat1, pFrMat1, element1);
		dilate(pFrMat2, pFrMat2, element1);

		dilate(pFrMat1, pFrMat1, element1);
		dilate(pFrMat2, pFrMat2, element1);

		//imshow("diff1", pFrMat1);
		imshow("diff2", pFrMat2);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		//当前帧与前面帧相减后提取的轮廓线
		findContours(pFrMat2, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
		double Maxarea = 0;
		int numi = 0;
		for (size_t i = 0; i < contours.size(); ++i)
		{
			double area = contourArea(contours[i], false);
			if (area > Maxarea)
			{
				Maxarea = area;
				numi = i;
			}
		}
		_cprintf("Maxarea=%f\n", Maxarea);
		if (numi != 0)
			drawContours(pFrame2, contours, numi, Scalar(0, 0, 255), 2);

		Mat resultImage = Mat::zeros(pFrMat2.size(), CV_8U);

		imshow("src", pFrame2);
		waitKey(10);
	}
}


void CMFCApplication2Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	//cvNamedWindow("origin", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("background", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("foreground", CV_WINDOW_AUTOSIZE);
	Mat greyimg;
	Mat foreground, background;

	VideoCapture pCapture;

	int nFrmNum;

	Mat pframe;
	pCapture = VideoCapture("G://BaiduNetdiskDownload//test.avi");
	pCapture >> pframe;

	double alpha = 0.2;    //背景建模alpha值
	double std_init = 20;    //初始标准差
	double var_init = std_init * std_init;    //初始方差    
	double lamda = 2.5 * 1.2;    //背景更新参数



	
	
	Mat frame_u = Mat::zeros(pframe.rows, pframe.cols, CV_8UC3);   //期望图片
	for (int i = 0; i < pframe.rows; i++) {
		for (int j = 0; j < pframe.cols; j++)
		{
			frame_u.at<Vec3b>(i, j)[0] = pframe.at<Vec3b>(i, j)[0];
			frame_u.at<Vec3b>(i, j)[1] = pframe.at<Vec3b>(i, j)[1];
			frame_u.at<Vec3b>(i, j)[2] = pframe.at<Vec3b>(i, j)[2];
		}
	}
		
		
	Mat frame_d = Mat::zeros(pframe.rows, pframe.cols, CV_8UC3);   //前景图片
	Mat frame_var = Mat(pframe.rows, pframe.cols, CV_8UC3, var_init); //方差图像
	Mat frame_std = Mat(pframe.rows, pframe.cols, CV_8UC3, std_init); //标准差
	while(1){
		pCapture >> pframe;
		if (pframe.data == NULL)
			break;
		//imshow("test", pframe);
		for (int i = 0; i < pframe.rows; i++) {
			for (int j = 0; j < pframe.cols; j++) {
				if (abs(pframe.at<Vec3b>(i, j)[0] - frame_u.at<Vec3b>(i, j)[0]) < lamda * std_init &&
					abs(pframe.at<Vec3b>(i, j)[1] - frame_u.at<Vec3b>(i, j)[1]) < lamda * std_init &&
					abs(pframe.at<Vec3b>(i, j)[2] - frame_u.at<Vec3b>(i, j)[2]) < lamda * std_init) {
					//更新期望
					frame_u.at<Vec3b>(i, j)[0] = alpha * frame_u.at<Vec3b>(i, j)[0] + (1 - alpha) * pframe.at<Vec3b>(i, j)[0];
					frame_u.at<Vec3b>(i, j)[1] = alpha * frame_u.at<Vec3b>(i, j)[1] + (1 - alpha) * pframe.at<Vec3b>(i, j)[1];
					frame_u.at<Vec3b>(i, j)[2] = alpha * frame_u.at<Vec3b>(i, j)[2] + (1 - alpha) * pframe.at<Vec3b>(i, j)[2];
					//更新方差
					frame_var.at<Vec3b>(i, j)[0] = alpha * frame_var.at<Vec3b>(i, j)[0]
					+ (1 - alpha) * (pframe.at<Vec3b>(i, j)[0] - frame_u.at<Vec3b>(i, j)[0])
					* (pframe.at<Vec3b>(i, j)[0] - frame_u.at<Vec3b>(i, j)[0]);
					frame_var.at<Vec3b>(i, j)[1] = alpha * frame_var.at<Vec3b>(i, j)[1]
					+ (1 - alpha) * (pframe.at<Vec3b>(i, j)[1] - frame_u.at<Vec3b>(i, j)[1])
					* (pframe.at<Vec3b>(i, j)[1] - frame_u.at<Vec3b>(i, j)[1]);
					frame_var.at<Vec3b>(i, j)[2] = alpha * frame_var.at<Vec3b>(i, j)[2]
					+ (1 - alpha) * (pframe.at<Vec3b>(i, j)[2] - frame_u.at<Vec3b>(i, j)[2])
					* (pframe.at<Vec3b>(i, j)[2] - frame_u.at<Vec3b>(i, j)[2]);
					//更新标准差
					frame_std.at<Vec3b>(i, j)[0] = sqrt(frame_var.at<Vec3b>(i, j)[0]);
					frame_std.at<Vec3b>(i, j)[1] = sqrt(frame_var.at<Vec3b>(i, j)[1]);
					frame_std.at<Vec3b>(i, j)[2] = sqrt(frame_var.at<Vec3b>(i, j)[2]);
				}
				else {
					frame_d.at<Vec3b>(i, j)[0] = pframe.at<Vec3b>(i, j)[0] - frame_u.at<Vec3b>(i, j)[0];
					frame_d.at<Vec3b>(i, j)[1] = pframe.at<Vec3b>(i, j)[1] - frame_u.at<Vec3b>(i, j)[1];
					frame_d.at<Vec3b>(i, j)[2] = pframe.at<Vec3b>(i, j)[2] - frame_u.at<Vec3b>(i, j)[2];
				}
			}
		}
		imshow("原始图像", pframe);
		imshow("background", frame_u);
		imshow("foreground", frame_d);
		waitKey(10);
	}



	
}



void CMFCApplication2Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat greyimg;
	Mat foreground, foreground2;
	Ptr<BackgroundSubtractorKNN> ptrKNN = createBackgroundSubtractorKNN(100, 400, true);
	Ptr<BackgroundSubtractorMOG2> mog2 = createBackgroundSubtractorMOG2(100, 25, true);
	namedWindow("Extracted Foreground");
	VideoCapture pCapture;
	Mat pframe;
	pCapture = VideoCapture("G://BaiduNetdiskDownload//pets2001.avi");

	while (1)
	{
		pCapture >> pframe;
		if (pframe.data == NULL)
			return;
		cvtColor(pframe, greyimg, CV_BGR2GRAY);
		long long t = getTickCount();
		ptrKNN->apply(pframe, foreground, 0.01);
		long long t1 = getTickCount();
		mog2->apply(greyimg, foreground2, -1);
		long long t2 = getTickCount();
		_cprintf("t1 = %f t2 = %f\n", (t1 - t) / getTickFrequency(), (t2 - t1) / getTickFrequency());
		imshow("Extracted Foreground", foreground);
		imshow("Extracted Foreground2", foreground2);
		imshow("video", pframe);
		waitKey(10);
	}
	waitKey();
}
