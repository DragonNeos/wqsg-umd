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
// WQSG_UMDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG_UMD_APP.h"
#include "WQSG_UMDDlg.h"


#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct
{
	WCHAR const*const	name;
	const int			w;
}WQSG_FileList[] = {
	{	L"fileName"	,	300	},
	{	L"LBA"		,	80	},
	{	L"size"		,	100	},
};
// CWQSG_UMDDlg �Ի���
CWQSG_UMDDlg::CWQSG_UMDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWQSG_UMDDlg::IDD, pParent)
	, m_oldOffset(0)
	, m_pathW(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWQSG_UMDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE, m_cFileList);
	DDX_Text(pDX, IDC_EDIT1, m_pathW);
}

BEGIN_MESSAGE_MAP(CWQSG_UMDDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CWQSG_UMDDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_FILE, &CWQSG_UMDDlg::OnLvnItemActivateListFile)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CWQSG_UMDDlg::OnBnClickedButtonUp)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FILE, &CWQSG_UMDDlg::OnNMRClickListFile)
	ON_COMMAND(ID_32771_SAVEFILE, &CWQSG_UMDDlg::OnSavefile)
	ON_COMMAND(ID_32774, &CWQSG_UMDDlg::On32774_�滻�ļ�)
	ON_COMMAND(ID_32776, &CWQSG_UMDDlg::On32776_д�ļ�ƫ��)
	ON_BN_CLICKED(IDC_BUTTON2, &CWQSG_UMDDlg::OnBnClickedButton2)
END_MESSAGE_MAP()// CWQSG_UMDDlg ��Ϣ�������
BOOL CWQSG_UMDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	MEMORYSTATUS info;
	GlobalMemoryStatus( &info );
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	{
		CString str1,str2,str3;
		str1.LoadString( IDS_APP_NAME );
		str2.LoadString( IDS_APP_VER );

		SetWindowText( str1 + L" v" + str2 );
	}
	m_cFileList.EnableWindow( FALSE );
	m_cFileList.SetExtendedStyle( m_cFileList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	const int count = sizeof(WQSG_FileList)/sizeof(*WQSG_FileList);
	for( int i = 0 ; (i >= 0) && (i < count) ; ++i )
	{
		if( i != m_cFileList.InsertColumn( i , WQSG_FileList[i].name , 0 , WQSG_FileList[i].w ) )
		{
			MessageBox( L"FileList ��ʼ��ʧ��" );
			EndDialog( IDCANCEL );
			return FALSE;
		}
	}
	{
		HIMAGELIST hi = NULL;
		SHFILEINFO shfi;

		memset(&shfi, 0 ,sizeof(shfi));
		hi = (HIMAGELIST)SHGetFileInfoW( L"TESTICON" , FILE_ATTRIBUTE_DIRECTORY , &shfi , sizeof(shfi) ,
			SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES );

		if( !hi )
			ASSERT( FALSE );

		IMAGEINFO info = {0};
		if( !CImageList::FromHandle(hi)->GetImageInfo( 0 , &info ) ||
			!m_imageList.Create( info.rcImage.right , info.rcImage.bottom , ILC_COLOR , 1 , 1 ) )
			ASSERT( FALSE );

		m_imageList.SetBkColor( m_cFileList.GetBkColor() );

		m_imageList.Add( shfi.hIcon );

		memset( &shfi , 0 , sizeof(shfi) );
		if( !SHGetFileInfoW( L"TESTICON" , 0 , &shfi , sizeof(shfi) ,
			SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES ) )
			ASSERT( FALSE );

		m_imageList.Add( shfi.hIcon );
	}

	m_cFileList.SetImageList( &m_imageList , LVSIL_SMALL );
	//--------------------------------------------------------------
	m_menu.DestroyMenu();
	if( !m_menu.LoadMenu( IDR_MENU1 ) )
	{
		MessageBox( L"������Դʧ��(menu)" );
		EndDialog( IDCANCEL );
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
// �����Ի��������С����ť������Ҫ����Ĵ��������Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó����⽫�ɿ���Զ���ɡ�
void CWQSG_UMDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CWQSG_UMDDlg::OnQueryDragIcon(){	return static_cast<HCURSOR>(m_hIcon);}
void CWQSG_UMDDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
	EndDialog( IDCANCEL );
}

void CWQSG_UMDDlg::OnCancel(){}
void CWQSG_UMDDlg::OnOK(){}
bool CWQSG_UMDDlg::OpenISO( CStringW ISO_PathName , const BOOL bCanWrite )
{
	CloseISO();
	if( !m_umd.OpenISO( ISO_PathName , bCanWrite , E_WIT_UMD ) )
	{
		MessageBox( m_umd.GetErrStr() );
		return false;
	}
	m_path = L"";
	UpDataGUI();
	m_cFileList.EnableWindow( TRUE );
	return true;
}

void CWQSG_UMDDlg::CloseISO()
{
	m_cFileList.EnableWindow( FALSE );
	m_umd.CloseISO( );
	m_path = "";
	UpDataGUI();
}

void CWQSG_UMDDlg::UpDataGUI()
{
	m_cFileList.DeleteAllItems();
#if 1
	SIsoFileFind* handle;
	if( m_umd.IsOpen() && (handle = m_umd.FindIsoFile( m_path )) )
	{
		SIsoFileData data;
		while( m_umd.FindNextIsoFile( handle , data ) )
		{
			CString str;
			str = data.name;
			const int index = m_cFileList.InsertItem( m_cFileList.GetItemCount() , str , ((data.isDir)?0:1) );
			if( index >= 0 )
			{
				if( data.isDir )
				{
					m_cFileList.SetItemData( index , 0 );
				}
				else
				{
					CString tmp;

					tmp.Format( L"%d" , data.lba );
					m_cFileList.SetItemText( index , 1 , tmp );

					tmp.Format( L"%d" , data.size );
					m_cFileList.SetItemText( index , 2 , tmp );

					m_cFileList.SetItemData( index , 1 );
				}
			}
		}
		m_umd.CloseFindIsoFile( handle );

		m_pathW = m_path;
		UpdateData( FALSE );
	}
#endif
}

void CWQSG_UMDDlg::OnBnClickedButton1()
{
	static CString strPath;
	::CWQSGFileDialog dlg( TRUE );
	dlg.m_ofn.lpstrFilter = L"*.ISO\0*.iso\0\0";
	dlg.m_ofn.lpstrInitialDir = strPath;

	CString name;
#if _DEBUG && 0
	name = "s:\\Luxor.iso";
	OpenISO( name , FALSE );
#else
	if( IDOK != dlg.DoModal() )
		return;

	strPath = dlg.GetFolderPath();

	name = dlg.GetPathName();
	OpenISO( name , TRUE );
#endif
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CWQSG_UMDDlg::OnLvnItemActivateListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	if( 0 != m_cFileList.GetItemData( pNMIA->iItem ) )
		return;

	CString strNameW( m_cFileList.GetItemText( pNMIA->iItem , 0 ) );

	CStringA strNameA;
	strNameA = strNameW;
#if 0
	_tISO_DirEnt tP_DirEnt;
	if( !m_umd.GetPathDirEnt( tP_DirEnt , m_path ) )
	{
		CStringW path;
		MessageBox( m_umd.GetErrStr() , path = m_path );
		CloseISO();
		return ;
	}
	_tISO_DirEnt tmp;
	if( m_umd.FindFile( tP_DirEnt , strNameA.GetBuffer() , tmp ) < 0 )
	{
		MessageBox( L"Ŀ¼�����?" );
		CloseISO();
		return ;
	}

	if( (tmp.attr & 2) != 2 )
		return;
#endif
	if( m_path.Right( 1 ) != '/' )
		m_path += '/';

	m_path += strNameA;

	UpDataGUI();
}

BOOL CWQSG_UMDDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if( WM_DROPFILES == pMsg->message )
	{
		const HDROP hDrop = (HDROP)pMsg->wParam;
		if( pMsg->hwnd == m_cFileList.m_hWnd )
		{
			WCHAR strPathName[MAX_PATH*2];

			const int fileCount = DragQueryFile( hDrop , (UINT)-1 , NULL , 0 );

			for( int i = 0 ; (i>=0) && (i<fileCount) && ( DragQueryFile( hDrop , i , strPathName , MAX_PATH*2 ) != (UINT)-1 ) ; ++i )
			{
				if( !m_umd.�����ļ�( strPathName , m_path , 0 ) )
				{
					MessageBox( m_umd.GetErrStr() );
					break;
				}
			}
			UpDataGUI();
		}
		DragFinish( hDrop );
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CWQSG_UMDDlg::OnBnClickedButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringA path( m_path );
	int pos = path.ReverseFind( L'/' );
	if( pos >= 0 )
		path = path.Left( pos );

	m_path = path;
	UpDataGUI();
}

void CWQSG_UMDDlg::OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//------------------------------------
	CPoint pos( pNMItemActivate->ptAction );
	m_cFileList.ClientToScreen( &pos );

	const int count = m_cFileList.GetSelectedCount();

	if( count > 0 )
	{
		CMenu*const sub = m_menu.GetSubMenu( (count>1)?0:1 );
		if( sub )
			sub->TrackPopupMenu( TPM_LEFTALIGN /*|TPM_RIGHTBUTTON*/ , pos.x , pos.y , this );
	}
}

#include<WQSG_DirDlg.h>
void CWQSG_UMDDlg::OnSavefile()
{
	// TODO: �ڴ���������������
	CWQSG_DirDlg dlg( m_hWnd , L"���·��..." , m_LastSelDir.GetBuffer() );
	WCHAR outPath[MAX_PATH*2];
	if( !dlg.GetPath( outPath ) )
		return ;

	m_LastSelDir = outPath ;
	if( m_LastSelDir.Right( 1 ) != L'\\' )
		m_LastSelDir += L'\\';

	POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
	int index = 0;
	while( (index = m_cFileList.GetNextSelectedItem( pos )) >= 0 )
	{
		CString str( m_cFileList.GetItemText( index , 0 ) );
		CStringA strA;	strA = str;

		if( !m_umd.�����ļ�( m_LastSelDir + str , m_path , strA ) )
		{
			MessageBox( m_umd.GetErrStr() );
			break;
		}
	}
}

void CWQSG_UMDDlg::On32774_�滻�ļ�()
{
	// TODO: �ڴ���������������
	POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
	const int index = m_cFileList.GetNextSelectedItem( pos );
	if( index >= 0 )
	{
		CString str ( m_cFileList.GetItemText( index , 0 ) );
		CStringA strA; strA = str;

		static CString strPath;
		::CWQSGFileDialog dlg( TRUE );
		dlg.m_ofn.lpstrFilter = L"*.*\0*.*\0\0";
		dlg.m_ofn.lpstrTitle = L"ѡ���滻�õ��ļ�...";
		dlg.m_ofn.lpstrInitialDir = strPath;
		if( IDOK != dlg.DoModal() )
			return;

		strPath = dlg.GetFolderPath();

		if( !m_umd.�滻�ļ�( m_path , strA , dlg.GetPathName() ) )
			MessageBox( m_umd.GetErrStr() );
	}
}

#include "InputBox.h"
void CWQSG_UMDDlg::On32776_д�ļ�ƫ��()
{
	// TODO: �ڴ���������������
	POSITION pos = m_cFileList.GetFirstSelectedItemPosition();
	const int index = m_cFileList.GetNextSelectedItem( pos );
	if( index >= 0 )
	{
		CString name( m_cFileList.GetItemText( index , 0 ) );
		CStringA nameA;	nameA = name;

		SIsoFileData data;
		if( !m_umd.GetFileData( data , m_path , nameA ) )
		{
			MessageBox( m_umd.GetErrStr() );
			return ;
		}

		static CString strPath;
		CWQSGFileDialog dlg( TRUE );
		dlg.m_ofn.lpstrFilter = L"*.*\0*.*\0\0";
		dlg.m_ofn.lpstrTitle = L"ѡ��Ҫ������ļ�...";
		dlg.m_ofn.lpstrInitialDir = strPath;

		if( IDOK != dlg.DoModal() )
			return;

		strPath = dlg.GetFolderPath();

		CInputBox ibox( m_oldOffset , data.size );
		if( IDOK != ibox.DoModal() )
			return ;

		m_oldOffset = ibox.GetVal();

		if( !m_umd.д�ļ�ƫ��( m_path , nameA , m_oldOffset , dlg.GetPathName() ) )
			MessageBox( m_umd.GetErrStr() );
	}
}

void CWQSG_UMDDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAbout dlg;
	dlg.DoModal();
}
