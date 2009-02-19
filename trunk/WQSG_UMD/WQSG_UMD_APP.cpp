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
// WQSG_UMD.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "WQSG_UMD_APP.h"
#include "WQSG_UMDDlg.h"
#include "consolecommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWQSG_UMDApp

BEGIN_MESSAGE_MAP(CWQSG_UMDApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWQSG_UMDApp ����

CWQSG_UMDApp::CWQSG_UMDApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWQSG_UMDApp ����

CWQSG_UMDApp theApp;


// CWQSG_UMDApp ��ʼ��
int WQSG_Main( LPWSTR* szArglist , int nArgs )
{

	if(1)
	{

	}
	wprintf( L"��ʱ��֧��������" );

	_putws( L"123��ʱ��֧��������456" );
	return 0;
}

BOOL CWQSG_UMDApp::InitInstance()
{
	m_bCmdMode = FALSE;
	m_CmdR = 0;

	int nArgs = 0;
	LPWSTR* szArglist = CommandLineToArgvW( GetCommandLineW() , &nArgs );
	if( szArglist && nArgs > 1)
	{
		m_bCmdMode = TRUE;
		if (!ParseCommandParam(szArglist, nArgs))
			{m_CmdR = -1;}
	}
	else
	{
		// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
		// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
		//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
		INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(InitCtrls);
		// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
		// �����ؼ��ࡣ
		InitCtrls.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&InitCtrls);

		CWinApp::InitInstance();

		// ��׼��ʼ��
		// ���δʹ����Щ���ܲ�ϣ����С
		// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
		// ����Ҫ���ض���ʼ������
		// �������ڴ洢���õ�ע�����
		// TODO: Ӧ�ʵ��޸ĸ��ַ�����
		// �����޸�Ϊ��˾����֯��
		SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

		CWQSG_UMDDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: �ڴ˷��ô����ʱ��
			//  ��ȷ�������رնԻ���Ĵ���
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: �ڴ˷��ô����ʱ��
			//  ��ȡ�������رնԻ���Ĵ���
		}
	}
	LocalFree( szArglist );
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


int CWQSG_UMDApp::ExitInstance()
{
	return m_bCmdMode ? (CWinApp::ExitInstance(), m_CmdR) : CWinApp::ExitInstance();
}