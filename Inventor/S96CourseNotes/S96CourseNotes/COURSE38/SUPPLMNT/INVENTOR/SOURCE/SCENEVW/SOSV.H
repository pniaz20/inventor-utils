// SoSceneViewer.h : interface of the SoSceneViewer class
//
/////////////////////////////////////////////////////////////////////////////

#include /**/ <Inventor/mfc/SoMfcView.h>
#include "manipLst.h"
#include /**/ <Inventor/mfc/SoMfcColorEditor.h>
#include /**/ <Inventor/mfc/SoMfcMaterialEditor.h>
#include /**/ <Inventor/mfc/SoMfcDirectionalLightEditor.h>

#include /**/ <Inventor/SoPickedPoint.h>
#include /**/ <Inventor/draggers/SoDirectionalLightDragger.h>
#include /**/ <Inventor/draggers/SoTabBoxDragger.h>
#include /**/ <Inventor/manips/SoCenterballManip.h>
#include /**/ <Inventor/manips/SoDirectionalLightManip.h>
#include /**/ <Inventor/manips/SoHandleBoxManip.h>
#include /**/ <Inventor/manips/SoJackManip.h>
#include /**/ <Inventor/manips/SoPointLightManip.h>
#include /**/ <Inventor/manips/SoSpotLightManip.h>
#include /**/ <Inventor/manips/SoTabBoxManip.h>
#include /**/ <Inventor/manips/SoTransformerManip.h>
#include /**/ <Inventor/manips/SoTrackballManip.h>
#include /**/ <Inventor/manips/SoTransformBoxManip.h>
#include /**/ <Inventor/nodes/SoSwitch.h>
#include /**/ <Inventor/actions/SoBoxHighlightRenderAction.h>
#include /**/ <Inventor/actions/SoGetBoundingBoxAction.h>
#include /**/ <Inventor/actions/SoGetMatrixAction.h>
#include /**/ <Inventor/actions/SoSearchAction.h>
#include /**/ <Inventor/actions/SoCallbackAction.h>
#include /**/ <Inventor/nodes/SoShape.h>
#include /**/ <Inventor/nodes/SoTranslation.h>
#include /**/ <Inventor/nodes/SoLabel.h>
#include /**/ <Inventor/nodes/SoEnvironment.h>

class	SvManipList;
class	SoMfcDirectionalLightEditor;
class SoSceneViewer;
class SceneViewerDoc;

#include "lightdata.h"

enum SvEViewer {
    SV_VWR_EXAMINER = 0, 
    SV_VWR_FLY, 
    SV_VWR_WALK, 
    SV_VWR_PLANE
};

enum SvESelection {
	SV_SEL_SINGLE_SELECT, 
    SV_SEL_TOGGLE_SELECT, 
    SV_SEL_SHIFT_SELECT
}; 


enum SvEManipMode {
    SV_NONE,                         // None
	SV_TRANSFORMER,
    SV_TRACKBALL,                    // Trackball manip
    SV_HANDLEBOX,                    // Handlebox manip
    SV_JACK,                         // Jack manip
    SV_CENTERBALL,                   // Centerball manip
    SV_XFBOX,                        // TransformBox manip
    SV_TABBOX                        // TabBox manip
};


// class popupDialog;

class  SoSceneViewer : public SoMfcView
{
protected: 
	DECLARE_DYNAMIC(SoSceneViewer)

// Attributes

public:

public:

	SoSceneViewer::SoSceneViewer();
	SoSceneViewer::~SoSceneViewer();
	SceneViewerDoc* GetDocument();

   	void OnLightingSpotlight();
   	void OnLightingDirectlight();
   	void OnLightingPointlight();

   	SoMfcViewer * m_pCurrentViewer;

	SbBool IsSelection()		{ return(m_pSelection->getNumSelected() != 0) ; }
	SvEManipMode GetCurrentManip()  { return(m_curManip);	}
	SbBool IsViewing() { return(GetViewerPtr()->IsViewing()); }
	SvEViewer m_whichViewer;	// current viewer ID

	void SetSelectionPolicy(SvESelection);
	SvESelection GetSelectionPolicy() { return((SvESelection)m_pSelection->policy.getValue()); }

	void CreateColorEditor();
	void CreateMaterialEditor();
    void EditLightColor(SvLightData *data);
	void EditBackgroundColor();

	void SoSceneViewer::CreateLightsCameraEnvironment();

	//
    // Camera operation routines
    //
	void	ViewAll()	    
		    { if (m_pCurrentViewer != NULL) m_pCurrentViewer->ViewAll(); }
    void       	ViewSelection();
    void	SaveHomePosition()  
		    { if (m_pCurrentViewer != NULL) m_pCurrentViewer->SaveHomePosition(); }
    void    	SetCamera(SoCamera *cam) 
		    { if (m_pCurrentViewer != NULL) m_pCurrentViewer->SetCamera(cam); }
    // NOTE: because the camera may be changed dynamically (switch between ortho
    // and perspective), the user shouldn't cache the camera.
    SoCamera	*GetCamera()	    
		    { return (m_pCurrentViewer) ? m_pCurrentViewer->GetCamera() : NULL; }
    
    
    // Show/hide headlight (default on) and get to the headlight node.
    void    	    	SetHeadlight(SbBool bOnOrOff)	
		    { if (m_pCurrentViewer != NULL) m_pCurrentViewer->SetHeadlight(bOnOrOff); }
    SbBool  	    	IsHeadlight()	    
		    { return m_pCurrentViewer != NULL ? m_pCurrentViewer->IsHeadlight() : FALSE; }
    SoDirectionalLight	*GetHeadlight()	    
		    { return m_pCurrentViewer != NULL ? m_pCurrentViewer->GetHeadlight() : NULL; }
    
	void		TurnLightOnOff(SvLightData *data, SbBool flag);
    void		EditLight(SvLightData *data, SbBool flag);
	void		RemoveLight(SvLightData *);

	SbPList		m_lightDataList;
    SvLightData		    *m_pHeadlightData;

protected:
    // Temporarily remove manips for writing, printing, copying, etc.
    // and restore later
    void    RemoveManips();
    void    RestoreManips();
	
	SoSelection *m_pSelection;

	SoSeparator *m_pSv_sceneGraph;
	SoSeparator *m_pUserGraph;
	SoGroup 	*m_pLightGroup;
	SoGroup     *m_pLightsCameraEnvironment;
	SoEnvironment *m_pEnvironment;
	SoLabel       *m_pEnvLabel;

	// viewers
    void SwitchToViewer(SvEViewer newViewer);
	SoMfcViewer *m_pViewerList[4]; // list of viewers	 

	// Editors
	SoMaterial     	*FindMaterialForAttach( const SoPath *target );
	// callback used by Accum state action created by findMaterialForAttach
    static SoCallbackAction::Response FindMtlPreTailCB(void *data, 
					    SoCallbackAction *accum,
					    const SoNode *);
    // Editor closing callback functions
	static void OnColorEditorCloseCB( void * pData, const SoMfcColorEditor* pEditor)
                                 { ((SoSceneViewer*)pData)->m_pColorEditor = NULL ; }
	static void OnMaterialEditorCloseCB(void * pData, const SoMfcMaterialEditor* pEditor )
                                 { ((SoSceneViewer*)pData)->m_pMaterialEditor = NULL ; }
    static void  OnHeadLightCloseCB( void * pData, const SoMfcDirectionalLightEditor *pEditor )
                                  { ((SoSceneViewer*)pData)->m_pHeadlightEditor = NULL ;}

    SoMfcDirectionalLightEditor *m_pHeadlightEditor;
    SoMfcColorEditor    *m_pColorEditor ;
    SoMfcMaterialEditor *m_pMaterialEditor ;

		// Selection highlight
    SoBoxHighlightRenderAction *m_pHighlightRA;

	// Manipulators
	SvEManipMode m_curManip;
    SbBool       m_bCurManipReplaces;
	SvManipList	 *m_pManiplist;	// list of selection/manip/xfPath triplets.


	// replaces manips with the given type for all selected objects.
    void    ReplaceAllManips( SvEManipMode manipType );

    // attaches a manipulator
    void    AttachManip( SvEManipMode manipType, SoPath *p );
    void    AttachManipToAll( SvEManipMode manipType );

    // detaches a manipulator
    void    DetachManip( SoPath *p );
    void    DetachManipFromAll();


	// Callback to adjust size of scale tabs. Used only for SoTabBoxManip
    // Added to viewer as a finishCallback.
    static void AdjustScaleTabSizeCB( void *, SoMfcViewer *);

	SoPath     		*FindTransformForAttach( const SoPath * target );

	//
    // Lighting
    //
    
    void		AddLight(SoLight *light);
    SvLightData		*AddLightEntry(SoLight *light, SoSwitch *lightSwitch);
    void		AddLightMenuEntry(SvLightData *);
    
    // vars to make the light manips all the same size
    void		CalculateLightManipSize();
	float		m_fLightManipSize;
    SbBool		m_bCalculatedLightManipSize;

    
    // temporary remove/add the light manip geometry of the attached manips
    // (used for file writting and printing)
    void		RemoveAttachedLightManipGeometry();
    void		AddAttachedLightManipGeometry();
    
    // Background Color 
	SbColor m_backgroundColor;
	SoMfcColorEditor * m_pBackgroundColorEditor;
	static void  BackgroundColorEditorCB( void *, const SbColor * );
    static void  BackgroundColorEditorCloseCB( void *, const SoMfcColorEditor * );


    //
    // Selection
    //
    // manages changes in the selection.
    static void 	DeselectionCallback(void *userData, SoPath *obj);
    static void 	SelectionCallback(void *userData, SoPath *obj);
    static SoPath *	PickFilterCB(void *userData, const SoPickedPoint *pick);

	//
    // Convenience routines
    //
    static SbBool    IsAffectedByTransform( SoNode *node );
    static SbBool    IsAffectedByMaterial( SoNode *node );
    static SbBool    IsAffectedByTexture( SoNode *node );



protected:	  

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);


	void OnEditParent();
	void OnEditAll();
	void OnInventorTransformer();
	void OnInventorTrackball();
	void OnInventorTabbox();
	void OnInventorXfbox();
	void OnInventorJack();
	void OnInventorHandlebox();
	void OnInventorCenterball();
	void OnInventorNoManips();
	void OnInventorExaminer();
	void OnInventorFly();
	void OnInventorWalk();
	void OnInventorPlane();


};



#ifndef _DEBUG  
inline SceneViewerDoc* SoSceneViewer::GetDocument()
   { return (SceneViewerDoc*)m_pDocument; }
#endif
