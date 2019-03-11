// create.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "create.h"
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
	int exist[M];			//是否存在

};
typedef struct
{
	int count;				//景点数量
	CString Pname[M];		//景点名称
	CString Intro[M];		//景区介绍
	Matrix mat;				// 邻接矩阵
}Sce;						//景区类
Sce S;
int chose = 0;				//边点切换按钮
CString In1, In2;			//用来写文件



// create 对话框

IMPLEMENT_DYNAMIC(create, CDialogEx)

create::create(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

create::~create()
{
}

void create::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(create, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &create::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &create::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &create::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &create::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &create::OnBnClickedButton5)
	ON_BN_CLICKED(IDOK, &create::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &create::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &create::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &create::OnBnClickedButton7)
END_MESSAGE_MAP()


// create 消息处理程序

//切换边点信息
void create::OnBnClickedButton1()
{
	if (chose == 0)
		printvex();
	else
		printedge();
	// TODO: 在此添加控件通知处理程序代码
}

//增加景点
void create::OnBnClickedButton2()
{
	int num = GetDlgItemInt(IDC_EDIT17);
	if (S.mat.exist[num] == 1)
	{
		MessageBox("您输入的景点已存在");
	}
	else
	{
		GetDlgItemText(IDC_EDIT15, S.Pname[num]);
		GetDlgItemText(IDC_EDIT16, S.Intro[num]);
		S.mat.exist[num] = 1;
		S.count++;
		printvex();
	}
	

	// TODO: 在此添加控件通知处理程序代码
}


void create::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//删除景点
void create::OnBnClickedButton4()
{
	int num = GetDlgItemInt(IDC_EDIT17);
	if (S.mat.exist[num] == 0)
	{
		MessageBox("您输入的景点不存在");
	}
	else
	{
		S.mat.exist[num] = 0;
		printvex();
		S.count--;

	}

	// TODO: 在此添加控件通知处理程序代码
}

//打印 景点信息
void create::printvex()
{
	chose = 1;
	CString Information;
	CString X("\r\n"),Y("景点信息如下：");
	CString str;														//整数类型转换
	str.Format("%d", S.count);
	Information += str + X;
	for (int i = 0; i < 60; i++)
	{
		{
			if (S.mat.exist[i])
			{
				str.Format("%d", i);
				Information += str + X + S.Pname[i] + X + S.Intro[i] + X;
			}
		}
		
	}
	In1 = Information;
	SetDlgItemText(IDC_EDIT1, Y + X + Information + X + X);
		// TODO: 在此添加控件通知处理程序代码
	//Information.Empty();

}

//打印 路径信息
void create::printedge()
{
	chose = 0;
	CString Information;
	CString X("\r\n"), Y("路径信息如下："), Z("      ");
	CString str1, str2, str3;														//整数类型转换
	for (int i = 0; i < 60; i++)
	{
		for (int j = i; j < 60; j++)								//金字塔形输出
		if (S.mat.m[i][j])
		{
			printf("%d      %d      %d", i, j, S.mat.m[i][j]);
			str1.Format("%d", i);
			str2.Format("%d", j);
			str3.Format("%d", S.mat.m[i][j]);
			Information += str1 + Z + str2 + Z + str3 + X + X;
		}
			
	}
	In2 = Information;
	SetDlgItemText(IDC_EDIT1, Y + X + Information + X + X);
	// TODO: 在此添加控件通知处理程序代码
	//Information.Empty();
	// TODO: 在此添加控件通知处理程序代码
}

BOOL create::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	memset(S.mat.m, 0, sizeof(S.mat.m));
	memset(S.mat.exist, 0, sizeof(S.mat.exist));
	CString strline1;											
	CStdioFile file1;											
	FILE * file2;
	BOOL flag1 = file1.Open(_T("F://Vex.txt"), CFile::modeRead); 
	file2 = fopen("f://Edge.txt", "r");
	//逐行读文件
	file1.ReadString(strline1);
	S.count = _ttoi(strline1);
	CString n("");
	for (int i = 0; i < S.count; i++)
	{
		file1.ReadString(n);
		int nn = _ttoi(n);
		S.mat.exist[nn] = 1;
		file1.ReadString(S.Pname[nn]);
		file1.ReadString(S.Intro[nn]);
	}
	//按规定格式读
	int i1 = 0;
	int j1 = 0;
	int k1 = 0;
	while (!feof(file2))
	{
		fscanf(file2, "%d%d%d", &i1, &j1, &k1);
		S.mat.m[j1][i1] = k1;
		S.mat.m[i1][j1] = k1;
	}

	file1.Close();
	fclose(file2);
	printvex();
	

	// TODO:  在此添加额外的初始化

	return TRUE;  
}

//增加边
void create::OnBnClickedButton5()
{
	int num1 = GetDlgItemInt(IDC_EDIT14);
	int num2 = GetDlgItemInt(IDC_EDIT10);
	int num3 = GetDlgItemInt(IDC_EDIT13);
	if (S.mat.exist[num1] == 0 || S.mat.exist[num2] == 0)
	{
		MessageBox("您输入的景点不存在");
	}
	else
	{
		S.mat.m[num1][num2] = S.mat.m[num2][num1] = num3;
		printedge();
	}

}

//写入文件
void create::OnBnClickedOk()
{
	fstream file1("F://Vex.txt", ios::out);																//清空文件里的内容
	fstream file2("F://Edge.txt", ios::out);
	file1.close();
	file2.close();
	CStdioFile File1;
	File1.Open("F://Vex.txt", CFile::modeReadWrite | CFile::modeNoTruncate | CFile::modeCreate);		//将CString量写入文件中
	File1.SeekToEnd();
	File1.WriteString(In1);
	File1.Close();

	CStdioFile File2;
	File2.Open("F://Edge.txt", CFile::modeReadWrite | CFile::modeNoTruncate | CFile::modeCreate);
	File2.SeekToEnd();
	File2.WriteString(In2);
	File2.Close();
	// TODO: 在此添加控件通知处理程序代码
	//fstream file1("F://Vex.txt", ios::out);
	//fstream file2("F://Edge.txt", ios::out);
	CDialogEx::OnOK();
}

//修改景点
void create::OnBnClickedButton3()
{
	int num = GetDlgItemInt(IDC_EDIT20);
	if (S.mat.exist[num] == 0)
	{
		MessageBox("您输入的景点不存在");
	}
	else
	{
		GetDlgItemText(IDC_EDIT18, S.Pname[num]);
		GetDlgItemText(IDC_EDIT19, S.Intro[num]);
		printvex();
	}
	
}

//修改边
void create::OnBnClickedButton6()
{
	int num1 = GetDlgItemInt(IDC_EDIT11);
	int num2 = GetDlgItemInt(IDC_EDIT6);
	int num3 = GetDlgItemInt(IDC_EDIT7);
	if (S.mat.exist[num1] == 0 || S.mat.exist[num2] == 0)
	{
		MessageBox("您输入的景点不存在");
	}
	else
	{
		S.mat.m[num1][num2] = S.mat.m[num2][num1] = num3;
		printedge();
	}
	
}

//删除边
void create::OnBnClickedButton7()
{
	int num1 = GetDlgItemInt(IDC_EDIT12);
	int num2 = GetDlgItemInt(IDC_EDIT9);
	S.mat.m[num1][num2] = S.mat.m[num2][num1] = 0;
	printedge();
	// TODO: 在此添加控件通知处理程序代码
}
