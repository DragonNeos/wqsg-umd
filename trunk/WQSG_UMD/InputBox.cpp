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
// InputBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG_UMD_APP.h"
#include "InputBox.h"


// CInputBox �Ի���

IMPLEMENT_DYNAMIC(CInputBox, CDialog)

CInputBox::CInputBox( u32 old , u32 max , CWnd* pParent /*=NULL*/)
	: CDialog(CInputBox::IDD, pParent)
	, m_ʮ����(_T("0"))
	, m_ʮ������(_T("0"))
	, m_val(old)
	, m_maxval( max )
{

}

CInputBox::~CInputBox()
{
}

void CInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ʮ����);
	DDV_MaxChars(pDX, m_ʮ����, 10);
	DDX_Text(pDX, IDC_EDIT2, m_ʮ������);
	DDV_MaxChars(pDX, m_ʮ������, 8);
	DDX_Control(pDX, IDC_EDIT1, m_c10);
	DDX_Control(pDX, IDC_EDIT2, m_c16);
}


BEGIN_MESSAGE_MAP(CInputBox, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CInputBox::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CInputBox::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CInputBox ��Ϣ�������

void CInputBox::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	s64 val = _ttoi64( m_ʮ����.GetBuffer() );

	bool �ı� = true;
	if( val < 0 )
		val = 0;
	else if( val > m_maxval )
		val = m_maxval;
	else
		�ı� = false;

	m_val = (u32)val;

	if( �ı� )
		m_ʮ����.Format( L"%d" , m_val );
	m_ʮ������.Format( L"%X" , m_val );

	UpdateData(FALSE);
}

void CInputBox::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int start , end;
	m_c16.GetSel( start , end );
	m_ʮ������.MakeUpper();

	for( int i = 0 ; (i>=0) && m_ʮ������[i] ; ++i )
	{
		const WCHAR ch = m_ʮ������[i];
		if( ( ch < L'0' || ch > L'9' ) && ( ch < L'A' || ch > L'F' ) )
		{
			m_ʮ������.Delete( i );
			if( start > i-- )
				--start;
		}
	}

	s64 val = 0;
	swscanf( m_ʮ������.GetBuffer() , L"%X" , &val );

	bool �ı� = true;
	if( val < 0 )
		val = 0;
	else if( val > m_maxval )
		val = m_maxval;
	else
		�ı� = false;

	m_val = (u32)val;

	m_ʮ����.Format( L"%d" , m_val );
	if( �ı� )
		m_ʮ������.Format( L"%X" , m_val );

	UpdateData(FALSE);
	m_c16.SetSel( start , start );
}

BOOL CInputBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if( m_maxval < 0 )
		m_maxval = 0;

	if( m_val < 0 )
		m_val = 0;
	else if( m_val > m_maxval )
		m_val = m_maxval;

	m_ʮ����.Format( L"%d" , m_val );
	m_ʮ������.Format( L"%X" , m_val );

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

s32 CInputBox::GetVal(void)
{
	return s32(m_val);
}
