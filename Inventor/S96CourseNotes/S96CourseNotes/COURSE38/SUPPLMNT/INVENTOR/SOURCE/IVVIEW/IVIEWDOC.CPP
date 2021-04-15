// ivviewDoc.cpp : implementation of the CIvviewDoc class
//

#include "stdafx.h"
#include "ivview.h"

#include "iviewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvviewDoc

IMPLEMENT_DYNCREATE(CIvviewDoc, SoMfcDoc)

BEGIN_MESSAGE_MAP(CIvviewDoc, SoMfcDoc)
	//{{AFX_MSG_MAP(CIvviewDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIvviewDoc construction/destruction

CIvviewDoc::CIvviewDoc()
{
	// TODO: add one-time construction code here

}

CIvviewDoc::~CIvviewDoc()
{
}

BOOL CIvviewDoc::OnNewDocument()
{
	if (!SoMfcDoc::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	LPTSTR cmdLine = GetCommandLine();
	SetTitle(cmdLine);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CIvviewDoc serialization

void CIvviewDoc::Serialize(CArchive& ar)
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
// CIvviewDoc diagnostics

#ifdef _DEBUG
void CIvviewDoc::AssertValid() const
{
	SoMfcDoc::AssertValid();
}

void CIvviewDoc::Dump(CDumpContext& dc) const
{
	SoMfcDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIvviewDoc commands
#if 0
void CIvviewDoc::OnAppExit() 
{
	// TODO: Add your command handler code here
	
}
#endif
