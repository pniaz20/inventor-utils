// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "drop.h"

#include "MainFrm.h"
#include "dropView.h"
#include "dropDoc.h"
#include "TsField.h"
#include "helpDialog.h"

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
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_STATUS,    OnUpdateIndicatorStatus)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SCORE,    OnUpdateIndicatorScore)
	ON_WM_HELPINFO()  
	ON_COMMAND(ID_DROP_HELP, OnDropHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_STATUS,
	ID_INDICATOR_SCORE, 
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

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}				
	m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_NOBORDERS, 250);

	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_STATUS, 0, 150);	
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_SCORE, 0, 80);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cy = GetSystemMetrics(SM_CYFULLSCREEN);
	cs.cy = (cs.cy * 4) / 5;
	cs.cx = (cs.cy * 2) / 3;
	TRACE("setting cx, cy: %d %d\n", cs.cx, cs.cy);

	

	return CFrameWnd::PreCreateWindow(cs);
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
 

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	SoMfcFrameWnd::OnSize(nType, cx, cy);

	CDropView *view = (CDropView *)GetActiveView();
	if (view)
		view->NewSize(cx, cy);

	TRACE("OnSize: %d %d\n", cx, cy);
	// TODO: Add your message handler code here
}
 

// Update status pane indicator: 
//
void CMainFrame::OnUpdateIndicatorStatus(CCmdUI* pCmdUI)
{
    // Make sure to enable the pane!
    pCmdUI->Enable(TRUE);
	CDropView *pView = (CDropView *)GetActiveView();
	if (pView) {
		CDropDoc *pDoc = (CDropDoc *)pView->GetDocument();
		TsField *pField = pDoc->theField;
		if (!pField->isStarted())
			pCmdUI->SetText("Press <Enter> to start game!");
		else if (pField->isPaused())
			pCmdUI->SetText("Press <Enter> to resume game");
		else
			pCmdUI->SetText("Playing");
	}
}

// Update status pane indicator: 
//
void CMainFrame::OnUpdateIndicatorScore(CCmdUI* pCmdUI)
{	
	// Make sure to enable the pane!
    pCmdUI->Enable(TRUE);

	char buffer[80];
	CDropView *pView = (CDropView *)GetActiveView();
	if (pView) {
		CDropDoc *pDoc = (CDropDoc *)pView->GetDocument();
		TsField *pField = pDoc->theField;
		sprintf(buffer, "Score: %06d", pField->getScore());
		pCmdUI->SetText(buffer);
	} else {
		pCmdUI->SetText("Score: 000000");
	}
}

void CMainFrame::OnDropHelp() 
{
	// TODO: Add your command handler code here
	CDropDoc *pDoc;
	TsField *pField=NULL;
	CHelpDialog mydialog;
	CDropView *pView = (CDropView *)GetActiveView();
	if (pView) {
		pDoc = (CDropDoc *)pView->GetDocument();
		pField = pDoc->theField;
		if (!pField->isPaused()) 
			pField->pauseGame();
	}

	mydialog.DoModal();

	if (pField && pField->isPaused())
		pField->resumeGame();
}
