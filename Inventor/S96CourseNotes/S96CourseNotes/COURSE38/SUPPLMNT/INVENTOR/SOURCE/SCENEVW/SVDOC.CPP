// mfctedoc.cpp : implementation of the SceneViewerDoc class
//

#include "stdafx.h"
#include "SceneVw.h"
#include "SoSv.h"
#include /**/ <Inventor/nodes/SoWWWAnchor.h>
#include "SceneViewerDoc.h"
#include /**/ <Inventor/engines/SoElapsedTime.h>
#include /**/ <Inventor/nodes/SoRotationXYZ.h>
#include /**/ <Inventor/nodes/SoTexture2.h>
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SceneViewerDoc

IMPLEMENT_DYNCREATE(SceneViewerDoc, SoMfcDoc)

BEGIN_MESSAGE_MAP(SceneViewerDoc, SoMfcDoc)
	//{{AFX_MSG_MAP(SceneViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SceneViewerDoc construction/destruction

SceneViewerDoc::SceneViewerDoc()
{
   m_nWhichViewer = SV_VWR_EXAMINER;
}

SceneViewerDoc::~SceneViewerDoc()
{
}

void SceneViewerDoc::ViewerChange( int nWhichViewer )
{
	m_nWhichViewer = nWhichViewer;

	CString path = GetPathName();
	int length = path.GetLength();
	CString FileName;
	if( length == 0 )
	{
		FileName.LoadString( IDS_UNTITLED );
	}
	else
	{
		int index = path.ReverseFind('\\');
		++index;
		FileName = path.Right( length - index );
	}
	SetTitle( FileName.GetBuffer( 1 ) );
}

void SceneViewerDoc::SetTitle( LPCTSTR lpszTitle )
{
	int nStringID;
	if( !lpszTitle )
	   return;

	switch( m_nWhichViewer )
	{
	case 	SV_VWR_WALK:
			nStringID = IDS_WALK_TITLE;
	break;
	case    SV_VWR_PLANE:
			nStringID = IDS_PLANE_TITLE;
	break;
	case    SV_VWR_FLY:
			nStringID = IDS_FLY_TITLE;
	break;
	case    SV_VWR_EXAMINER:
			nStringID = IDS_EXAMINER_TITLE;
	break;
	default:
		return;
	break;
	}

	CString string;
	BOOL rtval = string.LoadString(nStringID);
	ASSERT( rtval );
	CString title = lpszTitle;
	CString separator = " - ";
	CString result = string + separator + title;
	SoMfcDoc::SetTitle( result );
}

BOOL SceneViewerDoc::OnNewDocument()
{
	if (!SoMfcDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
		  	  
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// SceneViewerDoc serialization

void SceneViewerDoc::Serialize(CArchive& ar)
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
// SceneViewerDoc diagnostics

#ifdef _DEBUG
void SceneViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}
  
void SceneViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SceneViewerDoc commands

BOOL SceneViewerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	static int count;

	if (!SoMfcDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	if (++count > 4) {
			MessageBox( GetActiveWindow(), 
				"Only 4 file open operations allowed in\n"
				"this demo version of IViewMdi.\n\n"
				"To obtain the release version of Open\n"
				"Inventor, contact Portable Graphics at\n"
				"512-719-8029.\n"
				"(e-mail: sales@portable.com)\n",
				"File Open Limit Exceeded!",
				MB_APPLMODAL | MB_ICONSTOP | MB_OK );
			return FALSE;
	}

	return TRUE;
}

BOOL SceneViewerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class

	return SoMfcDoc::OnSaveDocument(lpszPathName);
}

