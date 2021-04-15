// dropDoc.cpp : implementation of the CDropDoc class
//

#include "stdafx.h"
#include "drop.h"

#include "dropDoc.h"
#include "TsField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropDoc

IMPLEMENT_DYNCREATE(CDropDoc, SoMfcDoc)

BEGIN_MESSAGE_MAP(CDropDoc, SoMfcDoc)
	//{{AFX_MSG_MAP(CDropDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropDoc construction/destruction

CDropDoc::CDropDoc()
{
	// TODO: add one-time construction code here
	m_pwndStatusBar = NULL;
}

CDropDoc::~CDropDoc()
{
	delete theField;
}

BOOL CDropDoc::OnNewDocument()
{
	if (!SoMfcDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here	  
	SetTitle("Level #1");
	// (SDI documents will reuse this document)
	
	return TRUE;
}

void CDropDoc::InitGame(SoMfcViewer *viewer)
{
	theField = new TsField(viewer, this);
	theField->initGame();
}

/////////////////////////////////////////////////////////////////////////////
// CDropDoc serialization

void CDropDoc::Serialize(CArchive& ar)
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
// CDropDoc diagnostics

#ifdef _DEBUG
void CDropDoc::AssertValid() const
{
	SoMfcDoc::AssertValid();
}

void CDropDoc::Dump(CDumpContext& dc) const
{
	SoMfcDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDropDoc commands


