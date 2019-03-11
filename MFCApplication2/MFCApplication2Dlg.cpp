
// MFCApplication2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <sstream>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include"create.h"

using namespace std;
#define M 200
#define INF 99999

//定义的结构体
struct Matrix				//矩阵类
{
	int m[M][M];			//景点邻接矩阵
	int exist[M];			//查看这个点是否存在
	
};
typedef struct
{
	int count;				//景点数量
	CString Pname[M];		//景点名称
	CString Intro[M];		//景区介绍
	Matrix mat;				// 邻接矩阵
}Scenic;					//景区类
Scenic S;	




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
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_EN_CHANGE(SCREEN, &CMFCApplication2Dlg::OnEnChangeScreen)
	ON_EN_CHANGE(IDC_EDIT8, &CMFCApplication2Dlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication2Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication2Dlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication2Dlg::OnBnClickedButton6)
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


//dijstra求最短路径
void CMFCApplication2Dlg::OnBnClickedButton3()
{
	CString Information;										//显示屏幕操作
	CString X("最短路径为： "), Y("\r\n"), Z("  ----->  ");
	CString str;												//整数中作格式转换用
	int start = GetDlgItemInt(IDC_EDIT3);
	int end = GetDlgItemInt(IDC_EDIT5);							//交换一下，打印出来的就是正的
	int dis[M];													//单点到各点的最短路径数组
	int pre[M];													//存储前一个节点
	int visit[M];												//是否被访问

	//初始化
	memset(dis,INF, sizeof(dis));
	memset(pre, -1, sizeof(pre));
	memset(visit, 0, sizeof(visit));
	dis[start] = 0;
	visit[start] = 1;

	for (int j = 0; j < S.count; j++)									//把所有为0值变成无穷大
	{
		for(int i = 0; i < S.count; i++)
			if (S.mat.m[j][i] == 0)
			{
				S.mat.m[j][i] = INF;
			}
	}

	for (int i = 0; i < S.count; i++)									//将第一个点变为访问点
	{
			dis[i] = S.mat.m[start][i] + dis[start];
			pre[i] = start;
	}
	
	
	for (int j = 0; j < S.count; j++)
	{
		int min = INF;
		int mini = start;
		for (int i = 0; i < S.count; i++)
		{
			if (visit[i] == 0 && dis[i] < min)					//寻找相邻最小点
			{
				min = dis[i];
				mini = i;
			}
		}
		visit[mini] = 1;

		for (int i = 0; i < S.count; i++)						//更新其余未访问的边权
		{
			if (dis[i] > S.mat.m[mini][i] + dis[mini] && visit[i] == 0)
			{
				dis[i] = S.mat.m[mini][i] + dis[mini];
				pre[i] = mini;
			}
				
		}
		if (visit[end])											//找到终点并打印
		{
			int i = end;
			while (i != start)
			{
				Information += S.Pname[i] + Z;
				i = pre[i];
			}
			Information += S.Pname[i] + Y + Y;
			str.Format("%d", dis[end]);
			Information += X + str;
			SetDlgItemText(SCREEN, Information);
			MessageBox("最短距离已被加载");
			Information.Empty();
			break;
		}
		
	}

	// TODO: 在此添加控件通知处理程序代码
}


//读取文件操作
void CMFCApplication2Dlg::OnBnClickedButton5()
{
	memset(S.mat.m, 0, sizeof(S.mat.m));

	CString strline1;											//定义一个变量用于接收读取的一行内容
	CStdioFile file1;											//定义一个CStdioFile类的对象 file1
	FILE * file2;
	BOOL flag1 = file1.Open(_T("F://Vex.txt"), CFile::modeRead); //open函数需要传两个参数，前一个是文件路径，后一个是文件的打开模式
	file2 = fopen("f://Edge.txt", "r");

	if (flag1 == FALSE && file2 == FALSE)
	{
		MessageBox("文件打开失败！");
	}
	
	//逐行读文件
	file1.ReadString(strline1);
	S.count = _ttoi(strline1);
	CString n("");
	for (int i=0; i < S.count; i++)
	{
		file1.ReadString(n);
		int nn = _ttoi(n);										//字符转化成整数型
		file1.ReadString(S.Pname[nn]);
		file1.ReadString(S.Intro[nn]);

	}
	//MessageBox(_T("Vex.txt 读取成功"));

	//按规定格式读
	int i = 0;
	int j = 0;
	int k = 0;
	while (!feof(file2))
	{
		fscanf(file2, "%d%d%d", &i, &j, &k);
		S.mat.m[j][i] = k;
		S.mat.m[i][j] = k;
	}

	file1.Close();
	fclose(file2);

	CString  Information;										//screen显示的内容
	CString str;												//整形转为字符型所用
	CString X("      "), Y("\r\n");								//windows需要两个一起用
	Information += X;

	//打印行列号
	for (int i = 0; i < S.count; i++)							//列号
	{
		str.Format("%6d", i + 1);
		Information += str;
	}
	Information += Y + Y;										//两行比较明显，美观
	for (int i = 0; i < S.count; i++)
	{
		str.Format("%6d", i + 1);
		Information += str ;									//行号
		for (int j = 0; j < S.count; j++)
		{
			str.Format("%6d", S.mat.m[i][j]);
			Information += str ;
		}
		Information += Y + Y;
	}
	SetDlgItemText(SCREEN, Information);
	MessageBox("输出图的邻接矩阵成功！");

}


//功能四：prim算法铺路
//prim和dijstra代码相似，仅少量修改
void CMFCApplication2Dlg::OnBnClickedButton4()
{
	CString Information;										//显示屏幕操作
	CString X("长度: "), Y("\r\n"), Z(" -----> "), W("总共需要铺设:  ") ,F1(")   "), F2("(");
	CString str;												//整数中作格式转换用
	int start = 0;
	int dis[M];													//已访问点到未访问点的最短路径数组
	int count = 1;													//计数
	int visit[M];												//是否被访问
	int longth = 0;													//总长度

	//初始化
	memset(dis, INF, sizeof(dis));
	memset(visit, 0, sizeof(visit));
	dis[start] = 0;
	visit[start] = 1;
	Information += "铺设的道路依次为： " + Y;

	for (int j = 0; j < S.count; j++)									//把所有为0值变成无穷大
	{
		for (int i = 0; i < S.count; i++)
			if (S.mat.m[j][i] == 0)
			{
				S.mat.m[j][i] = INF;
			}
	}
	Information += S.Pname[0] + Z;
	for (int i = 0; i < S.count; i++)							//将第一个点变为访问点
	{
		dis[i] = S.mat.m[start][i];
	}




	for (int j = 0; j < S.count; j++)
	{
		int mini = start;
		for (int i = 0; i < S.count; i++)
		{
			if (visit[i] == 0 && dis[i] < dis[mini])					//寻找相邻最小点
			{
				mini = i;
			}
		}
		visit[mini] = 1;
		count++;
		str.Format("%d", dis[mini]);
		longth += dis[mini];
		if (count == S.count)											//修饰打印格式
		{
			Information += F2 + X + str + F1 + S.Pname[mini];
			break;
		}
		else
		{
			Information += F2 + X + str + F1 + S.Pname[mini] + Z;
		}
		
		for (int i = 1; i < S.count; i++)						//更新其余未访问的边权
		{
			if (dis[i] > S.mat.m[mini][i])
			{
				dis[i] = S.mat.m[mini][i];
			}

		}
	}
	
	Information += + Y + Y + W +Y;
	str.Format("%d", longth);
	Information += str;
	SetDlgItemText(SCREEN, Information);
	MessageBox("输出铺设电路成功！");
	// TODO: 在此添加控件通知处理程序代码*/
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::OnEnChangeScreen()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


//功能一： 景点查询
void CMFCApplication2Dlg::OnBnClickedButton1()
{
	int Search = GetDlgItemInt(IDC_EDIT2);
	CString Information;
	CString str;
	CString X("输入的景点名称为："), Y("\r\n"), Z("输入景点景区介绍: ");
	CString X1("相邻景点："), Y1(" "), Z1("距离为：");
	
	//输入景点信息
	Information += X + S.Pname[Search] ;
	Information += Y + Y;
	Information += Z + S.Intro[Search];
	Information += Y + Y + Y;

	for (int j = 0; j < S.count; j++)
	{
		if (S.mat.m[Search][j])
		{
			Information += X1 + S.Pname[j];
			Information += Y + Y;
			str.Format("%6d", S.mat.m[Search][j]);
			Information += Z1 + str;
			Information += Y + Y;
		}
	}
	SetDlgItemText(SCREEN, Information);
	MessageBox("已加载查询结果");
}




//功能二：景点导航
int Vis;														//起点
int visited[M];
CString  Information1;
CString X("建议路线： "), Y("\r\n"), Z("  ----->  ");
int Route[M];													//要注意的是编号从0开始的，记录路线
int number;														//记录是否全部走完

void CMFCApplication2Dlg::dfs(int i)
{
	visited[i] = 1;
	Route[++number] = i;

	for (int j = 0; j < S.count; j++)				
	{
		if (visited[j] == 0 && S.mat.m[i][j])					//dfs搜索
		{
				dfs(j);
		}
		
	}
	if (number == S.count - 1 && Route[0] == Vis)					//打印可行解
	{
		Information1 += X;
		for (int j = 0; j < S.count - 1; j++)
		{
			Information1 += S.Pname[Route[j]] + Z;
		}
		Information1 += S.Pname[Route[S.count - 1]] + Y + Y;
		SetDlgItemText(SCREEN, Information1);
		visited[i] = 0;												//向前回溯
		Route[number] = -1;
		number--;

	}
	else
	{
		visited[i] = 0;												//向前回溯
		Route[number] = -1;
		number--;
	}
	

	}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	memset(visited, 0, sizeof(visited));
	memset(Route, -1 , sizeof(Route));							//-1表示无前驱节点，即无法被访问
	number = -1;
	Vis = GetDlgItemInt(IDC_EDIT8);
	dfs(Vis);
	MessageBox("路径已被加载");
	Information1.Empty();										//用来反复激活使用
	// TODO: 在此添加控件通知处理程序代码
}



void CMFCApplication2Dlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnBnClickedButton6()
{
	create cre;
	cre.DoModal();
	
	// TODO: 在此添加控件通知处理程序代码
}
