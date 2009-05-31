/*  WQSG_UMD
*  Copyright (C) WQSG <wqsg@qq.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
// About.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "About.h"


// CAbout �Ի���

IMPLEMENT_DYNAMIC(CAbout, CDialog)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAbout::OnNMClickSyslink1)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK2, &CAbout::OnNMClickSyslink2)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK3, &CAbout::OnNMClickSyslink3)
END_MESSAGE_MAP()


// CAbout ��Ϣ�������

void CAbout::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute( NULL , L"open" , L"http://code.google.com/p/wqsg-umd" , NULL , NULL , SW_SHOW );

	*pResult = 0;
}

void CAbout::OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute( NULL , L"open" , L"http://code.google.com/p/wqsglib" , NULL , NULL , SW_SHOW );

	*pResult = 0;
}

BOOL CAbout::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str;
	str.LoadString( IDS_APP_NAME );
	SetDlgItemText( IDC_APP_NAME , str );

	str.LoadString( IDS_APP_VER );
	SetDlgItemText( IDC_APP_VER , L"v" + str );

	CString str2;
	str.LoadString( IDS_APP_AUTHOR );
	str2.LoadString( IDS_APP_AUTHOR2 );

	SetDlgItemText( IDC_EDIT1 , str2 + L"(" + str + L")" + L"\r\nKid" );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAbout::OnNMClickSyslink3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute( NULL , L"open" , L"http://wqsg.ys168.com" , NULL , NULL , SW_SHOW );

	*pResult = 0;
}
