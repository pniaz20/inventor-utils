// OleDemoDoc.cpp : implementation of the COleDemoDoc class
//

#include "stdafx.h"
#include "OleDemo.h"

#include "ODDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleDemoDoc

IMPLEMENT_DYNCREATE(COleDemoDoc, SoMfcOleSrvrDoc)

BEGIN_MESSAGE_MAP(COleDemoDoc, SoMfcOleSrvrDoc)
	//{{AFX_MSG_MAP(COleDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COleDemoDoc construction/destruction

COleDemoDoc::COleDemoDoc()
{
}

COleDemoDoc::~COleDemoDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// COleDemoDoc diagnostics

#ifdef _DEBUG
void COleDemoDoc::AssertValid() const
{
	SoMfcOleSrvrDoc::AssertValid();
}

void COleDemoDoc::Dump(CDumpContext& dc) const
{
	SoMfcOleSrvrDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COleDemoDoc commands

BOOL COleDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	static int count;
	
	if (!SoMfcOleSrvrDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	if (++count > 4) {
			MessageBox( GetActiveWindow(), 
				"Only 4 file open operations allowed in\n"
				"this demo version of OleDemo.\n\n"
				"To obtain the release version of Open\n"
				"Inventor, contact Portable Graphics at\n"
				"512-719-8029.\n"
				"(e-mail: sales@portable.com)\n",
				"File Open Limit Exceeded!",
				MB_APPLMODAL | MB_ICONSTOP | MB_OK );
			return FALSE;
	}
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
