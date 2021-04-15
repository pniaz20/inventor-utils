// SceneViewerVw.h interface of the SceneView class
//
/////////////////////////////////////////////////////////////////////////////
#include /**/ <Inventor/mfc/SoMfcRenderArea.h>
#include "SoSV.h"

class CLightDialog;


class  SceneView : public SoSceneViewer
{

  public:
 	SceneView();

protected: // create from serialization only
	DECLARE_DYNCREATE(SceneView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SceneView)
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~SceneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
   SoMfcClipboardHelper *m_pClipBoard;

// Generated message map functions
protected:

	LONG OnLightGoodbye(UINT wParam, LONG lParam);
	//{{AFX_MSG(SceneView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnInventorCopy();
	afx_msg void OnInventorPaste();
	afx_msg void OnInventorEditAll();
	afx_msg void OnInventorEditParent();
	afx_msg void OnInventorHandlebox();
	afx_msg void OnInventorJack();
	afx_msg void OnInventorNoManips();
	afx_msg void OnInventorTabbox();
	afx_msg void OnInventorTransformer();
	afx_msg void OnInventorTrackball();
	afx_msg void OnInventorXfbox();
	afx_msg void OnInventorCenterball();
	afx_msg void OnEditColor();
	afx_msg void OnEditMaterial();
	afx_msg void OnEditLight();
	afx_msg void OnInventorExaminer();
	afx_msg void OnInventorFly();
	afx_msg void OnInventorWalk();
	afx_msg void OnInventorPlane();
	afx_msg void OnUpdateInventorNoManips(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorJack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorHandlebox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorCenterball(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorTabbox(CCmdUI* pCmdUI); 
	afx_msg void OnUpdateInventorTransformer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorTrackball(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorXfbox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditMaterial(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditXform(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorExaminer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorFly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorPlane(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInventorWalk(CCmdUI* pCmdUI);
	afx_msg void OnSelectionShift();
	afx_msg void OnUpdateSelectionShift(CCmdUI* pCmdUI);
	afx_msg void OnSelectionSingle();
	afx_msg void OnUpdateSelectionSingle(CCmdUI* pCmdUI);
	afx_msg void OnSelectionToggle();
	afx_msg void OnUpdateSelectionToggle(CCmdUI* pCmdUI);
	afx_msg void OnEditBackground();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
										    
	BOOL m_bShiftON;

private:

	SoSceneViewer *m_SV;
	CLightDialog *m_light_pDlg;


    // Paste callback - invoked when paste data transfer is complete
    void    	    	PasteDone(SoPathList *pathList);
    static void    		PasteDoneCB(void *userData, SoPathList *pathList);
};





/////////////////////////////////////////////////////////////////////////////
