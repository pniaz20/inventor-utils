// IViewdoc.h : interface of the CIViewMdiDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CIViewMdiDoc : public SoMfcDoc
{
protected: // create from serialization only
	CIViewMdiDoc();
	DECLARE_DYNCREATE(CIViewMdiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIViewMdiDoc)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIViewMdiDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIViewMdiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
