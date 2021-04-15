// ivviewView.h : interface of the CIvviewView class
//
/////////////////////////////////////////////////////////////////////////////

class CIvviewView : public SoMfcView
{
protected: // create from serialization only
	CIvviewView();
	DECLARE_DYNCREATE(CIvviewView)

// Attributes
public:
	CIvviewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIvviewView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIvviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIvviewView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ivviewView.cpp
inline CIvviewDoc* CIvviewView::GetDocument()
   { return (CIvviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
