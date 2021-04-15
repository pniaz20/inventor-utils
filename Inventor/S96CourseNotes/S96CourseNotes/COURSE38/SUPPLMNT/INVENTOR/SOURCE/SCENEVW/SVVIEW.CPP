// mfctevw.cpp : implementation of the SceneView class
//

#include "stdafx.h"
#include "SceneVw.h"

#include "SVDoc.h"
#include "SVView.h"
#include "svDefMsg.h"
#include "lightdia.h"
#include /**/ <Inventor/mfc/viewers/SoMfcExamViewer.h>
#include /**/ <Inventor/mfc/SoMfcClipboardHelper.h>
#include /**/ <Inventor/actions/SoWriteAction.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SceneView

IMPLEMENT_DYNCREATE(SceneView, SoSceneViewer)

BEGIN_MESSAGE_MAP(SceneView, SoSceneViewer)
	ON_MESSAGE(WM_LIGHT_GOODBYE, OnLightGoodbye)
	//{{AFX_MSG_MAP(SceneView)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_COPY, OnInventorCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnInventorPaste)
	ON_COMMAND(ID_INVENTOR_EDIT_ALL, OnInventorEditAll)
	ON_COMMAND(ID_INVENTOR_EDIT_PARENT, OnInventorEditParent)
	ON_COMMAND(ID_INVENTOR_HANDLEBOX, OnInventorHandlebox)
	ON_COMMAND(ID_INVENTOR_JACK, OnInventorJack)
	ON_COMMAND(ID_INVENTOR_NO_MANIPS, OnInventorNoManips)
	ON_COMMAND(ID_INVENTOR_TABBOX, OnInventorTabbox) 
	ON_COMMAND(ID_INVENTOR_TRANSFORMER, OnInventorTransformer)
	ON_COMMAND(ID_INVENTOR_TRACKBALL, OnInventorTrackball)
	ON_COMMAND(ID_INVENTOR_XFBOX, OnInventorXfbox)
	ON_COMMAND(ID_INVENTOR_CENTERBALL, OnInventorCenterball)
	ON_COMMAND(INVENTOR_EDIT_COLOR, OnEditColor)
	ON_COMMAND(INVENTOR_EDIT_MATERIAL, OnEditMaterial)
	ON_COMMAND(INVENTOR_EDIT_LIGHT, OnEditLight)
	ON_COMMAND(IDC_INVENTOR_EXAMINER, OnInventorExaminer)
	ON_COMMAND(IDC_INVENTOR_FLY, OnInventorFly)
	ON_COMMAND(IDC_INVENTOR_WALK, OnInventorWalk)
	ON_COMMAND(IDC_INVENTOR_PLANE, OnInventorPlane)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_NO_MANIPS, OnUpdateInventorNoManips)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_JACK, OnUpdateInventorJack)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_HANDLEBOX, OnUpdateInventorHandlebox)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_CENTERBALL, OnUpdateInventorCenterball)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_TABBOX, OnUpdateInventorTabbox) 
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_TRANSFORMER, OnUpdateInventorTransformer)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_TRACKBALL, OnUpdateInventorTrackball)
	ON_UPDATE_COMMAND_UI(ID_INVENTOR_XFBOX, OnUpdateInventorXfbox)
	ON_UPDATE_COMMAND_UI(INVENTOR_EDIT_COLOR, OnUpdateEditColor)
	ON_UPDATE_COMMAND_UI(INVENTOR_EDIT_MATERIAL, OnUpdateEditMaterial)
	ON_UPDATE_COMMAND_UI(INVENTOR_EDIT_XFORM, OnUpdateEditXform)
	ON_UPDATE_COMMAND_UI(IDC_INVENTOR_EXAMINER, OnUpdateInventorExaminer)
	ON_UPDATE_COMMAND_UI(IDC_INVENTOR_FLY, OnUpdateInventorFly)
	ON_UPDATE_COMMAND_UI(IDC_INVENTOR_PLANE, OnUpdateInventorPlane)
	ON_UPDATE_COMMAND_UI(IDC_INVENTOR_WALK, OnUpdateInventorWalk)
	ON_COMMAND(ID_SELECTION_SHIFT, OnSelectionShift)
	ON_UPDATE_COMMAND_UI(ID_SELECTION_SHIFT, OnUpdateSelectionShift)
	ON_COMMAND(ID_SELECTION_SINGLE, OnSelectionSingle)
	ON_UPDATE_COMMAND_UI(ID_SELECTION_SINGLE, OnUpdateSelectionSingle)
	ON_COMMAND(ID_SELECTION_TOGGLE, OnSelectionToggle)
	ON_UPDATE_COMMAND_UI(ID_SELECTION_TOGGLE, OnUpdateSelectionToggle)
	ON_COMMAND(INVENTOR_EDIT_BACKGROUND, OnEditBackground)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SceneView construction/destruction

SceneView::SceneView()
{
	//m_SV = new SoSceneViewer;
	m_light_pDlg = new CLightDialog(this);
	m_pClipBoard = NULL;

	m_bShiftON = FALSE;
}

SceneView::~SceneView()
{
	delete m_light_pDlg;
	delete m_pClipBoard;
}
							  
/////////////////////////////////////////////////////////////////////////////
// SceneView drawing
/////////////////////////////////////////////////////////////////////////////
// SceneView diagnostics

#ifdef _DEBUG
void SceneView::AssertValid() const
{
	CView::AssertValid();
}

void SceneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SceneView message handlers

int SceneView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  	if (SoSceneViewer::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SceneViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	return 0;
}


LONG SceneView::OnLightGoodbye(UINT wParam, LONG lParam)
{
	// message received in response to xformedit dialog OK
	// and CANCEL buttons
	m_light_pDlg->DestroyWindow();
	return 0L;
}



void SceneView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    // first, detach manips from all selected objects
    DetachManipFromAll();
    
    // now, turn off the sel/desel callbacks.
    // we'll turn them on again after we've adjusted the m_pSelection
    m_pSelection->removeSelectionCallback( SoSceneViewer::SelectionCallback, this );
    m_pSelection->removeDeselectionCallback( SoSceneViewer::DeselectionCallback, this );
    
    // now deselect all, and build up a m_pSelection from the pasted paths
    m_pSelection->deselectAll();
	
	SoSceneViewer::OnUpdate(pSender, lHint, pHint);

	// and turn the sel/desel callbacks back on
    m_pSelection->addSelectionCallback( SoSceneViewer::SelectionCallback, this );
    m_pSelection->addDeselectionCallback( SoSceneViewer::DeselectionCallback, this );

}




void SceneView::OnInventorCopy( )
{
	BeginWaitCursor();

	if( !m_pClipBoard )
	{
	  m_pClipBoard = new SoMfcClipboardHelper( this );
    }

	RemoveManips();
	m_pClipBoard->Copy( (SoPathList *)m_pSelection->getList() );
 	RestoreManips();
   	
   	EndWaitCursor();

}

void SceneView::OnInventorPaste()
{
	BeginWaitCursor();

	if( !m_pClipBoard )
	{
	  m_pClipBoard = new SoMfcClipboardHelper( this );
    }
	m_pClipBoard->Paste(PasteDoneCB, this);

	EndWaitCursor();

}



////////////////////////////////////////////////////////////////////////
//
// Description:
//	Called after a paste operation has completed.
//
// Use: static, private
//
void
SceneView::PasteDoneCB(void *userData, SoPathList *pathList)
//
////////////////////////////////////////////////////////////////////////
{
    SceneView *sv = (SceneView *) userData;
    sv->PasteDone(pathList);
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
SceneView::PasteDone(SoPathList *pathList)
//
////////////////////////////////////////////////////////////////////////
{
    if (pathList->getLength() <= 0)
    	return;

    // first, detach manips from all selected objects
    DetachManipFromAll();
    
    // now, turn off the sel/desel callbacks.
    // we'll turn them on again after we've adjusted the m_pSelection
    m_pSelection->removeSelectionCallback( SoSceneViewer::SelectionCallback, this );
    m_pSelection->removeDeselectionCallback( SoSceneViewer::DeselectionCallback, this );
    
    // now deselect all, and build up a m_pSelection from the pasted paths
    m_pSelection->deselectAll();
    
    //get a pointer to the scene root, as maintained by the document
	SoSeparator *proot = ( (SoMfcDoc *)GetDocument())->GetScene();


    // Add every path in the path list as a child under m_pSelection.
    // Then select each of these paths.
    for (int i = 0; i < pathList->getLength(); i++) {
    
    	// if the head of the path is a m_pSelection node, then don't
	// paste the head - rather, paste all of its children. 
	// this makes sure we don't have more than 1 m_pSelection node.
	// While we're adding the paths as children, select each path.
    	SoPath *p = (*pathList)[i];
	SoNode *head = p->getHead();
	SoPath *selpath;
	if (head->isOfType(SoSelection::getClassTypeId())) {
	    for (int j = 0; j < ((SoSelection *)head)->getNumChildren(); j++) {
	    	proot->addChild(((SoSelection *)head)->getChild(j));
		
		// create a path from m_pSelection to this child
		// and select the path.
	    selpath = new SoPath(m_pSelection);
		selpath->ref();
		selpath->append( m_pSelection->findChild( proot ) );
        
		selpath->append(proot->getNumChildren() - 1);
		m_pSelection->select(selpath);
		selpath->unref();
	    }
	}
	else {
	    // not a m_pSelection node, so just add it.
	    proot->addChild(p->getHead());
	    
	    // create a path from m_pSelection to this child
	    // and select the path.
	    selpath = new SoPath(m_pSelection);
		selpath->ref();
		selpath->append( m_pSelection->findChild( proot ) );
        
	    selpath->append(proot->getNumChildren() - 1);
	    m_pSelection->select(selpath);
		selpath->unref();
	}
    }
    
    // now add manips to all the selected objects
    AttachManipToAll(m_curManip);
    
    // and turn the sel/desel callbacks back on
    m_pSelection->addSelectionCallback( SoSceneViewer::SelectionCallback, this );
    m_pSelection->addDeselectionCallback( SoSceneViewer::DeselectionCallback, this );
    

    delete pathList;
}



void SceneView::OnInventorEditAll() 
{
	OnEditAll();
}

void SceneView::OnInventorEditParent() 
{
	OnEditParent();
}



void SceneView::OnInventorTabbox() 
{
	SoSceneViewer::OnInventorTabbox();
	
}

void SceneView::OnInventorTransformer() 
{
	SoSceneViewer::OnInventorTransformer();
}

void SceneView::OnInventorTrackball() 
{
	SoSceneViewer::OnInventorTrackball();
	
}

void SceneView::OnInventorXfbox() 
{
	SoSceneViewer::OnInventorXfbox();
	
}

void SceneView::OnInventorJack() 
{
	SoSceneViewer::OnInventorJack();
	
}

void SceneView::OnInventorHandlebox() 
{
	SoSceneViewer::OnInventorHandlebox();
	
}

void SceneView::OnInventorCenterball() 
{
	SoSceneViewer::OnInventorCenterball();
	
}

void SceneView::OnInventorNoManips() 
{
	SoSceneViewer::OnInventorNoManips();
	
}


void SceneView::OnEditColor() 
{

	CreateColorEditor();
}

void SceneView::OnEditMaterial() 
{
    CreateMaterialEditor();
}

void SceneView::OnEditLight() 
{
	if (m_light_pDlg->GetSafeHwnd() == 0) {
		m_light_pDlg->Create();
	}
	
}


void SceneView::OnInventorExaminer() 
{
	SoSceneViewer::OnInventorExaminer();
	
}

void SceneView::OnInventorFly() 
{
	SoSceneViewer::OnInventorFly();
	
}

void SceneView::OnInventorWalk()
{
	SoSceneViewer::OnInventorWalk();
}

void SceneView::OnInventorPlane()
{
	SoSceneViewer::OnInventorPlane();
}

void SceneView::OnUpdateInventorNoManips(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_NONE);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}

void SceneView::OnUpdateInventorJack(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_JACK);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}

void SceneView::OnUpdateInventorHandlebox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_HANDLEBOX);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}

void SceneView::OnUpdateInventorCenterball(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_CENTERBALL);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}

void SceneView::OnUpdateInventorTabbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_TABBOX);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}
void SceneView::OnUpdateInventorTransformer(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_TRANSFORMER);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}

void SceneView::OnUpdateInventorTrackball(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_TRACKBALL);
	pCmdUI->Enable(SoSceneViewer::IsSelection());
	
}

void SceneView::OnUpdateInventorXfbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(SoSceneViewer::GetCurrentManip() == SV_XFBOX);
	pCmdUI->Enable(SoSceneViewer::IsSelection());

}

void SceneView::OnUpdateEditColor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(SoSceneViewer::IsSelection());

}

void SceneView::OnUpdateEditMaterial(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(SoSceneViewer::IsSelection());

}													   

void SceneView::OnUpdateEditXform(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(SoSceneViewer::IsSelection());

}

void SceneView::OnUpdateInventorExaminer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::m_whichViewer == SV_VWR_EXAMINER);	
}

void SceneView::OnUpdateInventorFly(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::m_whichViewer == SV_VWR_FLY);
}

void SceneView::OnUpdateInventorPlane(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::m_whichViewer == SV_VWR_PLANE);
}

void SceneView::OnUpdateInventorWalk(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::m_whichViewer == SV_VWR_WALK);
}

void SceneView::OnSelectionShift() 
{
	SoSceneViewer::SetSelectionPolicy(SV_SEL_SHIFT_SELECT);
}

void SceneView::OnUpdateSelectionShift(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::GetSelectionPolicy() == SV_SEL_SHIFT_SELECT);

}

void SceneView::OnSelectionSingle() 
{
	SoSceneViewer::SetSelectionPolicy(SV_SEL_SINGLE_SELECT);

}

void SceneView::OnUpdateSelectionSingle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::GetSelectionPolicy() == SV_SEL_SINGLE_SELECT);

}

void SceneView::OnSelectionToggle() 
{
	SoSceneViewer::SetSelectionPolicy(SV_SEL_TOGGLE_SELECT);
	
}

void SceneView::OnUpdateSelectionToggle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(SoSceneViewer::GetSelectionPolicy() == SV_SEL_TOGGLE_SELECT);

}

void SceneView::OnEditBackground() 
{
	SoSceneViewer::EditBackgroundColor();
}
