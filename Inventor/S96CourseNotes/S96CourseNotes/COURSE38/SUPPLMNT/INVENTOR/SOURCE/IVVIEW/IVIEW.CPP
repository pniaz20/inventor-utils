// ivviewView.cpp : implementation of the CIvviewView class
//

#include "stdafx.h"
#include "ivview.h"

#include "iviewDoc.h"
#include "iView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvviewView

IMPLEMENT_DYNCREATE(CIvviewView, SoMfcView)

BEGIN_MESSAGE_MAP(CIvviewView, SoMfcView)
	//{{AFX_MSG_MAP(CIvviewView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIvviewView construction/destruction

CIvviewView::CIvviewView() : SoMfcView(RUNTIME_CLASS(SoMfcExaminerViewer))
{
	// TODO: add construction code here

}

CIvviewView::~CIvviewView()
{
}

BOOL CIvviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return SoMfcView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CIvviewView drawing


/////////////////////////////////////////////////////////////////////////////
// CIvviewView diagnostics

#ifdef _DEBUG
void CIvviewView::AssertValid() const
{
	SoMfcView::AssertValid();
}

void CIvviewView::Dump(CDumpContext& dc) const
{
	SoMfcView::Dump(dc);
}

CIvviewDoc* CIvviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIvviewDoc)));
	return (CIvviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIvviewView message handlers

