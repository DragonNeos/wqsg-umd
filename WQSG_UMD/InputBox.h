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
#pragma once
#include "afxwin.h"


// CInputBox �Ի���

class CInputBox : public CDialog
{
	u32 m_val;
	u32 m_maxval;
	DECLARE_DYNAMIC(CInputBox)

public:
	CInputBox( CString a_strTitle , CString a_strDec ,
		u32 old , u32 max , CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputBox();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_ʮ����;
	CString m_ʮ������;

	CString m_strTitle ;
	CString m_strDec;
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	virtual BOOL OnInitDialog();
	s32 GetVal(void);
private:
	CEdit m_c10;
	CEdit m_c16;
};
