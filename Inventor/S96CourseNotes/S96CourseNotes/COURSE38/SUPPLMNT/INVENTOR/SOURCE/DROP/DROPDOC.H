// dropDoc.h : interface of the CDropDoc class
//
/////////////////////////////////////////////////////////////////////////////

class TsField;
class SoMfcViewer;


class CDropDoc : public SoMfcDoc
{
protected: // create from serialization only
	CDropDoc();
	DECLARE_DYNCREATE(CDropDoc)

// Attributes
public:
	TsField *theField;
	CStatusBar * m_pwndStatusBar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDropDoc();
	void InitGame(SoMfcViewer *);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDropDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
