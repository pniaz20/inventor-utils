// OleDemoView.cpp : implementation of the COleDemoView class
//

#include "stdafx.h"
#include "OleDemo.h"

#include "ODDoc.h"
#include "ODView.h"

#include <Inventor/nodes/SoSelection.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>

#include "ODViewer.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleDemoView

IMPLEMENT_DYNCREATE(COleDemoView, SoMfcView)

BEGIN_MESSAGE_MAP(COleDemoView, SoMfcView)
	//{{AFX_MSG_MAP(COleDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EDIT_COPY, OnInventorCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnInventorPaste)
	ON_WM_CREATE()

	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, SoMfcView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, SoMfcView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, SoMfcView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COleDemoView construction/destruction

COleDemoView::COleDemoView() : SoMfcView( RUNTIME_CLASS( COleDemoViewer ) )
{
	m_pClipBoard = NULL;
}

COleDemoView::~COleDemoView()
{
	delete m_pClipBoard;
}


int COleDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int rtval =	  SoMfcView::OnCreate( lpCreateStruct );
	if( 0 == rtval )
	{
		// register drop target
		m_dropTarget.Register(this);
	}
	return rtval;
}


void COleDemoView::OnInventorCopy( )
{
	SoSelection *pSelection = ((COleDemoViewer*)GetExaminerViewerPtr())->GetSelectionNode();
	ASSERT( pSelection );
	COleDemoSrvrItem  *pItem; 

	SoPathList *pList = (SoPathList *)pSelection->getList();
	
	if( pList )
	{
		BeginWaitCursor();			 
		pItem = new COleDemoSrvrItem( this, pList );
		pItem->CopyToClipboard(TRUE);
   		EndWaitCursor();
	}

}

void COleDemoView::OnInventorPaste()
{
	BeginWaitCursor();

	COleDataObject clipboardData;
	clipboardData.AttachClipboard();
	DoPasteNative(&clipboardData);

	EndWaitCursor();
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//	Called after a paste operation has completed, this adds the
// pasted data to our scene graph.
//
// Use: private
//
void
COleDemoView::PasteDone(SoPathList *pathList)
//
////////////////////////////////////////////////////////////////////////
{
    if (pathList->getLength() <= 0)
    	return;

    SoSelection *pSelection = ((COleDemoViewer*)GetExaminerViewerPtr())->GetSelectionNode();
	ASSERT( pSelection );

    // now deselect all, and build up a pSelection from the pasted paths
    pSelection->deselectAll();
    
    //get a pointer to the scene root, as maintained by the document
	SoSeparator *proot = ( (SoMfcOleSrvrDoc *)GetDocument())->GetScene();


    // Add every path in the path list as a child under pSelection.
    // Then select each of these paths.
    for (int i = 0; i < pathList->getLength(); i++) {
    
    	// if the head of the path is a pSelection node, then don't
	// paste the head - rather, paste all of its children. 
	// this makes sure we don't have more than 1 pSelection node.
	// While we're adding the paths as children, select each path.
    	SoPath *p = (*pathList)[i];
	SoNode *head = p->getHead();
	SoPath *selpath;
	if (head->isOfType(SoSelection::getClassTypeId())) {
	    for (int j = 0; j < ((SoSelection *)head)->getNumChildren(); j++) {
	    	proot->addChild(((SoSelection *)head)->getChild(j));
		
		// create a path from pSelection to this child
		// and select the path.
	    selpath = new SoPath(pSelection);
		selpath->ref();
		selpath->append( pSelection->findChild( proot ) );
        
		selpath->append(proot->getNumChildren() - 1);
		pSelection->select(selpath);
		selpath->unref();
	    }
	}
	else {
	    // not a pSelection node, so just add it.
	    proot->addChild(p->getHead());
	    
	    // create a path from pSelection to this child
	    // and select the path.
	    selpath = new SoPath(pSelection);
		selpath->ref();
		selpath->append( pSelection->findChild( proot ) );
        
	    selpath->append(proot->getNumChildren() - 1);
	    pSelection->select(selpath);
		selpath->unref();
	}
    }
    
    delete pathList;
}



DROPEFFECT COleDemoView::OnDragEnter(COleDataObject* pDataObject,
	DWORD grfKeyState, CPoint point)
{
	ASSERT(m_prevDropEffect == DROPEFFECT_NONE);
	return OnDragOver(pDataObject, grfKeyState, point);
}


DROPEFFECT COleDemoView::OnDragOver(COleDataObject* pDataObject,
	DWORD grfKeyState, CPoint point)
{
	DROPEFFECT dropEffect = DROPEFFECT_NONE;
	SoMfcCommonFrame *pFrame = GetCommonFrame();
	ASSERT( pFrame );

	if (pDataObject->IsDataAvailable(pFrame->GetInventorClipboardFormat() ) )
	{
		dropEffect = DROPEFFECT_COPY;
	}
	m_prevDropEffect = dropEffect;
	return dropEffect;
}

void COleDemoView::OnDragLeave()
{
	m_prevDropEffect = DROPEFFECT_NONE;
}



BOOL COleDemoView::OnDrop(COleDataObject* pDataObject, DROPEFFECT, CPoint)
{
	ASSERT_VALID(this);
	OnDragLeave();
	DoPasteNative(pDataObject);
	return TRUE;
}


void COleDemoView::DoPasteNative(COleDataObject *pDataObject)
{
	SoMfcCommonFrame *pFrame = GetCommonFrame();
	ASSERT( pFrame );

	// get file refering to clipboard data
	CFile *pFile = pDataObject->GetFileData(pFrame->GetInventorClipboardFormat() );
	if (pFile == NULL)
	{
		return;
	}

	CDocument *pDoc = GetDocument();
	if( pDoc->IsKindOf( RUNTIME_CLASS( SoMfcOleSrvrDoc ) ) )
	{
		SoMfcOleSrvrDoc *pIvDoc = (SoMfcOleSrvrDoc*) pDoc;

		// connect the file to the archive and read the contents
		CArchive ar(pFile, CArchive::load);
		ar.m_pDocument = pIvDoc; // for COleClientItem serialize

		SoPathList *pList = pIvDoc->GetCommonDoc()->ImportPathList(ar);
		ar.Close();

		PasteDone( pList );
	}
	delete pFile;

}



BOOL COleDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return SoMfcView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// COleDemoView printing

BOOL COleDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COleDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COleDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void COleDemoView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// COleDemoView diagnostics

#ifdef _DEBUG
void COleDemoView::AssertValid() const
{
	SoMfcView::AssertValid();
}

void COleDemoView::Dump(CDumpContext& dc) const
{
	SoMfcView::Dump(dc);
}

COleDemoDoc* COleDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COleDemoDoc)));
	return (COleDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COleDemoView message handlers
