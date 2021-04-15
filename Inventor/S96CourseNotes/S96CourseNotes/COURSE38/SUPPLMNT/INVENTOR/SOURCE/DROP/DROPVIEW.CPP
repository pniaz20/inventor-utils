// dropView.cpp : implementation of the CDropView class
//

#include "stdafx.h"
#include "drop.h"

#include "dropDoc.h"
#include "dropView.h"
#include "MainFrm.h"
#include <math.h>
 
enum ViewerModes {
    IDLE_MODE, 
    TRANS_MODE, 
    SEEK_MODE, 
    ROT_MODE
};  // PGI_IV ---- delete the last comma

#define TS_XROT_FACTOR 3.14
#define TS_YROT_FACTOR 3.14
#define TS_YTRANS_FACTOR 16.0


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropView

IMPLEMENT_DYNCREATE(CDropView, SoMfcView)

BEGIN_MESSAGE_MAP(CDropView, SoMfcView)
	//{{AFX_MSG_MAP(CDropView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropView construction/destruction

CDropView::CDropView():SoMfcView(RUNTIME_CLASS(SoMfcViewer))
{
	// TODO: add construction code here
	mode = IDLE_MODE;
    createdCursors = FALSE;
}

CDropView::~CDropView()
{
}

BOOL CDropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	 
	return SoMfcView::PreCreateWindow(cs);
}

void CDropView::NewSize(int x, int y)
{
	windowSize.setValue(x, y);
}

/////////////////////////////////////////////////////////////////////////////
// CDropView diagnostics

#ifdef _DEBUG
void CDropView::AssertValid() const
{
	SoMfcView::AssertValid();
}

void CDropView::Dump(CDumpContext& dc) const
{
	SoMfcView::Dump(dc);
}

CDropDoc* CDropView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDropDoc)));
	return (CDropDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDropView message handlers

void CDropView::OnSize(UINT nType, int cx, int cy) 
{
	SoMfcView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	windowSize.setValue(cx, cy);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Switches to the specified viewer mode. The correct
//    cursor is also set on the window.
//
// Use: private

void
CDropView::switchMode(int newMode)

//
////////////////////////////////////////////////////////////////////////
{
	SoMfcViewer *viewer = GetViewerPtr();
	ASSERT(viewer);
	SoCamera *camera = viewer->GetCamera();
#if 0
	// jlr - TBD
    // needed to define new cursors
    Widget w = SoXtRenderArea::getWidget();
    Display *display = (w != NULL) ? XtDisplay(w) : NULL;
    Window window = (w != NULL) ? XtWindow(w) : 0;
    if (!createdCursors && window != 0)
	defineCursors();
#endif    
    // switch to new viewer mode
    mode = newMode;
    switch (mode) {
	case IDLE_MODE:
		TRACE("IDLE_MODE\n");
	    // if (window != 0)
		// XDefineCursor(display, window, vwrCursor);
	    break;
	    
	case TRANS_MODE:
	    {
		TRACE("TRANS_MODE\n");
		// Figure out the focal plane
		SbMatrix mx;
		mx = camera->orientation.getValue();
		SbVec3f forward(-mx[2][0], -mx[2][1], -mx[2][2]);
		SbVec3f fp = camera->position.getValue() + 
		    forward * camera->focalDistance.getValue();
		focalplane = SbPlane(forward, fp);
		
		// map mouse position onto the viewing plane
		SbViewVolume cameraVolume;
		SbLine line;
		cameraVolume = camera->getViewVolume();
		cameraVolume.projectPointToLine(
		    SbVec2f( locator[0] / float(windowSize[0]), 
			locator[1] / float(windowSize[1])), line);
		focalplane.intersect(line, locator3D);
	    }
	    // if (window != 0)
		// XDefineCursor(display, window, vwrCursor);
	    break;
    }
}
 ////////////////////////////////////////////////////////////////////////
//
// Description:
//    Moves the camera along the vertical Y axis as the user moves
//    the mouse up and down.
//
// Use: private

void
CDropView::translateCamera()

//
////////////////////////////////////////////////////////////////////////
{
	SoMfcViewer *viewer = GetViewerPtr();
	ASSERT(viewer);
	SoCamera *camera =  viewer->GetCamera();
    if (camera == NULL)
	return;
    
    SbVec2f delta2D( (movement[0]-locator[0]) / float(windowSize[0]), 
                     (movement[1]-locator[1]) / float(windowSize[1]) );

    // map vertical mouse motion into a Y translation in world space.
    SbVec3f  delta3D;
    delta3D[0] = 0.0;
    delta3D[1] = (delta2D[0] + delta2D[1]) * TS_YTRANS_FACTOR;
    delta3D[2] = 0.0;

    camera->position = camera->position.getValue() + delta3D;
}


////////////////////////////////////////////////////////////////////////
//
// Description:
//    Revolves the camera around its focal point
//    to follow the new mouse location.  Rotations are about
//    the X and Y axes only.
//
// Use: private

void
CDropView::rotateCamera()
//
////////////////////////////////////////////////////////////////////////
{
	SoMfcViewer *viewer = GetViewerPtr();
	ASSERT(viewer);
	SoCamera *camera =  viewer->GetCamera();

    if (camera == NULL)
        return;

    SbVec2f newLocator( (movement[0]-locator[0]) / float(windowSize[0]), 
	(movement[1]-locator[1]) / float(windowSize[1]) );
    
    // figure out the new rotation.
    SbRotation xRot( SbVec3f(-1.0, 0.0, 0.0), newLocator[1] * TS_XROT_FACTOR );
    SbRotation yRot( SbVec3f(0.0, -1.0, 0.0), newLocator[0] * TS_YROT_FACTOR );
    SbRotation rot;

    // get center of rotation
    SbRotation camRot = camera->orientation.getValue();
    float radius = camera->focalDistance.getValue();
    SbMatrix mx;
    mx = camRot;
    SbVec3f forward( -mx[2][0], -mx[2][1], -mx[2][2]);
    SbVec3f center = camera->position.getValue()
        + radius * forward;

    // apply new rotation to the camera
    camRot = xRot * camRot * yRot;
    camera->orientation = camRot;

    // reposition camera to look at pt of interest
    mx = camRot;
    forward.setValue( -mx[2][0], -mx[2][1], -mx[2][2]);
    camera->position = center - radius * forward;

    movement[0] = locator[0];
    movement[1] = locator[1];
}



void CDropView::OnInitialUpdate() 
{
	SoMfcView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SoMfcViewer *viewer = GetViewerPtr();
	SoDirectionalLight *dirLgt = viewer->GetHeadlight();
    dirLgt->intensity = 1.0;

	CDropDoc *doc = GetDocument();
	ASSERT(doc);
	
	doc->InitGame(viewer);
	
}

void CDropView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SoMfcViewer *viewer = GetViewerPtr();
	locator[0] = windowSize[0] - point.x;
	locator[1] = windowSize[1] - point.y;
#if 0
	// jlr - can't access this since it is protected -- TR?
	if (mode == IDLE_MODE) 
		viewer->InteractiveCountInc();
#endif
    switchMode(ROT_MODE);

	SoMfcView::OnLButtonDown(nFlags, point);
}

void CDropView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SoMfcViewer *viewer = GetViewerPtr();
	if (mode == ROT_MODE) {
	    switchMode(IDLE_MODE);
	   // jlr viewer->InteractiveCountDec();
    }

	SoMfcView::OnLButtonUp(nFlags, point);
}

void CDropView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	 movement[0] = locator[0];
     movement[1] = locator[1];

   	 locator[0] = windowSize[0] - point.x;
	 locator[1] = windowSize[1] - point.y;
	 if (mode == TRANS_MODE)
		translateCamera();
	 else if (mode == ROT_MODE)
		rotateCamera();

	SoMfcView::OnMouseMove(nFlags, point);
}

void CDropView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SoMfcViewer *viewer = GetViewerPtr();
	ASSERT(viewer);
	// if (mode == IDLE_MODE) 
	// jlr	viewer->InteractiveCountInc();
    switchMode(TRANS_MODE);

	SoMfcView::OnRButtonDown(nFlags, point);
}

void CDropView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SoMfcViewer *viewer = GetViewerPtr();
	ASSERT(viewer);

	if (mode == TRANS_MODE) {
	    switchMode(IDLE_MODE);
		  //  viewer->InteractiveCountDec();
    } else {
		switchMode(ROT_MODE);
    }

	SoMfcView::OnRButtonUp(nFlags, point);
}

void CDropView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	 
	SoMfcView::OnKeyDown(nChar, nRepCnt, nFlags);
}
