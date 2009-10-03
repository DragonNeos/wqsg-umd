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
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include<WQSG_lib.h>
#include<ISO/ISO_App.h>

class CWQSGFileDialog;
class CWQSGFileDialog_Save
{
protected:
	CString m_strFolderPath;
	CString m_strFilter;
	CString m_strDefExt;
	CString m_strFileName;

	CString m_strWindowTitle;
	CWQSGFileDialog* m_pDlg;
public:
	explicit CWQSGFileDialog_Save(LPCTSTR lpszFilter = NULL,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL
		)
		: m_pDlg( NULL )
		, m_strFilter(lpszFilter)
		, m_strDefExt(lpszDefExt)
		, m_strFileName(lpszFileName)
	{
	}

	virtual ~CWQSGFileDialog_Save();

	virtual INT_PTR DoModal();

	CString GetPathName()const;

	void SetWindowTitle( LPCTSTR lpszTitle )
	{
		m_strWindowTitle = lpszTitle;
	}
};

class CWQSGFileDialog_Open
{
protected:
	CString m_strFolderPath;
	CString m_strFilter;
	CString m_strFileName;

	CString m_strWindowTitle;
	CWQSGFileDialog* m_pDlg;
public:
	explicit CWQSGFileDialog_Open(LPCTSTR lpszFilter = NULL,
		LPCTSTR lpszFileName = NULL
		)
		: m_pDlg( NULL )
		, m_strFilter(lpszFilter)
		, m_strFileName(lpszFileName)
	{
	}

	virtual ~CWQSGFileDialog_Open();

	virtual INT_PTR DoModal();

	CString GetPathName()const;

	void SetWindowTitle( LPCTSTR lpszTitle )
	{
		m_strWindowTitle = lpszTitle;
	}
};

class CWQSGFileDialog_OpenS
{
protected:
	CString m_strFolderPath;
	CString m_strFilter;

	CString m_strWindowTitle;
	CWQSGFileDialog* m_pDlg;
	CString m_strNameBuffer;
public:
	explicit CWQSGFileDialog_OpenS(LPCTSTR lpszFilter = NULL)
		: m_pDlg( NULL )
		, m_strFilter(lpszFilter)
	{
		m_strNameBuffer.GetBuffer(65536);
	}

	virtual ~CWQSGFileDialog_OpenS();

	virtual INT_PTR DoModal();

	void SetWindowTitle( LPCTSTR lpszTitle )
	{
		m_strWindowTitle = lpszTitle;
	}

	POSITION GetStartPosition( ) const;

	BOOL GetNextPathName( CString& a_strPathName , POSITION& pos) const;
};
