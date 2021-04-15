// SceneViewerDoc.h : interface of the SceneViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include /**/ <Inventor/mfc/SoMfcDoc.h>
#include /**/ <Inventor/nodes/SoPerspectiveCamera.h>

class SceneViewerDoc : public SoMfcDoc
{
protected: // create from serialization only
	SceneViewerDoc();
	DECLARE_DYNCREATE(SceneViewerDoc)

// Attributes
public:
	void ViewerChange( int nWhichViewer );
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SceneViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle( LPCTSTR lpszTitle );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~SceneViewerDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_nWhichViewer;
// Generated message map functions
protected:
	//{{AFX_MSG(SceneViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
