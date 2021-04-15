// IViewvw.cpp : implementation of the CIViewMdiView class
//

#include "stdafx.h"
#include "IViewMdi.h"

#include "IViewdoc.h"
#include "IViewvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiView

IMPLEMENT_DYNCREATE(CIViewMdiView, SoMfcView)

BEGIN_MESSAGE_MAP(CIViewMdiView, SoMfcView)
	//{{AFX_MSG_MAP(CIViewMdiView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, SoMfcView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, SoMfcView::OnFilePrintPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiView construction/destruction

CIViewMdiView::CIViewMdiView()
{
	// TODO: add construction code here

}

CIViewMdiView::~CIViewMdiView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CIViewMdiView printing

BOOL CIViewMdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIViewMdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIViewMdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiView diagnostics

#ifdef _DEBUG
void CIViewMdiView::AssertValid() const
{
	SoMfcView::AssertValid();
}

void CIViewMdiView::Dump(CDumpContext& dc) const
{
	SoMfcView::Dump(dc);
}

CIViewMdiDoc* CIViewMdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIViewMdiDoc)));
	return (CIViewMdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiView message handlers
