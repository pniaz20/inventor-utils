// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ivview.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, SoMfcFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, SoMfcFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_THUMBWHEELBAR, OnThumbwheelbar)
	ON_COMMAND(ID_CAMERATOOLBAR, OnCameratoolbar)
	ON_UPDATE_COMMAND_UI(ID_CAMERATOOLBAR, OnUpdateCameratoolbar)
	ON_UPDATE_COMMAND_UI(ID_THUMBWHEELBAR, OnUpdateThumbwheelbar)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()		  
{
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	//set the Length and the Width.   
	cs.cx = 556;
	cs.cy = 471;
    
	return CFrameWnd::PreCreateWindow(cs);
}


	

void CMainFrame::OnThumbwheelbar() 
{
	
	m_pCommonFrame->ToggleThumbWheels();

}

void CMainFrame::OnCameratoolbar() 
{
	
 	m_pCommonFrame->ToggleInventorToolbar();
}

void CMainFrame::OnUpdateCameratoolbar(CCmdUI* pCmdUI) 
{
	CMenu *pMenu;

	pMenu = GetMenu()->GetSubMenu( 2 );

	if( FALSE == m_pCommonFrame->IsInventorToolbarVisible() )
	{
		pMenu->CheckMenuItem( ID_CAMERATOOLBAR, MF_BYCOMMAND | MF_UNCHECKED );
	}
	else
	{
		pMenu->CheckMenuItem( ID_CAMERATOOLBAR, MF_BYCOMMAND | MF_CHECKED );
	}
	
}

void CMainFrame::OnUpdateThumbwheelbar(CCmdUI* pCmdUI) 
{
	CMenu *pMenu;

	pMenu = GetMenu()->GetSubMenu( 2 );

	if( FALSE == m_pCommonFrame->IsThumbWheelsVisible() )
	{
		pMenu->CheckMenuItem( ID_THUMBWHEELBAR, MF_BYCOMMAND | MF_UNCHECKED );
	}
	else
	{
		pMenu->CheckMenuItem( ID_THUMBWHEELBAR, MF_BYCOMMAND | MF_CHECKED );
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	SoMfcFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	SoMfcFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	
}
