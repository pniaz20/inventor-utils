/*
 * Copyright 1996, Portable Graphics, Inc., Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * IRIS GL and OpenGL are registered trademarks, and Inventor and
 * Open Inventor are trademarks of Silicon Graphics, Inc.
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Portable Graphics, Inc.,
 * 3006 Longhorn Blvd. Suite #105,  Austin, TX 78758-7631.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF PORTABLE GRAPHICS, INC. AND SILICON GRAPHICS, INC. ANY
 * DUPLICATION, MODIFICATION, DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN
 * WHOLE, OR IN PART, IS STRICTLY PROHIBITED WITHOUT THE PRIOR EXPRESS
 * WRITTEN  PERMISSION OF PORTABLE GRAPHICS, INC.
 */


// mazeview.cpp : implementation of the CMazeView class
//

#include "stdafx.h"
#include "maze.h"

#include "mazedoc.h"
#include "mazeview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMazeView

IMPLEMENT_DYNCREATE(CMazeView, SoMfcView)

BEGIN_MESSAGE_MAP(CMazeView, SoMfcView)
	//{{AFX_MSG_MAP(CMazeView)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMazeView construction/destruction

CMazeView::CMazeView() : SoMfcView(RUNTIME_CLASS(SoMfcExaminerViewer))
{
	// TODO: add construction code here
	rightMouseDown = FALSE;
	leftMouseDown = FALSE;
}

CMazeView::~CMazeView()
{
}

 
 
/////////////////////////////////////////////////////////////////////////////
// CMazeView diagnostics

#ifdef _DEBUG
void CMazeView::AssertValid() const
{
	CView::AssertValid();
}

void CMazeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMazeDoc* CMazeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMazeDoc)));
	return (CMazeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMazeView message handlers
 
 
 
BOOL CMazeView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// just keep the old arrow cursor, unless we've turn viewing on
	// through the right mouse menu
	SoMfcExaminerViewer * pv = GetExaminerViewerPtr();
	if (pv->IsViewing())
		return SoMfcView::OnSetCursor(pWnd, nHitTest, message);
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	return TRUE;
}

void CMazeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	SoMfcView::OnUpdate(pSender, lHint, pHint);
	SoMfcExaminerViewer * pv = GetExaminerViewerPtr();
	pv->SetViewing(FALSE);
	TRACE("OnUpdate\n");
}
