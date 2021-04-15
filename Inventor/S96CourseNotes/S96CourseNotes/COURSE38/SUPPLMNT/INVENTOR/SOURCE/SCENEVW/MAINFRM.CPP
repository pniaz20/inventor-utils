// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"


#include "mainfrm.h"

#include "SceneVw.h"
#include "SVDoc.h"
#include "SVView.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, SoMfcFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, SoMfcFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, SoMfcFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, SoMfcFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, SoMfcFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, SoMfcFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, SoMfcFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_THUMBWHEELBAR, OnThumbwheelbar)
	ON_COMMAND(ID_CAMERATOOLBAR, OnCameratoolbar)
	ON_UPDATE_COMMAND_UI(ID_CAMERATOOLBAR, OnUpdateCameratoolbar)
	ON_UPDATE_COMMAND_UI(ID_THUMBWHEELBAR, OnUpdateThumbwheelbar)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

static UINT BASED_CODE indicators[] =
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

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (SoMfcFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.cx = 707;
	cs.cy = 600;
	cs.x = 0;
	cs.y = 0;

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

	pMenu = GetMenu()->GetSubMenu( 7 );

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

	pMenu = GetMenu()->GetSubMenu( 7 );

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


