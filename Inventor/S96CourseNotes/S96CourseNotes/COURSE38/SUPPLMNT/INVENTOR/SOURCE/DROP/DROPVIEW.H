// dropView.h : interface of the CDropView class
//
/////////////////////////////////////////////////////////////////////////////

class CDropDoc;

class CDropView : public SoMfcView
{
protected: // create from serialization only
	CDropView();
	DECLARE_DYNCREATE(CDropView)

// Attributes
public:
	CDropDoc* GetDocument();
	void		NewSize(int x, int y);  // called by CMainFrame
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	// viewer state variables
    int		    mode;
    SbBool	    createdCursors;
    // Cursor	    vwrCursor, seekCursor;
    SbVec2s	    locator;    // mouse position
    SbVec2s	    movement;   // mouse movement
    SbVec2s	    windowSize; // cached size of the window
    
    // camera translation vars
    SbVec3f	    locator3D;
    SbPlane	    focalplane;
    float	    transXspeed, transYspeed;
    
    void	    switchMode(int newMode);
    void	    defineCursors();
    void	    translateCamera();
    void        rotateCamera();
    void	    computeTranslateValues();
    static void	transWheelStartCB(void *v, float);



// Generated message map functions
protected:
	//{{AFX_MSG(CDropView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in dropView.cpp
inline CDropDoc* CDropView::GetDocument()
   { return (CDropDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
