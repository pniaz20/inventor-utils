// IViewvw.h : interface of the CIViewMdiView class
//
/////////////////////////////////////////////////////////////////////////////

class CIViewMdiView : public SoMfcView
{
protected: // create from serialization only
	CIViewMdiView();
	DECLARE_DYNCREATE(CIViewMdiView)

// Attributes
public:
	CIViewMdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIViewMdiView)
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIViewMdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIViewMdiView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IViewvw.cpp
inline CIViewMdiDoc* CIViewMdiView::GetDocument()
   { return (CIViewMdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
