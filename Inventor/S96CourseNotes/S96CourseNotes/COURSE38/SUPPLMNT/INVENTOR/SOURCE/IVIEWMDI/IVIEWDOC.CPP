// IViewdoc.cpp : implementation of the CIViewMdiDoc class
//

#include "stdafx.h"
#include "IViewMdi.h"

#include "IViewdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiDoc

IMPLEMENT_DYNCREATE(CIViewMdiDoc, SoMfcDoc)

BEGIN_MESSAGE_MAP(CIViewMdiDoc, SoMfcDoc)
	//{{AFX_MSG_MAP(CIViewMdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiDoc construction/destruction

CIViewMdiDoc::CIViewMdiDoc()
{

}

CIViewMdiDoc::~CIViewMdiDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CIViewMdiDoc serialization

void CIViewMdiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiDoc diagnostics

#ifdef _DEBUG
void CIViewMdiDoc::AssertValid() const
{
	SoMfcDoc::AssertValid();
}

void CIViewMdiDoc::Dump(CDumpContext& dc) const
{
	SoMfcDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIViewMdiDoc commands

