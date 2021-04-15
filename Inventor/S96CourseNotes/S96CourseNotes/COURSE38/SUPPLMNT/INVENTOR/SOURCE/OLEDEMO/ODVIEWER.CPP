#include "stdafx.h"

#include <Inventor/nodes/SoSelection.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>

#include "ODViewer.h"


IMPLEMENT_DYNCREATE(COleDemoViewer, SoMfcExaminerViewer)


COleDemoViewer::COleDemoViewer() 
{
	m_pSelection = new SoSelection;
	m_pSelection->ref();

	m_pPrevScene = NULL;
	RedrawOnSelectionChange(m_pSelection);

	m_pHighlightRA = new SoBoxHighlightRenderAction;
	m_pHighlightRA->setVisible(TRUE); // highlight visible when no manip
	SetGLRenderAction(m_pHighlightRA);
}


COleDemoViewer::~COleDemoViewer()
{
  m_pSelection->deselectAll();

  delete m_pHighlightRA;
  m_pSelection->unref();
}


void COleDemoViewer::SetSceneGraph( SoNode *pNewScene )
{
	m_pSelection->deselectAll();

	if( pNewScene )
	  m_pSelection->addChild( pNewScene );
	
	SoMfcExaminerViewer::SetSceneGraph( m_pSelection );
	
	if( m_pPrevScene )
	{
		m_pSelection->removeChild( m_pPrevScene );
	}
	m_pPrevScene = (SoSeparator*)pNewScene;

}

